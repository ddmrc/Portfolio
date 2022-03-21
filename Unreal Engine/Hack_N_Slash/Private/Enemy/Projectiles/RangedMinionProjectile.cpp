// Code Created By Diego Demarco


#include "Enemy/Projectiles/RangedMinionProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/MyHealthComponent.h"

// Sets default values
ARangedMinionProjectile::ARangedMinionProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARangedMinionProjectile::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(this, 0);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([&] { bEmergencyDestroy = true;});
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 5.f, false);

}

// Called every frame
void ARangedMinionProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEmergencyDestroy)
	{
		Destroy();
	}



}

void ARangedMinionProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{

	if (OtherActor == Player)
	{
		if (UMyHealthComponent* PlatyerHealth = Player->FindComponentByClass<UMyHealthComponent>())
		{
			float DamageToDeal = FMath::RandRange(DamageToPlayer - 10.f, DamageToPlayer + 10.f);
			PlatyerHealth->InflictDamage(DamageToDeal);
			Destroy();
		}
	}
}

