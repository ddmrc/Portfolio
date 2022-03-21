// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "UserInterfaceBase.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API UUserInterfaceBase : public UUserWidget
{
	GENERATED_BODY()

public:
	//void SetVisibility(ESlateVisibility State);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* EnergyBar;

	float	ModifyHealthBar(float Amount);

	float	ModifyEnergyBar(float Amount);
};
