// Code Created By Diego Demarco


#include "Player/MyPlayerCharacterBase.h"
#include "Enemy/MyEnemyCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "GenericTeamAgentInterface.h"
#include "Components/EnergyComponent.h"
#include "Components/MyHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ActorComponent.h"

// Sets default values
AMyPlayerCharacterBase::AMyPlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponCollider == nullptr)
	{
		TArray<UActorComponent*> ComponentsArr = GetComponentsByTag(UActorComponent::StaticClass(), FName(TEXT("Weapon")));

		for (int i = 0; i < ComponentsArr.Num(); i++)
		{
			if (ComponentsArr.IsValidIndex(i) && ComponentsArr[i]->ComponentHasTag(FName(TEXT("Weapon"))))
			{
				WeaponCollider = Cast<UPrimitiveComponent>(ComponentsArr[i]);
				DisableWeaponCollider();
				break;
			}
		}
		
	}

	if (EnergyComponent == nullptr)
		EnergyComponent = FindComponentByClass<UEnergyComponent>();
	if (HealthComponent == nullptr)
		HealthComponent = FindComponentByClass<UMyHealthComponent>();
	if (HealthComponent)
	{
		HealthComponent->IsTakingDamage.AddDynamic(this, &AMyPlayerCharacterBase::TakeDamageAnimation);
		HealthComponent->IsDead.AddDynamic(this, &AMyPlayerCharacterBase::PlayerIsDead);
	}
}

// Called every frame
void AMyPlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFocusCamera)
	{
		FocusCameraOnEnemy(DeltaTime);
	}

}

// Called to bind functionality to input
void AMyPlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPlayerCharacterBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->GetClass()->IsChildOf(AMyEnemyCharacterBase::StaticClass()))
	{
		if (WeaponCollider && WeaponCollider->IsOverlappingActor(OtherActor))
		{
			UMyHealthComponent* EnemyHealth = OtherActor->FindComponentByClass<UMyHealthComponent>();

			if (EnemyHealth)
			{
				float DamageToDeal = FMath::RandRange(StandardMeleeDamage - 10.f, StandardMeleeDamage + 20.f);
				EnemyHealth->InflictDamage(DamageToDeal);

				FVector Velocity = (GetActorForwardVector() *(PushBackEnemyForce));

				Cast<ACharacter>(OtherActor)->LaunchCharacter(Velocity, true, true);
				
			}
		}
	}
}

void AMyPlayerCharacterBase::MoveForward(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), AxisValue);
	}
}

void AMyPlayerCharacterBase::MoveRight(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), AxisValue);
	}
}

