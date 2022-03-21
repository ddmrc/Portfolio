// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/MyHealthComponent.h"
#include "MyPlayerCharacterBase.generated.h"

UCLASS()
class SOUNDDEMO_TWO_API AMyPlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//Variables
	class UEnergyComponent *EnergyComponent = nullptr;

	class UMyHealthComponent* HealthComponent = nullptr;

	UPrimitiveComponent* WeaponCollider = nullptr;

	bool bCanDash = true;
	bool bCanTakeDamage = true;
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, Category = "Camera Sensitivity")
		float LookUpRate = 90.f;

	UPROPERTY(EditAnywhere, Category = "Camera Sensitivity")
		float TurnRate = 50.f;

	UPROPERTY(EditAnywhere, Category = "Attacks")
		float StandardMeleeDamage = 20.f;

	UPROPERTY(EditAnywhere, Category = "Attacks")
		float PushBackEnemyForce = 700.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float DashForce = 900.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float EnergySpentPerDash = -30.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float TimeRecoverEnergyAfterDash = 1.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float TimeResetDash = 2.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		class UAnimMontage *DashAnimation;

	UPROPERTY(EditAnywhere, Category = "TakingDamage")
		class UAnimMontage* TakingDamageAnimation;
	UPROPERTY(EditAnywhere, Category = "TakingDamage")
		float ResetTakeDamage = 0.5f;

	/*ATTACK COMBO*/

	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		class UAnimMontage* AnimAttackA;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		float DurationAttackA = 0.54;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		class UAnimMontage* AnimAttackB;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		float DurationAttackB = 0.54;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		class UAnimMontage* AnimAttackC;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		float DurationAttackC = 0.47;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		class UAnimMontage* AnimAttackD;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		float DurationAttackD = 0.51;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		float AttackSpeed = 1.2f;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
	float DelayBeforeCharginEnergy = 0.25;
	UPROPERTY(EditAnywhere, Category = "Attacks")
	float EnergySpentPerAttack = -20.f;
	UPROPERTY(EditAnywhere, Category = "AttackCombo")
		float TimeForComboReset = 1.f;


	int	AttackCount = 0;
	bool bIsAttacking = false;
	bool bSaveAttack = false;
	FTimerHandle AttackResetCounter;
	FTimerHandle ComboCounter;

	void ResetAttackCombo();

	void StandardAttack();

	void AttackMechanic();

	void ComboAttackSave();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void MoveForward(float AxisValue);

	virtual void MoveRight(float AxisValue);

	virtual void Turn(float AxisValue);

	virtual void LookUp(float AxisValue);

	virtual void StartJump();

	virtual void Interact();

	virtual void Dash();

	AActor* LastFocusedEnemy = nullptr;

	bool bFocusCamera = false;

	virtual void FocusCameraOnEnemy(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void GetNearestEnemy();

	virtual void StartLeftClick();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DisableWeaponCollider();

	UFUNCTION()
	void TakeDamageAnimation();

	UFUNCTION()
		void PlayerIsDead();
	virtual void StopLeftClick(); 

	virtual void StartRightClick();

	virtual void StopRightClick();

	UFUNCTION(BlueprintImplementableEvent, Category = "Dash")
		void DashEvent();
		void DashEvent_Implementing();

	UFUNCTION(BlueprintImplementableEvent, Category = "Jump")
		void JumpEvent();
		void JumpEvent_Implementing();

	UFUNCTION(BlueprintImplementableEvent, Category = "LeftClick")
		void LeftClickEvent();
		void LeftClickEvent_Implementing();

	UFUNCTION(BlueprintImplementableEvent, Category = "LeftClick")
		void LeftUnClickEvent();
		void LeftUnClickEvent_Implementing();

	UFUNCTION(BlueprintImplementableEvent, Category = "RightClick")
		void RightClickEvent();
		void RightClickEvent_Implementing();

	UFUNCTION(BlueprintImplementableEvent, Category = "RightClick")
		void RightUnClickEvent();
		void RightUnClickEvent_Implementing();

};
