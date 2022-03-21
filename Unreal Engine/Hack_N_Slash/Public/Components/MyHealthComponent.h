// Code Created By Diego Demarco
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyHealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIsTakingDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIsDead);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOUNDDEMO_TWO_API UMyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyHealthComponent();

protected:

	//Variables
	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealthValue = 400.f;

	float CurrentHealth;

	bool bCanTakeDamage = true;

	// Called when the game starts
	virtual void BeginPlay() override;




	void SetHealthBar(float CurrentHealth);



public:	

	UPROPERTY(BlueprintAssignable, Category = "Damage")
		FIsTakingDamage IsTakingDamage;

	UPROPERTY(BlueprintAssignable, Category = "Damage")
		FIsDead IsDead;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class UDisplayDamageWidget* DamageWidget = nullptr;

	class UWidgetComponent* ParentDamageWidget = nullptr;

	class UHealthBarWidgetBase* HealthBarWidget = nullptr;

	class AMyHUD* PlayerHUD = nullptr;

	void InflictDamage(float AmountOfDamage);


	UFUNCTION(BlueprintCallable, Category = "Damage")
		void ResetCanTakeDamage();

	UFUNCTION(BlueprintCallable, Category = "Damage")
		bool IsCurrentlyTakingDamage() { return !bCanTakeDamage; };
};
