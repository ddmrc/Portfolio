// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/MyHealthComponent.h"
#include "Components/EnergyComponent.h"
#include "MyEnemyCharacterBase.generated.h"

UCLASS()
class SOUNDDEMO_TWO_API AMyEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemyCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	

	bool bCanTakeDamage = true;
	bool bHasDied = false;
	bool bHasAttacked = false;

	UPROPERTY(EditAnywhere, Category = "Damage")
		float BasicDamageToPlayer = 20.f;
	UPROPERTY(EditAnywhere, Category = "Damage")
		float TimeBetweenAttacks = 3.f;

	class UWidgetComponent *HealthBarWidget = nullptr;
	class UMyHealthComponent* HealthComponent = nullptr;
	class UEnergyComponent* EnergyComponent = nullptr;

	/*ANIMATIONS*/
	UPROPERTY(EditAnywhere, Category = "Animations")
		class UAnimMontage* TakingDamageAnim = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animations")
		class UAnimMontage*IsDeadAnim = nullptr;
	UPROPERTY(EditAnywhere, Category = "Animations")
		class UAnimMontage* AttackPlayerAnim = nullptr;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap (AActor* OtherActor) override;

	virtual void AttackPlayer();

	void SetHealthBarVisibility(bool bVisible);
	
	UFUNCTION()
		void TakingDamageAnimation();	
	UFUNCTION()
		void IsDeadAnimation();
	UFUNCTION()
		void AttackPlayerAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void AttackPlayerEvent();
	void AttackPlayerEvent_Implementing();

};
