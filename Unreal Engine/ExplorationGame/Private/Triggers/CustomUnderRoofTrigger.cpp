// Code Created By Diego Demarco


#include "Triggers/CustomUnderRoofTrigger.h"
#include "GameFramework/Character.h"
#include "GameModeBase/PrototypeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomUnderRoofTrigger::ACustomUnderRoofTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomUnderRoofTrigger::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	}
}

// Called every frame
void ACustomUnderRoofTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomUnderRoofTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor == PlayerCharacter)
	{
		Cast<APrototypeGameModeBase>(UGameplayStatics::GetGameMode(this))->PlayerUnderRoofEvent.Broadcast(true);
	}
}

void ACustomUnderRoofTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor == PlayerCharacter)
	{
		Cast<APrototypeGameModeBase>(UGameplayStatics::GetGameMode(this))->PlayerUnderRoofEvent.Broadcast(false);
	}
}

