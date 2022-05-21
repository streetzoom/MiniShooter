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
	// Update player statistics
	UFUNCTION()
	void SetWidgetText(FText NewText) const;

protected:
	// Display player statistics 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextLabel;
};
