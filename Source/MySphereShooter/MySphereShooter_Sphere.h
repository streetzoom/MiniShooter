// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySphereShooter_Sphere.generated.h"

/* 
* Class represent spawned sphere that changes its size when spawned
* Spheres are spawned at a some set in Game Mode distance between each other. 
* This distance changes after sphere change its size, because spheres get smaller!
*/

UCLASS()
class MYSPHERESHOOTER_API AMySphereShooter_Sphere : public AActor
{
	GENERATED_BODY()
	
public:	
	/* Sets default values for this actor's properties */
	AMySphereShooter_Sphere();

protected:
	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;
	
	/* Change spawned sphere size by timer call when sphere is spawned */
	UFUNCTION()
	void GraduallyChangeSizeWhenSpawned();

public:	
	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	/* Emit sound and particle effects before sphere is destroyed */
	UFUNCTION()
		void ShowEffectsBeforeDestroy();

	/* Calls Game Mode class to verify if shot sphere lies from spawning point at the distance of 1500 */
	UFUNCTION()
		void OnSphereWasShot();

protected:
	/* Defines distance between spheres by blocking collision */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
		class USphereComponent* SphereComp;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
		UStaticMeshComponent* StaticMeshComp;

	/* Explosion particle component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
		class UParticleSystemComponent* ParticleComp;

	/* Explosion sound component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
		class USoundBase* ExplosionSound;

	/* Counter of function GraduallyChangeSizeWhenSpawned calls */
	UPROPERTY()
	int32 RadiusChangingTick;
	
	/* Sphere radius before decreasing in size*/
	UPROPERTY()
	float InitialSphereRadius;

	/* Minimum sphere radius in cm */
	UPROPERTY()
	float MinimalSphereRadius;

	/* Radius decreasing step in cm */
	UPROPERTY()
	float RadiusChangingStep;

	/* Distance between spheres in cm. It is used in SphereComp when spheres are created */
	UPROPERTY()
	float DistanceBetweenSpheres;
	
	/* Rate of calling GraduallyChangeSizeWhenSpawned in seconds */
	UPROPERTY()
	float RadiusChangingRate;

	/* Timer for calling GraduallyChangeSizeWhenSpawned */
	UPROPERTY()
	FTimerHandle TimerHandle;

protected:
	/* 
	*  Used to set sphere geometry parameters before sphere is spawned. 
	*  It is necessary in order to spawn sphere with custom scale that is set in blueprint.
	*/
	void SetSphereParametersFromGameMode();
};
