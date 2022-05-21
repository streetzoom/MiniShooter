// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MySphereShooterHUD.generated.h"

/*
* Class is fully copied from FPS Template
*/

UCLASS()
class AMySphereShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMySphereShooterHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

