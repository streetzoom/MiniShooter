// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySphereShooter_SphereSpawner.generated.h"

class AMySphereShooter_Sphere;

/* Created to spawn given number of spheres at given radius */

UCLASS()
class MYSPHERESHOOTER_API AMySphereShooter_SphereSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySphereShooter_SphereSpawner();

	/* 
	* Spawn AllSpawnedSpheresNumber spheres in SpawningRadius
	* Called by game mode when it is needed to spawn spheres wave
	*/
	UFUNCTION()
	void SpawnSpheresInRadius();

	UFUNCTION()
	FVector GetSpawnPoint() const { return SpawnPoint; }

	/* Called by game mode before spawning wave to configure spawning point */
	UFUNCTION()
	void SetSpawnPoint(FVector NewSpawnPoint) { SpawnPoint = NewSpawnPoint; }
	
	/* Called by game mode before spawning wave to configure spawned spheres number */
	UFUNCTION()
	void SetSpawnedSpheresNumber(int32 NewSpawnedSpheresNumber) { AllSpawnedSpheresNumber = NewSpawnedSpheresNumber; }
	
	/* Called by game mode before spawning wave to configure spawning radius */
	UFUNCTION()
	void SetSpawningRadius(float NewRadius) { SpawningRadius = NewRadius; }

	UFUNCTION()
	float GetSpawningRadius() const  { return SpawningRadius; }

	UFUNCTION()
	int32 GetSpawnedSpheresNumber()  const { return AllSpawnedSpheresNumber; }

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;
protected:
	/* Number of all spawned spheres = Number of spheres at 1500 distance + Number of spheres at other distance */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default Spawn Parameters")
	int32 AllSpawnedSpheresNumber;

	/* General spawning radius in meters */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default Spawn Parameters")
	float SpawningRadius;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Default Spawn Parameters")
	FVector SpawnPoint;

	/* Subclass of spheres to choose spawned sphere class in editor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default Spawn Parameters")
	TSubclassOf<AMySphereShooter_Sphere> SphereClass;

	UFUNCTION()
	FVector GetRandomPointInSphere(float SphereRadius);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
