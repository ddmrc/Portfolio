// Code Created By Diego Demarco


#include "Player/MyPlayerAnimBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Player/MyPlayerCharacterBase.h"

bool	UMyPlayerAnimBase::SetIsInAir()
{
	if (TryGetPawnOwner())
	{
		return (TryGetPawnOwner()->GetMovementComponent()->IsFalling());
	}
	return (false);
}

float	UMyPlayerAnimBase::SetSpeed()
{
	if (TryGetPawnOwner())
	{
		return (TryGetPawnOwner()->GetVelocity().Length());
	}
	return (0.f);
}

FRotator	UMyPlayerAnimBase::GetDeltaRotator()
{
	if (TryGetPawnOwner())
	{
		FRotator BaseAimRotation = TryGetPawnOwner()->GetBaseAimRotation();
		FRotator ActorRotation = TryGetPawnOwner()->GetActorRotation();
		FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(BaseAimRotation, ActorRotation);
		return (DeltaRotator);
	}
	return (FRotator::ZeroRotator);
}

float	UMyPlayerAnimBase::GetYawDelta(float DeltaTime, float IntensityScale)
{
	if (TryGetPawnOwner())
	{
		FRotator CurrentRotation = TryGetPawnOwner()->GetActorRotation();

		float Yaw = UKismetMathLibrary::NormalizedDeltaRotator(LastTickRotation, CurrentRotation).Yaw;
		float TargetYaw = (Yaw / DeltaTime) / IntensityScale;
		YawDelta = UKismetMathLibrary::FInterpTo(YawDelta, TargetYaw, DeltaTime, 6.f);
		LastTickRotation = CurrentRotation;
	}
	return (YawDelta);
}

bool	UMyPlayerAnimBase::SetIsAccelerating()
{
	if (TryGetPawnOwner())
	{
		ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
		if (Character)
		{
			float Acceleration = Character->GetCharacterMovement()->GetCurrentAcceleration().Length();
			if (Acceleration > 0.f)
				return (true);
		}
	}
	return (false);
}

bool	UMyPlayerAnimBase::SetIsFullBody(FString CurveName)
{
	if (GetCurveValue(FName(CurveName)) > 0.f)
		return (true);
	return (false);
}

float	UMyPlayerAnimBase::SetLandForce()
{
	if (TryGetPawnOwner())
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(TryGetPawnOwner()->GetWorld(), 0);
		if (PlayerPawn)
		{
			if (!PlayerPawn->GetMovementComponent()->IsMovingOnGround())
			{
				return (PlayerPawn->GetMovementComponent()->Velocity.Z);
			}
		}
	}
	return (0.f);
}

bool	UMyPlayerAnimBase::SetIsAttacking()
{
	bool IsAttacking = false;
	if (TryGetPawnOwner())
	{
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(TryGetPawnOwner()->GetWorld(), 0);
		if (Cast<AMyPlayerCharacterBase>(Player))
		{
			IsAttacking = Cast<AMyPlayerCharacterBase>(Player)->bIsAttacking;
		}
	}
	return (IsAttacking);
}

int32	UMyPlayerAnimBase::SetCurrentCombAttack()
{
	int32 ComboAttack = 0;
	if (TryGetPawnOwner())
	{
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(TryGetPawnOwner()->GetWorld(), 0);
		if (Cast<AMyPlayerCharacterBase>(Player))
		{
			ComboAttack = Cast<AMyPlayerCharacterBase>(Player)->AttackCount;
		}
	}
	return (ComboAttack);
}