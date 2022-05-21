// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySphereShooter_Projectile.generated.h"

/*  Represents projectile shot from character gun.
*	Almost all code is copied from FPS template projectile class.
*	OnOverlap function is added.
*/

UCLASS()
class MYSPHERESHOOTER_API AMySphereShooter_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySphereShooter_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
		class UProjectileMovementComponent* ProjectileMovement;

	/* Used to hit all objects but sphere spawned by sphere spawner */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	/* Used to call overlapped sphere emmitting effects function and checking function before destroy it */
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

};
