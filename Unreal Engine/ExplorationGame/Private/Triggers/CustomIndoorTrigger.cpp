// Code Created By Diego Demarco


#include "Triggers/CustomIndoorTrigger.h"
#include "GameFramework/Character.h"
#include "GameModeBase/PrototypeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomIndoorTrigger::ACustomIndoorTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomIndoorTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	}
}

// Called every frame
void ACustomIndoorTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACustomIndoorTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	if (OtherActor == PlayerCharacter)
	{		
		Cast<APrototypeGameModeBase>(UGameplayStatics::GetGameMode(this))->PlayerIndoorEvent.Broadcast(true);
	}
}

void ACustomIndoorTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor == PlayerCharacter)
	{
		Cast<APrototypeGameModeBase>(UGameplayStatics::GetGameMode(this))->PlayerIndoorEvent.Broadcast(false);
	}
}
