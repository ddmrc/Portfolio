// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOUNDDEMO_TWO_API UEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "Energy")
		float MaxEnergyValue = 100.f;

	UPROPERTY(EditAnywhere, Category = "Energy")
		float RechargeSpeed = 0.25f;

	float CurrentEnergy = 0.f;

	class UHealthBarWidgetBase* HealthBarWidget = nullptr;

	class AMyHUD* PlayerHUD = nullptr;

	FTimerHandle RechargeTimer;
	FTimerDelegate RechargeDelegate;

	UFUNCTION(BlueprintCallable, Category = "Energy")
	void ModifyEnergy(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Energy")
	void RechargeEnergy(bool Recharge, float Delay = 0.25f);

	float GetCurrentEnergy() { return CurrentEnergy; }

	void FillUpEnergy();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
