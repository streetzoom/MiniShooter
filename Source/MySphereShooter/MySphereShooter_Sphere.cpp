#include "MySphereShooter_Sphere.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundBase.h"
#include "MySphereShooter_GameMode.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Default values
AMySphereShooter_Sphere::AMySphereShooter_Sphere()
{
 	// Actor call Tick() every frame. Turn off to improve performance
	PrimaryActorTick.bCanEverTick = true;
 
    SetSphereParametersFromGameMode();

    RadiusChangingTick = 0;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    SphereComp->InitSphereRadius(InitialSphereRadius + 0.5 * DistanceBetweenSpheres);
    SphereComp->SetupAttachment(RootComponent);
    SphereComp->SetEnableGravity(false);
    
    //This profile was created in order to spawn spheres at some distance from each other and from the other world static objects
    //Profile defines blocking collision for static objects
    SphereComp->BodyInstance.SetCollisionProfileName("SphereZone");

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    StaticMeshComp->AttachToComponent(SphereComp, FAttachmentTransformRules::KeepRelativeTransform);
    StaticMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    
    //scale static mesh from its base diameter (100) to new diameter (2.f * InitialSphereRadius / 100) set in game mode
    const float RadiusRatio = 2.f * InitialSphereRadius / 100;
    StaticMeshComp->SetRelativeScale3D(FVector(RadiusRatio));
    
    //align static mesh with collision sphere in order to proper spawning guided by the distance between spheres
    StaticMeshComp->SetRelativeLocation(FVector(0.0, 0.0, -InitialSphereRadius));
    
    ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
    ParticleComp->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);
    ParticleComp->bAutoActivate = false;
    ParticleComp->bAutoDestroy = true;

    ExplosionSound = CreateDefaultSubobject<USoundBase>(TEXT("ExplosionSound"));
    
    // Effect, sound and mesh are hardcoded for simplicity
    static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    StaticMeshComp->SetStaticMesh(SphereMeshAsset.Object);

    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleCompAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
    ParticleComp->SetTemplate(ParticleCompAsset.Object);

    static ConstructorHelpers::FObjectFinder<USoundBase> ExplosionSoundObject(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion01.Explosion01'"));
    ExplosionSound = ExplosionSoundObject.Object;
}

void AMySphereShooter_Sphere::BeginPlay()
{
	Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AMySphereShooter_Sphere::GraduallyChangeSizeWhenSpawned, RadiusChangingRate, true, 0.3f);
}

void AMySphereShooter_Sphere::GraduallyChangeSizeWhenSpawned()
{
    /* 
    * RadiusRatioWithBaseMesh is used because SetRelativeScale3D function scales mesh relative to some basic size 
    * that is not equal to InitialSphereRadius set in editor
    * Algorithm of changing sphere size when it is spawned:
    * 1. Define how many steps is needed to change radius from InitialSphereRadius to MinimalSphereRadius based on RadiusChangingStep
    * 2. Define start, final sphere scale and scale step based on radii
    * 3. Calculate current scale based on RadiusChangingTick that represents number of this function calling
    */

    const int32 Steps = UKismetMathLibrary::FCeil((InitialSphereRadius - MinimalSphereRadius) / RadiusChangingStep);
    const float RadiusRatioWithBaseMesh = 2.f * InitialSphereRadius / 100;
    const float FinalRadiusRatio = (RadiusRatioWithBaseMesh) * MinimalSphereRadius / InitialSphereRadius;
    const float RadiusRatioStep = (RadiusRatioWithBaseMesh - FinalRadiusRatio) / Steps;
    const float CurrentRadiusRatio = RadiusRatioWithBaseMesh - RadiusChangingTick * RadiusRatioStep;
    
    if (RadiusChangingTick > Steps)
    { 
        GetWorldTimerManager().ClearTimer(TimerHandle);
    }
    else
    {
        StaticMeshComp->SetRelativeScale3D(FVector( CurrentRadiusRatio));
        ++RadiusChangingTick;
    }  
}

void AMySphereShooter_Sphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMySphereShooter_Sphere::ShowEffectsBeforeDestroy() const
{
    const FVector SphereLocation = GetActorLocation();
    if (ParticleComp)
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleComp->Template, SphereLocation, GetActorRotation());
    if (ExplosionSound)
        UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, SphereLocation);
}

void AMySphereShooter_Sphere::OnSphereWasShot() const
{
    AMySphereShooter_GameMode* GameMode = Cast<AMySphereShooter_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode != nullptr)
    {
        GameMode->OnSphereShot(this);
    }
}

void AMySphereShooter_Sphere::SetSphereParametersFromGameMode()
{
    const AMySphereShooter_GameMode* GameMode = Cast<AMySphereShooter_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode != nullptr)
    {
        InitialSphereRadius = GameMode->GetInitialSphereRadius();
        MinimalSphereRadius = GameMode->GetMinimalSphereRadius();
        RadiusChangingStep = GameMode->GetRadiusChangingStep();
        DistanceBetweenSpheres = GameMode->GetDistanceBetweenSpheres();
        RadiusChangingRate = GameMode->GetRadiusChangingRate();
    }
}
