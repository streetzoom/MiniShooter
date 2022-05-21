// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MySphereShooter_GameState.generated.h"

/**
 * Created to save player statistics : current wave number and amount of all shot by player spheres
 */
UCLASS()
class MYSPHERESHOOTER_API AMySphereShooter_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
		int32 GetWaveNumber() const { return WaveNumber; }

	UFUNCTION(BlueprintPure)
		int32 GetNumberSpheresDestroyed() const { return NumberSpheresDestroyed; }
	
	/* Called by Game mode when player complete condition to switch to new wave*/
	UFUNCTION()
		void IncWaveNumber();

	/* Called by Game mode when player shot any sphere*/
	UFUNCTION()
		void IncNumberSpheresDestroyed();

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 WaveNumber = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 NumberSpheresDestroyed = 0;

	/*Used to choose custom widget class in editor*/
	UPROPERTY(EditAnywhere, Category = "User Widget Class")
	TSubclassOf<UUserWidget> WidgetClass;

	/*Used to bind widget and player statistics*/
	UPROPERTY()
	class UMySphereShooter_UserWidget* TextWidget;

protected:
	/*Updates textWidget when player shoots sphere or wave number is increased*/
	UFUNCTION()
	void UpdateTextWidget();
};
