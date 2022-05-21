// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySphereShooter_UserWidget.generated.h"

/**
 * Class to display player statistics in blueprint bound widget
 */
UCLASS()
class MYSPHERESHOOTER_API UMySphereShooter_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/* Called by game state to update player statistics sent in NewText */
	UFUNCTION()
	void SetWidgetText(FText NewText);

protected:
	/* Bounded widget variable to display player statistics */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextLabel;
};
