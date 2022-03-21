// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API UHealthBarWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* EnergyBar;

	float	ModifyHealthBar(float Amount);

	float	ModifyEnergyBar(float Amount);
	
};
