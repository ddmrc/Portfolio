// Code Created By Diego Demarco


#include "Enemy/Minions/MinionMeleeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MyHealthComponent.h"


void AMinionMeleeBase::BeginPlay()
{
	Super::BeginPlay();

}

 void AMinionMeleeBase::AttackPlayer()
{
	 Super::AttackPlayer();

	 if (HealthComponent)
	 {
		 if (!HealthComponent->IsCurrentlyTakingDamage())
		 {
			 UMyHealthComponent* PlayerHealth = UGameplayStatics::GetPlayerCharacter(this, 0)->FindComponentByClass<UMyHealthComponent>();
			 if (PlayerHealth)
			 {
				 float DamageToDeal = FMath::RandRange(BasicDamageToPlayer - 10.f, BasicDamageToPlayer + 10.f);
				 PlayerHealth->InflictDamage(DamageToDeal);
				 if (EnergyComponent)
				 {
					 EnergyComponent->ModifyEnergy(-20.f);
					 EnergyComponent->RechargeEnergy(true);
				 }
					
			 }
		 }

	 }
	  

}
