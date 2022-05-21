#include "MySphereShooter_SphereSpawner.h"
#include "MySphereShooter_Sphere.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

// Default values
AMySphereShooter_SphereSpawner::AMySphereShooter_SphereSpawner()
{
 	// Actor call Tick() every frame. Turn off to improve performance
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnPoint = GetActorLocation();
	AllSpawnedSpheresNumber = 15;
	SpawningRadius = 2000;
}

void AMySphereShooter_SphereSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AMySphereShooter_SphereSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMySphereShooter_SphereSpawner::SpawnSpheresInRadius() const
{
	for (int i = 0; i < AllSpawnedSpheresNumber; ++i)
	{
		const AMySphereShooter_Sphere* CreatedSphere = nullptr;
		
		while (!CreatedSphere) {
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			FVector SpawnLocation = GetRandomPointInSphere(SpawningRadius);
			auto SpanRotation = GetActorRotation();
			CreatedSphere = GetWorld()->SpawnActor<AMySphereShooter_Sphere>(SphereClass, SpawnLocation, SpanRotation, ActorSpawnParams);
		}
	}
}

FVector AMySphereShooter_SphereSpawner::GetRandomPointInSphere(float SphereRadius) const
{
	FVector SpawnLocation = UKismetMathLibrary::RandomUnitVector() * UKismetMathLibrary::RandomFloatInRange(0, SphereRadius) + SpawnPoint;

	// Define room size to let spheres be created only inside of the playing area
	float constexpr LeftConstraintCoord = -2100;
	float constexpr RightConstraintCoord = 1600;
	float constexpr FrontConstraintCoord = 1900;
	float constexpr BackConstraintCoord = -1900;
	float constexpr FloorLevel = 200;
	
	if (SpawnLocation.Z < FloorLevel)
		SpawnLocation.Z += FloorLevel - SpawnLocation.Z;

	if (SpawnLocation.X < LeftConstraintCoord)
		SpawnLocation.X = LeftConstraintCoord;

	if (SpawnLocation.X > RightConstraintCoord)
		SpawnLocation.X = RightConstraintCoord;

	if (SpawnLocation.Y < BackConstraintCoord)
		SpawnLocation.Y = BackConstraintCoord;

	if (SpawnLocation.Y > FrontConstraintCoord)
		SpawnLocation.Y = FrontConstraintCoord;

	return SpawnLocation;
}


