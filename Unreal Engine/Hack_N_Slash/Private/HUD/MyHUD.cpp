// Code Created By Diego Demarco


#include "HUD/MyHUD.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UIWidgetClass)
	{
		UIWidget = CreateWidget<UUserInterfaceBase>(GetWorld(), UIWidgetClass);
		if (UIWidget)
		{
			UIWidget->AddToViewport();
			SetUIVisibility(ESlateVisibility::Visible);
		}
	}
}

void AMyHUD::SetUIVisibility(ESlateVisibility State)
{
	if (UIWidget)
		UIWidget->SetVisibility(State);
}

float AMyHUD::ModifyHealthBar(float Amount)
{
	return (UIWidget->ModifyHealthBar(Amount));
}

float	AMyHUD::ModifyEnergyBar(float Amount)
{
	return (UIWidget->ModifyEnergyBar(Amount));
}