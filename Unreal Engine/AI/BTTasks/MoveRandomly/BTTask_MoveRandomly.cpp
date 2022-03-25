// Written by Diego Demarco *2022.


#include "AI/BTTasks/Locomotion/BTTask_MoveRandomly.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "AIController.h"


UBTTask_MoveRandomly::UBTTask_MoveRandomly(const FObjectInitializer& objectInitializer)
{
	NodeName = "MoveRandomly";
	bNotifyTick = true;
}

EBTNodeResult::Type	UBTTask_MoveRandomly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type		NodeResult;
	FBTMoveToTaskMemory		*MyMemory;
	AAIController			*Controller;
	UBlackboardComponent		*BlackboardComp;
	ACharacter			*Character;

	NodeResult = EBTNodeResult::InProgress;
	Controller = OwnerComp.GetAIOwner();
	BlackboardComp = OwnerComp.GetBlackboardComponent();
	Character = Controller->GetCharacter();

	MyMemory = CastInstanceNodeMemory<FBTMoveToTaskMemory>(NodeMemory);
	MyMemory->PreviousGoalLocation = FAISystem::InvalidLocation;
	MyMemory->MoveRequestID = FAIRequestID::InvalidRequest;
	MyMemory->bWaitingForPath = bUseGameplayTasks ? false : Controller->ShouldPostponePathUpdates();

	if (MoveToLocation == FVector::ZeroVector)
	{
		MoveToLocation = GetRandLocation(OwnerComp);
		BlackboardComp->SetValueAsVector(FName(BB_KeyLocationName), MoveToLocation);
	}

	//On Task Finished
	if (!MyMemory->bWaitingForPath)
	{
		NodeResult = PerformMoveTask(OwnerComp, NodeMemory);
		MoveToLocation = FVector::ZeroVector;
	}

	return (NodeResult);
}

FVector	UBTTask_MoveRandomly::GetRandLocation(UBehaviorTreeComponent& OwnerComp)
{
	ACharacter*		Character;
	float			LocationX;
	float			LocationY;
	float			LocationZ;

	Character = OwnerComp.GetAIOwner()->GetCharacter();
	LocationX = 0.0f;
	LocationY = 0.0f;
	if (SpawnLocation == FVector::ZeroVector && MoveToLocation == FVector::ZeroVector)
	{
		SpawnLocation = Character->GetActorLocation();
		LocationX = SpawnLocation.X;
		LocationY = SpawnLocation.Y;
		LocationZ = SpawnLocation.Z;
		GetLocationBoundaries();
	}
	if (bLocationOnSpawnPoint)
	{
		LocationX = GetLocationXSpawnPoint(Character->GetActorLocation().X);
		LocationY = GetLocationYSpawnPoint(Character->GetActorLocation().Y);
	}
	else
	{
		LocationX = GetLocationXNonSpawnPoint(Character->GetActorLocation().X, Character);
		LocationY = GetLocationYNonSpawnPoint(Character->GetActorLocation().Y, Character);
	}
	LocationZ = Character->GetActorLocation().Z;

	DebugOptions(Character, (FVector(LocationX, LocationY, LocationZ)));
	return (FVector(LocationX, LocationY, LocationZ));
}

float	UBTTask_MoveRandomly::GetLocationXSpawnPoint(float LocationX)
{
	float		CurrentLocation;
	int32		Direction;

	CurrentLocation = LocationX;
	//Allows to alternate directions
	Direction = FMath::RandRange(0, 1);
	if (Direction == 0)
	{
		LocationX = SpawnLocation.X + FMath::RandRange(MinWalkOffset, -Radius);
		LocationX = AdjustLocBoundaries(LocationX, CurrentLocation, Direction, 'X');
	}
	else if (Direction == 1)
	{
		LocationX = SpawnLocation.X + FMath::RandRange(CurrentLocation + MinWalkOffset, Radius);
		LocationX = AdjustLocBoundaries(LocationX, CurrentLocation, Direction, 'X');
	}
	return (LocationX);
}

