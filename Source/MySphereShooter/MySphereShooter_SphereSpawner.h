#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySphereShooter_SphereSpawner.generated.h"

class AMySphereShooter_Sphere;

// Spawn given number of spheres at given radius

UCLASS()
class MYSPHERESHOOTER_API AMySphereShooter_SphereSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySphereShooter_SphereSpawner();
	
	UFUNCTION()
	void SpawnSpheresInRadius() const;
	
	UFUNCTION()
	FVector GetSpawnPoint() const { return SpawnPoint; }

	// Configure spawning point
	UFUNCTION()
	void SetSpawnPoint(FVector NewSpawnPoint) { SpawnPoint = NewSpawnPoint; }
	
	// Configure spawned spheres number
	UFUNCTION()
	void SetSpawnedSpheresNumber(int32 NewSpawnedSpheresNumber) { AllSpawnedSpheresNumber = NewSpawnedSpheresNumber; }
	
	// Configure spawning radius
	UFUNCTION()
	void SetSpawningRadius(float NewRadius) { SpawningRadius = NewRadius; }

	UFUNCTION()
	float GetSpawningRadius() const  { return SpawningRadius; }

	UFUNCTION()
	int32 GetSpawnedSpheresNumber()  const { return AllSpawnedSpheresNumber; }
	
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default Spawn Parameters")
	int32 AllSpawnedSpheresNumber;

	// Spawning radius
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default Spawn Parameters")
	float SpawningRadius;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Default Spawn Parameters")
	FVector SpawnPoint;

	// Choose spawned sphere
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default Spawn Parameters")
	TSubclassOf<AMySphereShooter_Sphere> SphereClass;

	UFUNCTION()
	FVector GetRandomPointInSphere(float SphereRadius) const;
	
public:	
	virtual void Tick(float DeltaTime) override;
};
