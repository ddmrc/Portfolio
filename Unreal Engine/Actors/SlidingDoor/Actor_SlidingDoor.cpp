// Written by Diego Demarco *2022.

#include "Portfolio/Actors/SlidingDoor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASlidingDoor::ASlidingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();
	
	SetTriggers();
	SetDoor();

	CurrentTime = 0.f;
	TimeForAnimation = AnimationTime;
	StartingPosition = InitialPosition;
	FinalPosition = StartingPosition + FVector(0.f, 0.f, AmountToOpen);
	DoorState = EDoorState::Closed;
}

void	ASlidingDoor::SetTriggers()
{
	if (!TriggerOne && !TriggerTwo)
	{
		TArray<UActorComponent*> Temp;
		Temp = GetComponentsOfClass(UBoxComponent::StaticClass(), true);
		if (Temp.IsValidIndex(0))
			TriggerOne = Cast<UBoxComponent>(Temp[0]);
		if (Temp.IsValidIndex(1))
			TriggerTwo = Cast<UBoxComponent>(Temp[1]);
	}
}

void	ASlidingDoor::SetDoor()
{
	if (!Door)
	{
		TArray<UActorComponent*> Temp;
		Temp = GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Door"));
		if (Temp.IsValidIndex(0))
			Door = Cast<UStaticMeshComponent>(Temp[0]);
		InitialPosition = Door->GetComponentLocation();
	}
}

void ASlidingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsPlayerOverlappingTrigger())
		OpenDoor(DeltaTime);
	else
		CloseDoor(DeltaTime);
}
//Using Tick for Demo purposes. Better performance with Begin/End Overlap Delegates. 
bool	ASlidingDoor::IsPlayerOverlappingTrigger()
{
	bool		Result;
	ACharacter	*Player;

	Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!TriggerOne || !TriggerTwo || !Player)
		return (false);
	if (TriggerOne->IsOverlappingActor(Player) || TriggerTwo->IsOverlappingActor(Player))
		Result = true;
	else
		Result = false;
	return (Result);
}

bool	ASlidingDoor::OpenDoor(float DeltaTime)
{
	bool			Result;

	if (!Door || DoorState == EDoorState::Open)
		return (false);
	if (DoorState == EDoorState::Closed)
	{
		StartingPosition = InitialPosition;
		FinalPosition = StartingPosition + FVector(0.f, 0.f, AmountToOpen);
		TimeForAnimation = AnimationTime;
	}
	else if (DoorState == EDoorState::Closing)
	{
		StartingPosition = Door->GetComponentLocation();
		FinalPosition = StartingPosition + FVector(0.f, 0.f, AmountToOpen);
		TimeForAnimation = GetAnimationTime(FinalPosition, StartingPosition);
		CurrentTime = 0.f;
	}

	if (DoorState != EDoorState::Opening)
		DoorState = EDoorState::Opening;
	Result = PerformAnimation(StartingPosition, FinalPosition, DeltaTime);
	return (Result);
}
bool	ASlidingDoor::CloseDoor(float DeltaTime)
{
	bool			Result;

	if (!Door || DoorState == EDoorState::Closed)
		return (false);
	if (DoorState == EDoorState::Open)
	{
		StartingPosition = Door->GetComponentLocation();
		FinalPosition = InitialPosition;
		TimeForAnimation = AnimationTime;
	}
	else if (DoorState == EDoorState::Opening)
	{
		FinalPosition = InitialPosition;
		StartingPosition = Door->GetComponentLocation();
		TimeForAnimation = GetAnimationTime(StartingPosition, FinalPosition);
		CurrentTime = 0.f;
	}

	if (DoorState != EDoorState::Closing)
		DoorState = EDoorState::Closing;
	Result = PerformAnimation(StartingPosition, FinalPosition, DeltaTime);
	return (Result);
}

float	ASlidingDoor::GetAnimationTime(FVector Pos1, FVector Pos2)
{
	float	Result;

	Result = AnimationTime;
	if (Pos1.Z - Pos2.Z <= AmountToOpen / 4.f)
		Result = AnimationTime / 4.f;
	else if (Pos1.Z - Pos2.Z <= AmountToOpen / 2.f)
		Result = AnimationTime / 2.f;
	else if (Pos1.Z - Pos2.Z <= AmountToOpen / 1.2f)
		Result = AnimationTime / 1.2f;
	return (Result);
}

bool	ASlidingDoor::PerformAnimation(FVector Start, FVector Finish, float DeltaTime)
{
	bool		Result;
	float		AlphaTime;
	FVector		CurrentLocation;

	Result = true;
	CurrentTime += DeltaTime;
	AlphaTime = FMath::Clamp(CurrentTime / TimeForAnimation, 0.0f, 1.0f);
	CurrentLocation = FMath::Lerp(Start, Finish, AlphaTime);
	Door->SetWorldLocation(CurrentLocation);
	if (Door->GetComponentLocation().Equals(Finish, 10.f))
	{
		CurrentTime = 0.f;
		DoorState = EDoorState::Closed;
		Result = false;
	}
	return (Result);
}

TArray<UActorComponent*>	ASlidingDoor::GetComponentsOfClass(TSubclassOf<UActorComponent> ComponentClass, bool bIncludeChildActors)
{
	TArray<UActorComponent*>		Components;
	TArray<UActorComponent*>		Temp;

	GetComponents(Temp, bIncludeChildActors);
	for (int i = 0; i < Temp.Num(); i++)
	{
		if (Temp.IsValidIndex(i) && Temp[i]->GetClass()->IsChildOf(ComponentClass))
			Components.Add(Temp[i]);
	}
	return (Components);
}

