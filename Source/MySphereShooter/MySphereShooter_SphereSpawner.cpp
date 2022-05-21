// Fill out your copyright notice in the Description page of Project Settings.


#include "MySphereShooter_SphereSpawner.h"
#include "Components/SphereComponent.h"
#include "MySphereShooter_Sphere.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMySphereShooter_SphereSpawner::AMySphereShooter_SphereSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnPoint = GetActorLocation();
	AllSpawnedSpheresNumber = 15;
	SpawningRadius = 2000;
}


// Called when the game starts or when spawned
void AMySphereShooter_SphereSpawner::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void AMySphereShooter_SphereSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySphereShooter_SphereSpawner::SpawnSpheresInRadius()
{
	for (int i = 0; i < AllSpawnedSpheresNumber; ++i)
	{
		AMySphereShooter_Sphere* CreatedSphere = nullptr;
		
		/*
		* while loop is used to finally spawn sphere.
		* Sphere may not be spawned at first attempt because of AdjustIfPossibleButDontSpawnIfColliding settings 
		* when Unreal tries to spawn it near the other object such as another sphere. 
		* In such wave i tried to implement necessary condition of distance between spheres.
		*/
		while (!CreatedSphere) {
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			FVector SpawnLocation = GetRandomPointInSphere(SpawningRadius);
			auto SpanRotation = GetActorRotation();
			CreatedSphere = GetWorld()->SpawnActor<AMySphereShooter_Sphere>(SphereClass, SpawnLocation, SpanRotation, ActorSpawnParams);
		}
	}
}

FVector AMySphereShooter_SphereSpawner::GetRandomPointInSphere(float SphereRadius)
{
	FVector SpawnLocation = UKismetMathLibrary::RandomUnitVector() * UKismetMathLibrary::RandomFloatInRange(0, SphereRadius) + SpawnPoint;
	/*
	* These hardcoded values define room size
	* Their usage let spheres be created only inside of the playing area.
	*/
	float LeftConstraintCoord = -2100;
	float RightConstraintCoord = 1600;

	float FrontConstraintCoord = 1900;
	float BackConstraintCoord = -1900;

	float FloorLevel = 200;
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


