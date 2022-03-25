// Written by Diego Demarco *2022.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveRandomly.generated.h"

USTRUCT() struct FLocationBounds
{
	GENERATED_BODY()

	UPROPERTY()
	float 		North;
	UPROPERTY()
	float 		South;
	UPROPERTY()
	float		East;
	UPROPERTY()
	float		West;
};

UCLASS()
class PORTFOLIO_API UBTTask_MoveRandomly : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTask_MoveRandomly(const FObjectInitializer& objectInitializer);

public:
	//Random Location Sphere Radius
	UPROPERTY(EditAnywhere, Category = "Random Location")
	float			Radius = 500.0f;
	//Minimun Distance Offset When Picking New Location
	UPROPERTY(EditAnywhere, Category = "Random Location")
	float			MinWalkOffset = 10.0f;
	//Name of the BlackBoard Key Vector
	UPROPERTY(EditAnywhere, Category = "Random Location")
	FString			BB_KeyLocationName;
	//TRUE: Always Uses Character Spawn Location
	//FALSE: It Takes Current Character Location
	UPROPERTY(EditAnywhere, Category = "Random Location")
	bool			bLocationOnSpawnPoint = true;
	//Key for BlackBoard
	FVector			MoveToLocation = FVector::ZeroVector;
	//Character Spawn Locations
	FVector			SpawnLocation = FVector::ZeroVector;
	//SpawnLocationBoundaries
	FLocationBounds 	LocatBonds;
	//Display Move To Location Vector
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool			bDisplayMoveToLocation = false;
	//Display Sphere Radius
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool			bDisplaySphereRadius = false;
	//Display Sphere Radius
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool			bDisplayNewLocation = false;
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool			bDisplayBounds = false;

protected:

	virtual		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//Select Random Location Point
	FVector		GetRandLocation(UBehaviorTreeComponent& OwnerComp);
	//Get Boundaries if bLocationOnSpawnPoint = true
	void		GetLocationBoundaries();
	//If bLocationOnSpawnPoint = true Get LocationX
	float		GetLocationXSpawnPoint(float LocationX);
	//If bLocationOnSpawnPoint = true Get LocationY
	float		GetLocationYSpawnPoint(float LocationY);
	//If bLocationOnSpawnPoint = false Get LocationX
	float		GetLocationXNonSpawnPoint(float LocationX, ACharacter* Character);
	//If bLocationOnSpawnPoint = false Get LocationY
	float		GetLocationYNonSpawnPoint(float LocationY, ACharacter* Character);
	//Check if Location in Bonds
	bool		CheckBoundaries(float Location, float MaxBound, float MinBound);
	//Check if Location in Bonds
	float		AdjustLocBoundaries(float Location, float CurrentLocation, int32 Direction, char Axis);
	//Verify Location with MinWalkDistance
	float		VerifyLocMinWalk(float Location, float CurrentLocation);
	//Set Bounds
	float		SetBounds(char Axis, FString Bound);
	//Location on Direction0
	float		CoordOnDirection0(float Location, float CurrentLocation, float MaxBound, float MinBound);
	//Location on Direction1
	float		CoordOnDirection1(float Location, float CurrentLocation, float MaxBound, float MinBound);
	//Check if Location is valid
	float		GetDistanceVal(float Location, float CurrentLocation);
	//Debug Options
	void		DebugOptions(ACharacter* Character, FVector Location);
};