float	UBTTask_MoveRandomly::GetLocationYSpawnPoint(float LocationY)
{
	float		CurrentLocation;
	int32		Direction;

	CurrentLocation = LocationY;
	//Allows to alternate directions
	Direction = FMath::RandRange(0, 1);
	if (Direction == 0)
	{
		LocationY = SpawnLocation.Y + FMath::RandRange(MinWalkOffset, -Radius);
		LocationY = AdjustLocBoundaries(LocationY, CurrentLocation, Direction, 'Y');
	}
	else if (Direction == 1)
	{
		LocationY = SpawnLocation.Y + FMath::RandRange(MinWalkOffset, Radius);
		LocationY = AdjustLocBoundaries(LocationY, CurrentLocation, Direction, 'Y');
	}
	return (LocationY);
}

float	UBTTask_MoveRandomly::GetLocationXNonSpawnPoint(float LocationX, ACharacter *Character)
{
	float	CurrentLocation;
	float	Direction;

	CurrentLocation = Character->GetActorLocation().X;
	Direction = FMath::RandRange(0, 1);
	if (Direction == 0)
	{
		LocationX = CurrentLocation + FMath::RandRange(MinWalkOffset, -Radius);
		LocationX = CoordOnDirection0(LocationX, CurrentLocation, CurrentLocation + Radius, CurrentLocation - Radius);
	}
	else if (Direction == 1)
	{
		LocationX = CurrentLocation + FMath::RandRange(MinWalkOffset, Radius);
		LocationX = CoordOnDirection1(LocationX, CurrentLocation, CurrentLocation + Radius, CurrentLocation - Radius);
	}
	return (LocationX);
}

float	UBTTask_MoveRandomly::GetLocationYNonSpawnPoint(float LocationY, ACharacter* Character)
{
	float	CurrentLocation;
	float	Direction;

	CurrentLocation = Character->GetActorLocation().Y;
	Direction = FMath::RandRange(0, 1);
	if (Direction == 0)
	{
		LocationY = Character->GetActorLocation().Y + FMath::RandRange(MinWalkOffset, -Radius);
		LocationY = CoordOnDirection0(LocationY, CurrentLocation, CurrentLocation + Radius, CurrentLocation - Radius);
	}
	else if (Direction == 1)
	{
		LocationY = Character->GetActorLocation().Y + FMath::RandRange(MinWalkOffset, Radius);
		LocationY = CoordOnDirection1(LocationY, CurrentLocation, CurrentLocation + Radius, CurrentLocation - Radius);
	}
	return (LocationY);
}

void	UBTTask_MoveRandomly::GetLocationBoundaries()
{
	float		North;
	float		South;
	float		East;
	float		West;

	North = SpawnLocation.X + Radius;
	South = SpawnLocation.X - Radius;
	East = SpawnLocation.Y + Radius;
	West = SpawnLocation.Y - Radius;

	LocatBonds.North = North;
	LocatBonds.South = South;
	LocatBonds.East = East;
	LocatBonds.West = West;
}

void	UBTTask_MoveRandomly::DebugOptions(ACharacter* Character, FVector Location)
{
	if (bDisplayMoveToLocation)
	{
		FString Debug = FString::Printf(TEXT("%s Moving To: %s"), *Character->GetName(), *Location.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Debug);
	}
	if (bDisplayNewLocation)
		DrawDebugDirectionalArrow(Character->GetWorld(), Character->GetActorLocation(), Location, 1000.f, FColor::Red, false, 2.f,
								(uint8)0U, 20.f);
	if (bDisplaySphereRadius && !bLocationOnSpawnPoint)
		DrawDebugSphere(Character->GetWorld(), Character->GetActorLocation(), Radius + 200.f, 32, FColor::Purple, false, 3.f);
	if (bDisplaySphereRadius && bLocationOnSpawnPoint)
		DrawDebugSphere(Character->GetWorld(), SpawnLocation, Radius + 200.f, 32, FColor::Purple, false, 3.f);
	if (bDisplayBounds)
	{
		FString Debug = FString::Printf(TEXT("BOUNDS: North %s, South %s, East %s, West %s"),
			*FString::SanitizeFloat(LocatBonds.North), *FString::SanitizeFloat(LocatBonds.South),
			*FString::SanitizeFloat(LocatBonds.East), *FString::SanitizeFloat(LocatBonds.West));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Debug);
	}
}

bool	UBTTask_MoveRandomly::CheckBoundaries(float Location, float MaxBound, float MinBound)
{
	if (Location >= MinBound && Location <= MaxBound)
		return (true);
	return (false);
}

