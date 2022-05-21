// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MySphereShooter_GameMode.generated.h"

/*
 * Created to guide spawning waves condition and setting sphere geometry parameters 
 */
class AMySphereShooter_Sphere;
class AMySphereShooter_SphereSpawner;

UCLASS()
class MYSPHERESHOOTER_API AMySphereShooter_GameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AMySphereShooter_GameMode();
	
	/* Called by sphere when it is shot to update shot spheres number and verify if shot sphere lies at 1500 distance */
	UFUNCTION()
	void OnSphereShot(AMySphereShooter_Sphere* ShotSphere);

	UFUNCTION()
	float GetInitialSphereRadius() const { return InitialSphereRadius; }

	UFUNCTION()
	float GetMinimalSphereRadius() const { return MinimalSphereRadius; }

	UFUNCTION()
	float GetRadiusChangingStep() const { return RadiusChangingStep; }

	UFUNCTION()
	float GetDistanceBetweenSpheres() const { return DistanceBetweenSpheres; }

	UFUNCTION()
	float GetRadiusChangingRate() const { return RadiusChangingRate; }

	virtual void BeginPlay() override;

protected:
	/* Number of spheres located at MinimumSpawningRadiusToCompleteWave (1500 by default) from spawning point */
	UPROPERTY()
	int32 NecessarySpheresDestroyedNumber;

	/* Sphere radius in cm before decreasing in size */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sphere Parameters")
	float InitialSphereRadius = 25;

	/* Minimum sphere radius in cm */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sphere Parameters")
	float MinimalSphereRadius = 10;

	/* Minimum sphere radius in cm */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sphere Parameters")
	float RadiusChangingStep = 2;

	/* Distance between spheres when they are created */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sphere Parameters")
	float DistanceBetweenSpheres = 80;

	/* Rate of calling changing radius function in seconds*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sphere Parameters")
	float RadiusChangingRate = 0.5;

	/* Amount of spheres player needs to shot before new wave will be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawner Parameters")
	int32 MinimumSpheresNumberToCompleteWave = 10;

	/* Radius where shot spheres is counted for spawning new wave. Cm units */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawner Parameters")
	float MinimumSpawningRadiusToCompleteWave = 1500.f;

	/* Sphere amount increase in percents */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawner Parameters")
	float SpheresAmountPercentageIncrease = 10.f;

	/* Radius increase in percents */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawner Parameters")
	float SpawningRadiusPercentageIncrease = 5.f;

	/* Used to choose shpere spawner class in blueprints. Needed to let user configure sphere spawner blueprint class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sphere Spawner Parameters")
	TSubclassOf<AMySphereShooter_SphereSpawner> SphereSpawnerClass;

	/* Variable that will spawn spheres */
	UPROPERTY()
	AMySphereShooter_SphereSpawner* SphereSpawner;

	/* Check if shot sphere lies at 1500 distance from spawning point */
	UFUNCTION()
	bool IsShotSphereNecessary(AMySphereShooter_Sphere* ShotSphere);

	/* Destroys the rest of the sphere when condition of spawning new wave is completed */
	UFUNCTION()
	void DestroyRemainingSpheres() const;

	/* Increase number of destroyed spheres that lies at 1500 from spawning point */
	UFUNCTION()
	void IncrementNecessarySpheresDestroyedNumber();

	/* Increase sphere spawner general radius and number of spawned spheres before spawn new wave  */
	UFUNCTION()
	void IncreaseSphereSpawnerParameters();

	/* Set sphere spawner number of spawned spheres and spawn radius  */
	UFUNCTION()
	void SetSphereSpawnerParameters(float Radius, int32 SpawningSpheresNumber);

	/* Makes sphere spawner spawn given number of spheres at given radius  
	*  It is called two times to spawn necessary spheres and to spawn the rest of spheres
	*/
	UFUNCTION()
	void SpawnSpheres(float Radius, int32 SpawningSpheresNumber);

	/* Used to calculate number of spheres that should be spawned at 2000 distance */
	UFUNCTION()
	int32 GetUnnecessarySpheresAmount();
};
