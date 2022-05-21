#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MySphereShooterHUD.generated.h"

UCLASS()
class AMySphereShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMySphereShooterHUD();
	
	virtual void DrawHUD() override;

private:
	class UTexture2D* CrosshairTex;
};

