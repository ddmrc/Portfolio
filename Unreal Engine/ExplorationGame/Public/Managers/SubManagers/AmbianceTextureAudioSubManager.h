// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/AmbientSound.h"
#include "AmbianceTextureAudioSubManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAINPROTOTYPE_API UAmbianceTextureAudioSubManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAmbianceTextureAudioSubManager();

	UPROPERTY(EditAnywhere)
	AAmbientSound* DroneAmbientSound = nullptr;
	UPROPERTY(EditAnywhere)
	AAmbientSound* RadiationAmbientSound = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
