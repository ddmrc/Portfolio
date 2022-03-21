// Code Created By Diego Demarco


#include "Managers/AudioManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAudioManager::AAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (GameModeBase == nullptr)
	{
		GameModeBase = Cast<APrototypeGameModeBase>(UGameplayStatics::GetGameMode(this));
	}

	if (GameModeBase)
	{
		GameModeBase->PlayerIndoorEvent.AddDynamic(this, &AAudioManager::PlayerIsCurrentlyIndoors);
		GameModeBase->PlayerUnderRoofEvent.AddDynamic(this, &AAudioManager::PlayerIsCurrentlyUnderRoof);
	}


	if (AmbientWindSubManager == nullptr)
	{
		AmbientWindSubManager = FindComponentByClass<UWindAudioSubManager>();

		if (AmbientWindAudio == nullptr)
		{
			AmbientWindAudio = AmbientWindSubManager->AmbientWindAudio;
		}

		AmbientWindSubManager->AmbianceWindSwitchValue.AddDynamic(this, &AAudioManager::AmbientWindChange);
	}

	if (AmbientWindAudio && PlayAmbientWind)
	{
		AmbientWindAudio->Play();
	}


	if (AmbientRainSubManager == nullptr)
	{
		AmbientRainSubManager = FindComponentByClass<URainAudioSubManager>();

		if (AmbientRainAudio == nullptr)
		{
			AmbientRainAudio = AmbientRainSubManager->AmbientRainAudio;
		}

		AmbientRainSubManager->AmbianceRainSwitchValue.AddDynamic(this, &AAudioManager::AmbientRainChange);
	}

	if (AmbientRainAudio && PlayAmbientRain)
	{
		AmbientRainAudio->Play();
	}

	if (AmbientTextureSubManager == nullptr)
	{
		AmbientTextureSubManager = FindComponentByClass<UAmbianceTextureAudioSubManager>();

		if (DroneAmbientSound == nullptr)
		{
			DroneAmbientSound = AmbientTextureSubManager->DroneAmbientSound;
		}

		if (RadiationAmbientSound == nullptr)
		{
			RadiationAmbientSound = AmbientTextureSubManager->RadiationAmbientSound;
		}


	}

	if (DroneAmbientSound && RadiationAmbientSound)
	{
		
		//DroneAmbientSound->FadeIn(10.f, 0.5f);
		//RadiationAmbientSound->FadeIn(10.f);
	}




}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioManager::AmbientWindChange_Implementation(float OldWindSwitchValue, float NewWindSwitchValue, float AlphaTime)
{
	
}

void AAudioManager::AmbientRainChange_Implementation(float OldWindSwitchValue, float NewWindSwitchValue, float AlphaTime)
{

}

void AAudioManager::PlayerIsCurrentlyIndoors_Implementation(bool bIsIndoors)
{

}

void AAudioManager::PlayerIsCurrentlyUnderRoof_Implementation(bool bIsUnderRoof)
{

}