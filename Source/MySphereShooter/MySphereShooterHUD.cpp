#include "MySphereShooterHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AMySphereShooterHUD::AMySphereShooterHUD()
{
	// Crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}

void AMySphereShooterHUD::DrawHUD()
{
	Super::DrawHUD();
	// Canvas center
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// Center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),(Center.Y + 20.0f));

	// Crosshair draw
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->GetResource(), FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}