void AMyPlayerCharacterBase::Turn(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->AddYawInput(AxisValue * TurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMyPlayerCharacterBase::LookUp(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->AddPitchInput(AxisValue * LookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMyPlayerCharacterBase::StartJump()
{
	JumpEvent();
	ResetAttackCombo();
	Jump();
}

void AMyPlayerCharacterBase::Interact()
{

}

void AMyPlayerCharacterBase::Dash()
{
	if (bCanDash && EnergyComponent && (EnergyComponent->GetCurrentEnergy() + EnergySpentPerDash) > 0.f)
	{
		bCanDash = false;

		FVector Velocity = (GetActorForwardVector() * DashForce) + FVector(0.f, 0.f, 300.f);

		LaunchCharacter(Velocity, true, true);
		if (DashAnimation)
			PlayAnimMontage(DashAnimation);
		ResetAttackCombo();
		if (EnergyComponent)
		{
			EnergyComponent->ModifyEnergy(EnergySpentPerDash);
			EnergyComponent->RechargeEnergy(true, TimeRecoverEnergyAfterDash);
		}

		DashEvent();


		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				bCanDash = true;
			}, TimeResetDash, false);
	}
	else
	{
		if (EnergyComponent)
			EnergyComponent->RechargeEnergy(true, 0.5f);
	}

}

void AMyPlayerCharacterBase::FocusCameraOnEnemy(float DeltaTime)
{
	UCameraComponent* Camera = FindComponentByClass<UCameraComponent>();
	if (Camera && LastFocusedEnemy)
	{
		bUseControllerRotationYaw = true;

		FVector EnemyLoc = LastFocusedEnemy->GetActorLocation() - FVector(0.f, 0.f, 150.f);
		FRotator FindRotation = UKismetMathLibrary::FindLookAtRotation(Camera->GetComponentLocation(), EnemyLoc);
		FRotator ControllerRotation = GetController()->GetControlRotation();

		float InterpSpeed = 5.f;
		FRotator RInterp = UKismetMathLibrary::RInterpTo(ControllerRotation, FindRotation, DeltaTime, InterpSpeed);

		//FRotator FinalRotation = UKismetMathLibrary::MakeRotator(ControllerRotation.Roll, RInterp.Pitch, RInterp.Yaw);
		FRotator FinalRotation = UKismetMathLibrary::MakeRotator(ControllerRotation.Roll, ControllerRotation.Pitch, RInterp.Yaw);

		GetController()->SetControlRotation(FinalRotation);
	}


}

void AMyPlayerCharacterBase::GetNearestEnemy()
{
	if (!bFocusCamera)
	{
		UCameraComponent* Camera = FindComponentByClass<UCameraComponent>();
		if (Camera)
		{
			TArray<FHitResult> Hits;
			float Range = 1000.f;
			FVector EndLocation = GetActorLocation() + (Camera->GetForwardVector() * Range);

			/*IDEA TO OPTIIMZE*/
			//CREATE A CHANNEL ONLY FOR ENEMIES!!!
			/**/

			ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility;
			FCollisionShape Shape = FCollisionShape::MakeSphere(Range);
			FCollisionQueryParams TraceParams;
			GetWorld()->SweepMultiByChannel(Hits, GetActorLocation(), EndLocation, FQuat::Identity, TraceChannel, Shape, TraceParams);

			for (int i = 0; i < Hits.Num(); i++)
			{

				//if (Hits.IsValidIndex(i) && Hits[i].GetActor() != LastFocusedEnemy)
				if (Hits.IsValidIndex(i))
				{
					if (Hits[i].GetActor()->GetClass()->IsChildOf(AMyEnemyCharacterBase::StaticClass()))
					{
						LastFocusedEnemy = Hits[i].GetActor();
						bFocusCamera = true;
						Cast<AMyEnemyCharacterBase>(LastFocusedEnemy)->SetHealthBarVisibility(true);
						break;
					}
				}
			}
		}
	}
	else
	{
		bFocusCamera = false;
		bUseControllerRotationYaw = false;
		Cast<AMyEnemyCharacterBase>(LastFocusedEnemy)->SetHealthBarVisibility(false);
	}
		

}

void AMyPlayerCharacterBase::StartLeftClick()
{

		LeftClickEvent();

		//Active Weapon Collider
		if (WeaponCollider)
			WeaponCollider->SetGenerateOverlapEvents(true);
		StandardAttack();


}

void AMyPlayerCharacterBase::DisableWeaponCollider()
{
	if (WeaponCollider)
	WeaponCollider->SetGenerateOverlapEvents(false);
}

void AMyPlayerCharacterBase::StopLeftClick()
{
	LeftUnClickEvent();
}

void AMyPlayerCharacterBase::StartRightClick()
{
	RightClickEvent();
}

void AMyPlayerCharacterBase::StopRightClick()
{
	RightUnClickEvent();
}

void AMyPlayerCharacterBase::TakeDamageAnimation()
{
	if (bCanTakeDamage)
	{
		bCanTakeDamage = false;
		if (TakingDamageAnimation)
			PlayAnimMontage(TakingDamageAnimation);
		ResetAttackCombo();
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				if (HealthComponent)
					HealthComponent->ResetCanTakeDamage();
				bCanTakeDamage = true;
			}, ResetTakeDamage, false);
	}

}

