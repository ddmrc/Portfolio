// Code Created By Diego Demarco


#include "Enemy/MyEnemyCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyEnemyCharacterBase::AMyEnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (EnergyComponent == nullptr)
		EnergyComponent = FindComponentByClass<UEnergyComponent>();
	if (HealthComponent == nullptr)
		HealthComponent = FindComponentByClass<UMyHealthComponent>();
	if (HealthComponent)
	{
		HealthComponent->IsTakingDamage.AddDynamic(this, &AMyEnemyCharacterBase::TakingDamageAnimation);
		HealthComponent->IsDead.AddDynamic(this, &AMyEnemyCharacterBase::IsDeadAnimation);
	}


}

// Called every frame
void AMyEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthBarWidget == nullptr)
	{
		TArray <UActorComponent*> WidgetArr = GetComponentsByTag(UWidgetComponent::StaticClass(), "HealthBar");
		if (WidgetArr.IsValidIndex(0))
		{
			HealthBarWidget = Cast<UWidgetComponent>(WidgetArr[0]);
			SetHealthBarVisibility(false);
		}
	}
	else
	{
		
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (Player)
		{
			//FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(HealthBarWidget->GetComponentLocation(), Player->GetActorLocation());
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(HealthBarWidget->GetComponentLocation(), 
				Player->FindComponentByClass<UCameraComponent>()->GetComponentLocation());
			HealthBarWidget->SetWorldRotation(Rotation);
		}

	}

}

// Called to bind functionality to input
void AMyEnemyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyEnemyCharacterBase::NotifyActorBeginOverlap(AActor* OtherActor)
{

}

void AMyEnemyCharacterBase::AttackPlayer()
{

	if (HealthComponent)
	{
		if (!HealthComponent->IsCurrentlyTakingDamage())
		{
			AttackPlayerEvent();
			AttackPlayerAnimation();
		}
			
	}
	else
	{
		FString Debug = FString::Printf(TEXT("%s: Health Component not detected in AttackPlayer (EnemyCharacterBase.cpp)"), * GetName());
		if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Debug);
	}
	

}

void AMyEnemyCharacterBase::AttackPlayerEvent_Implementing()
{

}

void AMyEnemyCharacterBase::SetHealthBarVisibility(bool bVisible)
{
	if (HealthBarWidget)
		HealthBarWidget->SetVisibility(bVisible, true);
}

void AMyEnemyCharacterBase::TakingDamageAnimation()
{
	if (bCanTakeDamage)
	{

		bCanTakeDamage = false;
		if (TakingDamageAnim)
			PlayAnimMontage(TakingDamageAnim);

		FTimerHandle TimerHandle;
		float TimeToReset = 0.5f;
		if (HealthComponent)
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					HealthComponent->ResetCanTakeDamage();
					bCanTakeDamage = true;
				}, TimeToReset, false);
	}

}

void AMyEnemyCharacterBase::IsDeadAnimation()
{
	if (!bHasDied)
	{
		bHasDied = true;
		float Duration = 0.f;
		if (IsDeadAnim)
		{
			Duration = IsDeadAnim->GetPlayLength() - 0.25f;
			PlayAnimMontage(IsDeadAnim);
		}
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				Destroy();
			}, Duration, false);
	}

}

void AMyEnemyCharacterBase::AttackPlayerAnimation()
{
	if (!bHasAttacked)
	{
		bHasAttacked = true;
		if (AttackPlayerAnim)
			PlayAnimMontage(AttackPlayerAnim);



		FTimerHandle TimerHandle;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				bHasAttacked = false;
			}, TimeBetweenAttacks, false);
	}
}