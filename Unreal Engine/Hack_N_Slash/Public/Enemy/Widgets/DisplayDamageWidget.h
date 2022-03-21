// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DisplayDamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API UDisplayDamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* DamageDisplay;
	
};