void AMyPlayerCharacterBase::PlayerIsDead()
{
	if (!bIsDead)
	{
		bIsDead = true;
		UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
	}

}

void AMyPlayerCharacterBase::StandardAttack()
{
	//Can change AttackSpeed here if necessary
	if (EnergyComponent && (EnergyComponent->GetCurrentEnergy() + EnergySpentPerAttack) > 0.f)
	{
		if (!bIsAttacking)
		{
			bIsAttacking = true;
			bSaveAttack = false;
			AttackMechanic();
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(AttackResetCounter);
			ComboAttackSave();
		}
	}
	else
	{
		ResetAttackCombo();
		DisableWeaponCollider();
	}


}


void AMyPlayerCharacterBase::AttackMechanic()
{
	if (EnergyComponent)
	{
		EnergyComponent->ModifyEnergy(EnergySpentPerAttack);
		EnergyComponent->RechargeEnergy(true, DelayBeforeCharginEnergy);
	}

	float StopAttacking = 0.5f;
	float ComboAttackTrigger = 0.f;
	switch (AttackCount)
	{
	case 0:
		AttackCount = 1;
		if (AnimAttackA)
			PlayAnimMontage(AnimAttackA, AttackSpeed);
		ComboAttackTrigger = AnimAttackA->GetPlayLength() * AttackSpeed;
		StopAttacking = DurationAttackA;
		break;
	case 1:
		AttackCount = 2;
		if (AnimAttackB)
			PlayAnimMontage(AnimAttackB, AttackSpeed);
		ComboAttackTrigger = AnimAttackB->GetPlayLength() * AttackSpeed;
		StopAttacking = DurationAttackB;
		break;
	case 2:
		AttackCount = 3;
		if (AnimAttackC)
			PlayAnimMontage(AnimAttackC, AttackSpeed);
		ComboAttackTrigger = AnimAttackC->GetPlayLength() * AttackSpeed;
		StopAttacking = DurationAttackC;
		break;
	case 3:
		AttackCount = 0;
		if (AnimAttackD)
			PlayAnimMontage(AnimAttackD, AttackSpeed);
		ComboAttackTrigger = AnimAttackD->GetPlayLength() * AttackSpeed;
		StopAttacking = DurationAttackD;
		break;
	}


	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			DisableWeaponCollider();
		}, StopAttacking, false);

	GetWorld()->GetTimerManager().SetTimer(ComboCounter, [&]()
		{
			bSaveAttack = true;
		}, TimeForComboReset / 2.f, false);


	GetWorld()->GetTimerManager().SetTimer(AttackResetCounter, [&]()
	{
		ResetAttackCombo();
	}, TimeForComboReset, false);
}

void AMyPlayerCharacterBase::ComboAttackSave()
{
	if (bSaveAttack)
	{ 
		bSaveAttack = false;
		GetWorld()->GetTimerManager().ClearTimer(ComboCounter);
		AttackMechanic();
	}

}

void AMyPlayerCharacterBase::ResetAttackCombo()
{
	AttackCount = 0;
	bSaveAttack = false;
	bIsAttacking = false;
	if (EnergyComponent)
		EnergyComponent->RechargeEnergy(true, 0.5f);

}


void AMyPlayerCharacterBase::DashEvent_Implementing()
{

}

void AMyPlayerCharacterBase::JumpEvent_Implementing()
{

}

void AMyPlayerCharacterBase::LeftClickEvent_Implementing()
{

}

void AMyPlayerCharacterBase::LeftUnClickEvent_Implementing()
{

}

void AMyPlayerCharacterBase::RightClickEvent_Implementing()
{

}

void AMyPlayerCharacterBase::RightUnClickEvent_Implementing()
{

}