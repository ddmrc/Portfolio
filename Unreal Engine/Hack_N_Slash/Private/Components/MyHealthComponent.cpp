// Code Created By Diego Demarco


#include "Components/MyHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "Enemy/Widgets/DisplayDamageWidget.h"
#include "Enemy/Widgets/HealthBarWidgetBase.h"
#include "HUD/MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

// Sets default values for this component's properties
UMyHealthComponent::UMyHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealthValue;


}


// Called every frame
void UMyHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (DamageWidget == nullptr && ParentDamageWidget == nullptr)
	{
		TArray <UActorComponent*> WidgetArr = GetOwner()->GetComponentsByTag(UWidgetComponent::StaticClass(), "DisplayDamage");
		if (WidgetArr.IsValidIndex(0))
			ParentDamageWidget = Cast<UWidgetComponent>(WidgetArr[0]);

		if (ParentDamageWidget)
		{
			if (ParentDamageWidget->GetWidget())
			{
				DamageWidget = Cast<UDisplayDamageWidget>(ParentDamageWidget->GetWidget());
				ParentDamageWidget->SetVisibility(false, true);
			}
		}
	}

	if (HealthBarWidget == nullptr)
	{
		TArray <UActorComponent*> WidgetArr = GetOwner()->GetComponentsByTag(UWidgetComponent::StaticClass(), "HealthBar");
		if (WidgetArr.IsValidIndex(0))
		{
			if (Cast<UWidgetComponent>(WidgetArr[0])->GetWidget())
			{
				UUserWidget* Widget = Cast<UWidgetComponent>(WidgetArr[0])->GetWidget();
				HealthBarWidget = Cast<UHealthBarWidgetBase>(Widget);
			}
		}
		else
		{
			PlayerHUD = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		}
	}

}

void UMyHealthComponent::InflictDamage(float AmountOfDamage)
{
	if (bCanTakeDamage && CurrentHealth > 0.f)
	{
		bCanTakeDamage = false;

		CurrentHealth = CurrentHealth - AmountOfDamage;

		if (CurrentHealth <= 0.f)
		{
			CurrentHealth = 0.f;
			SetHealthBar(CurrentHealth);
			IsDead.Broadcast();
			return;
		}

		IsTakingDamage.Broadcast();

		if (DamageWidget && ParentDamageWidget)
		{
			ParentDamageWidget->SetVisibility(true, true);
			FText Message = FText::FromString(FString::SanitizeFloat(AmountOfDamage));
			DamageWidget->DamageDisplay->SetText(Message);
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					ParentDamageWidget->SetVisibility(false, true);
				}, 1, false);
		}

		SetHealthBar(CurrentHealth);
		

		FString Message = FString::Printf(TEXT("%s Health: %s (Health Component)"), *GetOwner()->GetName(), *FString::SanitizeFloat(CurrentHealth));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, Message);

	}
}

void UMyHealthComponent::ResetCanTakeDamage()
{
	bCanTakeDamage = true;
}

void UMyHealthComponent::SetHealthBar(float Health)
{
	float OldRange = MaxHealthValue - 0;
	float NewRange = 100 - 0;
	float NewValue = (((Health - 0) * NewRange) / OldRange) + 0;

	if (HealthBarWidget)
	{
		HealthBarWidget->ModifyHealthBar(NewValue / 100);
	}
	else if (PlayerHUD)
	{
		PlayerHUD->ModifyHealthBar(NewValue / 100);
	}
}