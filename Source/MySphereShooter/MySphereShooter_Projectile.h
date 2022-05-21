#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySphereShooter_Projectile.generated.h"

/*  Represents projectile shot from character gun.
*	OnOverlap function is added.
*/

UCLASS()
class MYSPHERESHOOTER_API AMySphereShooter_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Default values
	AMySphereShooter_Projectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
		class UProjectileMovementComponent* ProjectileMovement;

	/* Used to hit all objects but sphere spawned by sphere spawner */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	/* Used to call overlapped sphere emitting effects function and checking function before destroy it */
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
};
