// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/Audio/CustomSpotAudioComponent.h"
#include "PhantomAudioSphere.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Audio), meta = (BlueprintSpawnableComponent))
class RAINPROTOTYPE_API UPhantomAudioSphere : public USphereComponent
{
	GENERATED_BODY()

public:

	UPhantomAudioSphere();

protected:

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
};
