// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/AmbientSound.h"
#include "Managers/SubManagers/WindAudioSubManager.h"
#include "Managers/SubManagers/RainAudioSubManager.h"
#include "Managers/SubManagers/AmbianceTextureAudioSubManager.h"
#include "GameModeBase/PrototypeGameModeBase.h"
#include "AudioManager.generated.h"

UCLASS()
class RAINPROTOTYPE_API AAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioManager();

	UPROPERTY(EditAnywhere, Category = "Toggle On BeginPlay")
		bool PlayAmbientWind = true;
	UPROPERTY(EditAnywhere, Category = "Toggle On BeginPlay")
		bool PlayAmbientRain = true;

	UFUNCTION(BlueprintCallable, Category = "AmbientSound")
	AAmbientSound* GetAmbientWindSound() {  return AmbientWindAudio;  };

	UFUNCTION(BlueprintCallable, Category = "AmbientSound")
		AAmbientSound* GetAmbientRainSound() { return AmbientRainAudio; };

	UFUNCTION(BlueprintImplementableEvent, Category = "AmbientSound")
	void AmbientWindChange(float OldWindSwitchValue, float NewWindSwitchValue, float AlphaTime);
	void AmbientWindChange_Implementation(float OldWindSwitchValue, float NewWindSwitchValue, float AlphaTime);


	UFUNCTION(BlueprintImplementableEvent, Category = "AmbientSound")
	void AmbientRainChange(float OldWindSwitchValue, float NewWindSwitchValue, float AlphaTime);
	void AmbientRainChange_Implementation(float OldWindSwitchValue, float NewWindSwitchValue, float AlphaTime);

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerLocation")
	void PlayerIsCurrentlyIndoors(bool bIsIndoors);
	void PlayerIsCurrentlyIndoors_Implementation(bool bIsIndoors);

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerLocation")
	void PlayerIsCurrentlyUnderRoof(bool bIsUnderRoof);
	void PlayerIsCurrentlyUnderRoof_Implementation(bool bIsUnderRoof);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APrototypeGameModeBase* GameModeBase = nullptr;

	UWindAudioSubManager* AmbientWindSubManager = nullptr;
	AAmbientSound* AmbientWindAudio = nullptr;

	URainAudioSubManager* AmbientRainSubManager = nullptr;
	AAmbientSound* AmbientRainAudio = nullptr;

	UAmbianceTextureAudioSubManager* AmbientTextureSubManager = nullptr;
	AAmbientSound* DroneAmbientSound = nullptr;
	AAmbientSound* RadiationAmbientSound = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
