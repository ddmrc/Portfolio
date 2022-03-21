// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayerAnimBase.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API UMyPlayerAnimBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		bool	SetIsInAir();

	UFUNCTION(BlueprintCallable)
		float	SetSpeed();

	UFUNCTION(BlueprintCallable)
		FRotator	GetDeltaRotator();

	UFUNCTION(BlueprintCallable)
		float	GetYawDelta(float DeltaTime, float IntensityScale = 7.f);

	UFUNCTION(BlueprintCallable)
		bool	SetIsAccelerating();

	UFUNCTION(BlueprintCallable)
		bool	SetIsFullBody(FString CurveName);

	UFUNCTION(BlueprintCallable)
		float	SetLandForce();

	UFUNCTION(BlueprintCallable)
		bool	SetIsAttacking();

	UFUNCTION(BlueprintCallable)
		int32	SetCurrentCombAttack();

private:
	
	FRotator LastTickRotation = FRotator::ZeroRotator;
	float	YawDelta = 0.f;
};
