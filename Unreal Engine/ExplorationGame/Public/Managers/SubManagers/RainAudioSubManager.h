// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/AmbientSound.h"
#include "RainAudioSubManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRainSwitchValue, float, OldSwitchParam, float, NewSwitchParam, float, AlphaTime);

UENUM(BlueprintType)
enum class EAmbianceRainState :uint8
{
	Initial,
	Soft,
	Medium,
	Hard,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAINPROTOTYPE_API URainAudioSubManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URainAudioSubManager();

	UPROPERTY(EditAnywhere)
	AAmbientSound* AmbientRainAudio = nullptr;

	FRainSwitchValue AmbianceRainSwitchValue;

	float GetOldSwitchParamAsFloat() { return (float)OldSwitchParam; }
	float GetNewSwitchParamAsFloat() { return (float)NewSwitchParam; }
	float GetAlphaSwitchParam() { return AlphaSwitchParam; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Default Rain")
	EAmbianceRainState NewSwitchParam = EAmbianceRainState::Initial;
	UPROPERTY(EditAnywhere, Category = "Default Rain")
	float AlphaSwitchParam = 1.f;

	EAmbianceRainState OldSwitchParam = NewSwitchParam;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
