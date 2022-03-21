// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundAttenuation.h"
#include "Components/PointLightComponent.h"
#include "Components/ActorComponent.h"
#include "OuterWallTrigger.generated.h"

USTRUCT()
struct FTriggerPoint
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		FString TagForTriggerPoint;
		UPROPERTY(EditAnywhere)
		USoundCue* SoundToSpawn;	
		UPROPERTY(EditAnywhere)
		USoundAttenuation* AttenuationSettings;
		UPROPERTY(EditAnywhere)
		bool TriggerAtSpecificLocation = false;
		UPROPERTY(EditAnywhere)
		FVector SoundLocationOffset = FVector::ZeroVector;
		UPROPERTY(EditAnywhere)
		bool EnableRandomSoundSpawn = false;
		UPROPERTY(EditAnywhere)
		FVector RandomRangeOffset = FVector::ZeroVector;
};

USTRUCT()
struct FInternalTriggerSoundBind
{
	GENERATED_BODY()


		UStaticMeshComponent* MeshComponent;
		USoundCue* SoundCue;
		USoundAttenuation* Attenuation;
		FVector SoundLocationOffset = FVector::ZeroVector;
		bool bTriggerAtSpecificLocation = false;
		bool EnableRandomSoundSpawn = false;
		FVector RandomRangeOffset = FVector::ZeroVector;
};

USTRUCT()
struct FFinalTriggerPoint
{
	GENERATED_BODY()

		
		float TriggerPoint;
		USoundCue* SoundCue;
		USoundAttenuation* Attenuation;	
		FVector SoundLocationOffset = FVector::ZeroVector;
		bool EnableRandomSoundSpawn = false;
		FVector RandomRangeOffset = FVector::ZeroVector;

};
UCLASS()
class RAINPROTOTYPE_API AOuterWallTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOuterWallTrigger();

protected:

	ACharacter* PlayerCharacter = nullptr;

	float RelativeBoxStartingLocationA = 0.f;
	float RelativeBoxStartingLocationB = 0.f;

	float BoxExtenteDistance = 0.f;

	float PlayerDotProduct = 0.f;
	float PlayerDistanceTraveled = 0.f;

	float PlayerDistanceOffset = 0.f;

	float RefLocationPlayer = 0.f;

	float PlayerForwardVector = 0.f;

	TArray <FFinalTriggerPoint> TriggerLocations;

	bool bIsPlayerIn = false;
	bool bTriggerPointIsActive = false;

	UPROPERTY(EditAnywhere, Category = "Trigger Points")
	TArray<FTriggerPoint> TriggerPoints;

	UPROPERTY(EditAnywhere, Category = "Number Of Triggers")
		bool TriggerSound1 = false;
	UPROPERTY(EditAnywhere, Category = "Number Of Triggers")
		bool TriggerSound2 = false;
	UPROPERTY(EditAnywhere, Category = "Number Of Triggers")
		bool TriggerSound3 = false;
	UPROPERTY(EditAnywhere, Category = "Number Of Triggers")
		bool TriggerSound4 = false;
	UPROPERTY(EditAnywhere, Category = "Number Of Triggers")
		bool TriggerSound5 = false;
	UPROPERTY(EditAnywhere, Category = "Number Of Triggers")
		bool TriggerSound6 = false;
	UPROPERTY(EditAnywhere, Category = "Number Of Triggers")
		bool TriggerSound7 = false;


	UPROPERTY(EditAnywhere, Category = "Axis Selection")
	bool OverrideWithAxisY = false;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DebugLocation = false;

	UStaticMeshComponent* MainBoxMesh = nullptr;

	FVector PlayerRelativeLocation = FVector::ZeroVector;

	TArray<UAudioComponent*> EdgeOfWorldAudioComponents;	

	TArray <FInternalTriggerSoundBind> InternalTriggerSoundBindArr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	void PlayerDetectionWithinTriggerArea();
	void SetProperRelativeStartPoint();
	void SetProperBoxExtent();
	void SetPlayerOffset();
	void SetTriggersLocation();
	void TriggerSound(bool bActivated,float index);
	void PlayTriggerSoundAtLocation(FFinalTriggerPoint Trigger, FVector SoundLocation, float StratTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