float	UBTTask_MoveRandomly::AdjustLocBoundaries(float Location, float CurrentLocation, int32 Direction, char Axis)
{
	float		LocationOffset;
	float		MaxBound;
	float		MinBound;

	LocationOffset = VerifyLocMinWalk(Location, CurrentLocation);
	MaxBound = SetBounds(Axis, "Max");
	MinBound = SetBounds(Axis, "Min");
	if (LocationOffset < MinWalkOffset || !CheckBoundaries(Location, MaxBound, MinBound))
	{
		if (Direction == 0)
			Location = CoordOnDirection0(Location, CurrentLocation, MaxBound, MinBound);
		else if (Direction == 1)
			Location = CoordOnDirection1(Location, CurrentLocation, MaxBound, MinBound);
	}

	if (bDisplayMoveToLocation)
	{
		FString Debug = FString::Printf(TEXT("Distance To Travel: %s || WalkMin = %s"), *FString::SanitizeFloat(VerifyLocMinWalk(Location, CurrentLocation)),
			*FString::SanitizeFloat(MinWalkOffset));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, Debug);
	}
	return (Location);
}

float	UBTTask_MoveRandomly::CoordOnDirection0(float Location, float CurrentLocation, float MaxBound, float MinBound)
{
	float		LocationOffset;

	LocationOffset = VerifyLocMinWalk(Location, CurrentLocation);
	while (LocationOffset < MinWalkOffset)
	{
		Location = Location - MinWalkOffset;
		LocationOffset = VerifyLocMinWalk(Location, CurrentLocation);
		if (!CheckBoundaries(Location, MaxBound, MinBound))
		{
			Location = Location + MinWalkOffset;
			break ;
		}
	}
	while (LocationOffset < MinWalkOffset)
	{
		Location = Location + MinWalkOffset;
		LocationOffset = VerifyLocMinWalk(Location, CurrentLocation);
		if (!CheckBoundaries(Location, MaxBound, MinBound))
			break ;
	}
	if (!CheckBoundaries(Location, MaxBound, MinBound))
		Location = MinBound;
	return (Location);
}

float	UBTTask_MoveRandomly::CoordOnDirection1(float Location, float CurrentLocation, float MaxBound, float MinBound)
{
	float		LocationOffset;

	LocationOffset = VerifyLocMinWalk(Location, CurrentLocation);
	while (LocationOffset < MinWalkOffset)
	{
		Location = Location + MinWalkOffset;
		LocationOffset = VerifyLocMinWalk(Location, CurrentLocation);
		if (!CheckBoundaries(Location, MaxBound, MinBound))
		{
			Location = Location - MinWalkOffset;
			break ;
		}

	}
	while (LocationOffset < MinWalkOffset)
	{
		Location = Location - MinWalkOffset;
		LocationOffset = VerifyLocMinWalk(Location, CurrentLocation);
		if (!CheckBoundaries(Location, MaxBound, MinBound))
			break ;
	}
	if (!CheckBoundaries(Location, MaxBound, MinBound))
		Location = MaxBound;
	return (Location);
}

float	UBTTask_MoveRandomly::VerifyLocMinWalk(float Location, float CurrentLocation)
{
	float	RelLocation;
	float	ReLCurrentLocation;
	float	Difference;

	RelLocation = FMath::Abs(Location);
	ReLCurrentLocation = FMath::Abs(CurrentLocation);
	Difference = 0;
	if (RelLocation > ReLCurrentLocation)
		Difference = RelLocation - ReLCurrentLocation;
	else if (RelLocation < ReLCurrentLocation)
		Difference = ReLCurrentLocation - RelLocation;
	return (Difference);
}

float	UBTTask_MoveRandomly::SetBounds(char Axis, FString Bound)
{
	if (Axis == 'X')
	{
		if (Bound == "Max")
			return (LocatBonds.North);
		if (Bound == "Min")
			return (LocatBonds.South);
	}
	else if (Axis == 'Y')
	{
		if (Bound == "Max")
			return (LocatBonds.East);
		if (Bound == "Min")
			return (LocatBonds.West);
	}
	return (0.f);
}

float	UBTTask_MoveRandomly::GetDistanceVal(float Location, float CurrentLocation)
{
	Location = FMath::Abs(Location);;
	CurrentLocation = FMath::Abs(Location);
	if (Location > CurrentLocation)
		return (Location - CurrentLocation);
	else if (Location < CurrentLocation)
		return (CurrentLocation - Location);
	return (0);
}

