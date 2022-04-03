// Written by Diego Demarco *2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlidingDoor.generated.h"

UENUM() 
enum class EDoorState : uint8
{
	Closed		UMETA(DisplayName = "Closed"),
	Closing		UMETA(DisplauName = "Closing"),
	Open		UMETA(DisplauName = "Open"),
	Opening		UMETA(DisplauName = "Opening")
};

UCLASS()
class AUDIOTESTING_API ASlidingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlidingDoor();

protected:
	//Door State
	EDoorState					DoorState;
	//Open Close Trigger
	class UBoxComponent				*TriggerOne = nullptr;
	//Open Close Trigger
	class UBoxComponent				*TriggerTwo = nullptr;
	//Door Mesh
	class UStaticMeshComponent			*Door = nullptr;
	//Actors Initial Location
	FVector						InitialPosition = FVector::ZeroVector;
	//Actor's Starting Location
	FVector						StartingPosition = FVector::ZeroVector;
	//Actor's Final Position
	FVector						FinalPosition = FVector::ZeroVector;
	//Time used for Animation
	float						CurrentTime;
	//Amount of Distance to Open
	UPROPERTY(EditAnywhere, Category = "OpeningAmount")
	float						AmountToOpen = 240.f;
	//Time to Open/Close in seconds
	UPROPERTY(EditAnywhere, Category = "OpeningAmount")
	float						AnimationTime = 3.f;
	//This is used internaly
	float						TimeForAnimation;
	
	public:
	// Called when the game starts or when spawned
	virtual void					BeginPlay() override;
	// Called every frame
	virtual void					Tick(float DeltaTime) override;
	//Player Overlapping Trigger
	bool						IsPlayerOverlappingTrigger();
	//Open Door
	bool						OpenDoor(float DeltaTime);
	//Close Door
	bool						CloseDoor(float DeltaTime);
	//Get Time for Animation based on Location. Pos1 - Pos 2.
	float						GetAnimationTime(FVector Pos1, FVector Pos2);
	//Perform Animation
	bool						PerformAnimation(FVector Start, FVector Finish, float DeltaTime);
	//Redefined deprecated GetComponentsByClass
	TArray<UActorComponent*>			GetComponentsOfClass(TSubclassOf<UActorComponent> ComponentClass, bool bIncludeChildActors);
};

