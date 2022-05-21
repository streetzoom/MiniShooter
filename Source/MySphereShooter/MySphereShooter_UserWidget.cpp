#include "MySphereShooter_UserWidget.h"
#include "Components/TextBlock.h"

void UMySphereShooter_UserWidget::SetWidgetText(FText NewText) const
{
	TextLabel->SetText(NewText);
}
