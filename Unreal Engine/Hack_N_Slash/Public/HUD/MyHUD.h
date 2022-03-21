// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD/Widgets/UserInterfaceBase.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserInterfaceBase> UIWidgetClass;

	UUserInterfaceBase* UIWidget;

	void SetUIVisibility(ESlateVisibility State);

	float	ModifyHealthBar(float Amount);

	float ModifyEnergyBar(float Amount);

protected:

	virtual void BeginPlay() override;


	
};
