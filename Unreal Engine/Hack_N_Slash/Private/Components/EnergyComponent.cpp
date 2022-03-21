// Code Created By Diego Demarco


#include "Components/EnergyComponent.h"
#include "Enemy/Widgets/HealthBarWidgetBase.h"
#include "HUD/MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UEnergyComponent::UEnergyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergyComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnergy = MaxEnergyValue;
	RechargeDelegate = FTimerDelegate::CreateUObject(this, &UEnergyComponent::FillUpEnergy);
}


// Called every frame
void UEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

void UEnergyComponent::ModifyEnergy(float Amount)
{
	CurrentEnergy = CurrentEnergy + Amount;
	float OldRange = MaxEnergyValue - 0;
	float NewRange = 100 - 0;
	float NewValue = (((CurrentEnergy - 0) * NewRange) / OldRange) + 0;

	if (HealthBarWidget)
	{
		HealthBarWidget->ModifyEnergyBar(NewValue / 100);
	}
	else if (PlayerHUD)
	{
		PlayerHUD->ModifyEnergyBar(NewValue / 100);
	}
}

void UEnergyComponent::RechargeEnergy(bool Recharge, float Delay)
{
	GetWorld()->GetTimerManager().ClearTimer(RechargeTimer);
	GetWorld()->GetTimerManager().SetTimer(RechargeTimer, RechargeDelegate, RechargeSpeed, true, Delay);
}

void UEnergyComponent::FillUpEnergy()
{
	if (CurrentEnergy < MaxEnergyValue)
		ModifyEnergy(5.f);
	else if (CurrentEnergy >= MaxEnergyValue)
	{
		CurrentEnergy = MaxEnergyValue;
		if (!GetWorld()->GetTimerManager().IsTimerPaused(RechargeTimer))
			GetWorld()->GetTimerManager().PauseTimer(RechargeTimer);
	}
}
