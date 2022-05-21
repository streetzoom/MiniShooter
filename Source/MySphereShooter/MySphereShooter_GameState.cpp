// Fill out your copyright notice in the Description page of Project Settings.


#include "MySphereShooter_GameState.h"
#include "MySphereShooter_UserWidget.h"
#include "Blueprint/UserWidget.h"

void AMySphereShooter_GameState::BeginPlay() 
{
	if (IsValid(WidgetClass))
	{
		TextWidget = Cast<UMySphereShooter_UserWidget>(CreateWidget(GetWorld(), WidgetClass));
		
		if (TextWidget != nullptr)
		{
			TextWidget->AddToViewport();
		}
	}
}

void AMySphereShooter_GameState::IncWaveNumber()
{
	++WaveNumber;
	UpdateTextWidget();
}

void AMySphereShooter_GameState::IncNumberSpheresDestroyed()
{
	++NumberSpheresDestroyed;
	UpdateTextWidget();
}

void AMySphereShooter_GameState::UpdateTextWidget()
{
	if (TextWidget != nullptr)
	{
		TextWidget->SetWidgetText(FText::FromString(FString::Printf(TEXT("Wave: %i; Score: %i"), WaveNumber, NumberSpheresDestroyed)));
	}
}
