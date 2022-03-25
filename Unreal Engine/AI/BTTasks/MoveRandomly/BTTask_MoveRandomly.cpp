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
	EBTNodeResult::Type			NodeResult;
	FBTMoveToTaskMemory			*MyMemory;
	AAIController				*Controller;
	UBlackboardComponent			*BlackboardComp;
	ACharacter				*Character;

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

	if (NodeResult == EBTNodeResult::InProgress && bObserveBlackboardValue)
	{
		//Set customized logic here for approaching objects if needed
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
		LocationX = GetLocationXSpawnPoint(LocationX);
		LocationY = GetLocationYSpawnPoint(LocationY);
	}
	else
	{
		LocationX = GetLocationXNonSpawnPoint(LocationX, Character);
		LocationY = GetLocationYNonSpawnPoint(LocationY, Character);
	}
	LocationZ = Character->GetActorLocation().Z;

	DebugOptions(Character, (FVector(LocationX, LocationY, LocationZ)));
	return (FVector(LocationX, LocationY, LocationZ));
}

float	UBTTask_MoveRandomly::GetLocationXSpawnPoint(float LocationX)
{
	float		CurrentLocation;
	int32		Direction;
	int32		LoopSafeguard;
	bool		bIsInRange;

	CurrentLocation = LocationX;
	LoopSafeguard = 0;
	bIsInRange = false;
	//Make sure conditions are met before submitting Coordinate
	while (!bIsInRange || LoopSafeguard < 5000)
	{
		//Allows to alternate directions
		Direction = FMath::RandRange(0, 1);
		if (Direction == 0)
		{
			LocationX = SpawnLocation.X + FMath::RandRange(CurrentLocation + MinWalkOffset, -Radius);
			bIsInRange = CheckBoundaries(LocationX, LocatBonds.North, LocatBonds.South);
		}
		else if (Direction == 1)
		{
			LocationX = SpawnLocation.X + FMath::RandRange(CurrentLocation + MinWalkOffset, Radius);
			bIsInRange = CheckBoundaries(LocationX, LocatBonds.North, LocatBonds.South);
		}
		LoopSafeguard++;
	}
	return (LocationX);
}

float	UBTTask_MoveRandomly::GetLocationYSpawnPoint(float LocationY)
{
	float		CurrentLocation;
	int32		Direction;
	int32		LoopSafeguard;
	bool		bIsInRange;

	CurrentLocation = LocationY;
	LoopSafeguard = 01;
	bIsInRange = false;
	//Make sure conditions are met before submitting Coordinate
	while (!bIsInRange || LoopSafeguard < 5000)
	{
		//Allows to alternate directions
		Direction = FMath::RandRange(0, 1);
		if (Direction == 0)
		{
			LocationY = SpawnLocation.Y + FMath::RandRange(MinWalkOffset, -Radius);
			bIsInRange = CheckBoundaries(LocationY, LocatBonds.East, LocatBonds.West);
		}
		else if (Direction == 1)
		{
			LocationY = SpawnLocation.Y + FMath::RandRange(MinWalkOffset, Radius);
			bIsInRange = CheckBoundaries(LocationY, LocatBonds.East, LocatBonds.West);
		}
		LoopSafeguard++;
	}
	return (LocationY);
}

float	UBTTask_MoveRandomly::GetLocationXNonSpawnPoint(float LocationX, ACharacter *Character)
{
	float	Direction;

	Direction = FMath::RandRange(0, 1);
	if (Direction == 0)
		LocationX = Character->GetActorLocation().X + FMath::RandRange(MinWalkOffset, -Radius);
	else if (Direction == 1)
		LocationX = Character->GetActorLocation().X + FMath::RandRange(MinWalkOffset, Radius);
	return (LocationX);
}

float	UBTTask_MoveRandomly::GetLocationYNonSpawnPoint(float LocationY, ACharacter* Character)
{
	float	Direction;

	Direction = FMath::RandRange(0, 1);
	if (Direction == 0)
		LocationY = Character->GetActorLocation().Y + FMath::RandRange(MinWalkOffset, -Radius);
	else if (Direction == 1)
		LocationY = Character->GetActorLocation().Y + FMath::RandRange(MinWalkOffset, Radius);
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
		DrawDebugSphere(Character->GetWorld(), Character->GetActorLocation(), Radius, 32, FColor::Purple, false, 3.f);
	if (bDisplaySphereRadius && bLocationOnSpawnPoint)
		DrawDebugSphere(Character->GetWorld(), SpawnLocation, Radius, 32, FColor::Purple, false, 3.f);
	if (bDisplayBounds)
	{
		FString Debug = FString::Printf(TEXT("BOUNDS: North %s, South %s, East %s, West %s"),
			*FString::SanitizeFloat(LocatBonds.North), *FString::SanitizeFloat(LocatBonds.South),
			*FString::SanitizeFloat(LocatBonds.East), *FString::SanitizeFloat(LocatBonds.West));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Debug);
	}
}

bool	UBTTask_MoveRandomly::CheckBoundaries(float Location, float MaxBond, float MinBond)
{
	if (Location >= MinBond && Location <= MaxBond)
		return (true);
	return (false);
}

