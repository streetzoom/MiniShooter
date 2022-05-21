// Fill out your copyright notice in the Description page of Project Settings.


#include "MySphereShooter_Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MySphereShooter_Sphere.h"

// Sets default values
AMySphereShooter_Projectile::AMySphereShooter_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionSphere->InitSphereRadius(5.0f);
	CollisionSphere->BodyInstance.SetCollisionProfileName("Projectile");

	CollisionSphere->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionSphere->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionSphere;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void AMySphereShooter_Projectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentHit.AddDynamic(this, &AMySphereShooter_Projectile::OnHit);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMySphereShooter_Projectile::OnOverlap);
}

// Called every frame
void AMySphereShooter_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySphereShooter_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}
}

void AMySphereShooter_Projectile::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if ((OtherActor != nullptr))
	{
		if (OtherActor->IsA(AMySphereShooter_Sphere::StaticClass()))
		{
			AMySphereShooter_Sphere* SphereReference = Cast<AMySphereShooter_Sphere>(OtherActor);
			SphereReference->OnSphereWasShot();
			SphereReference->ShowEffectsBeforeDestroy();
			SphereReference->Destroy();
		}
		Destroy();
	}
}