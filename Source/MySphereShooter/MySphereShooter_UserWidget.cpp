// Fill out your copyright notice in the Description page of Project Settings.


#include "MySphereShooter_UserWidget.h"
#include "Components/TextBlock.h"

void UMySphereShooter_UserWidget::SetWidgetText(FText NewText) {
	TextLabel->SetText(NewText);
}