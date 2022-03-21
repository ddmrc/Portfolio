// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/AmbientSound.h"
#include "WindAudioSubManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWindSwitchValue, float, OldSwitchParam, float, NewSwitchParam, float, AlphaTime);
UENUM(BlueprintType)
enum class EAmbianceWindState :uint8
{
	Initial,
	Soft,
	Medium,
	Hard,
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAINPROTOTYPE_API UWindAudioSubManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWindAudioSubManager();

	UPROPERTY(EditAnywhere)
	AAmbientSound* AmbientWindAudio = nullptr;

	FWindSwitchValue AmbianceWindSwitchValue;


	float GetOldSwitchParamAsFloat() { return (float)OldSwitchParam; }
	float GetNewSwitchParamAsFloat() { return (float)NewSwitchParam; }
	float GetAlphaSwitchParam() { return AlphaSwitchParam; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Default Wind")
	EAmbianceWindState NewSwitchParam = EAmbianceWindState::Initial;
	UPROPERTY(EditAnywhere, Category = "Default Wind")
	float AlphaSwitchParam = 1.f;

	EAmbianceWindState OldSwitchParam = NewSwitchParam;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
