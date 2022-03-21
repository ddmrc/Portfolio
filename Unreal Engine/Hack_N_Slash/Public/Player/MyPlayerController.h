// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/MyPlayerCharacterBase.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	AMyPlayerCharacterBase* PlayerCharacterBase = nullptr;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	//AXIS
	void RequestMoveForward(float AxisValue);

	void RequestMoveRight(float AxisValue);

	void RequestTurn(float AxisValue);

	void RequestLookUp(float AxisValue);

	//ACTIONS
	void RequestJump();

	void RequestInteract();

	void RequestDash();

	void RequestStartLeftClick();

	void RequestStopLeftClick();

	void RequestStartRightClick(); 

	void RequestStopRightClick();
	
};
