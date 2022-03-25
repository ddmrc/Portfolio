// Written by Diego Demarco *2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_MoveToTarget.generated.h"

UCLASS()
class PORTFOLIO_API AActor_MoveToTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor_MoveToTarget();

public:	
	//The Character that MovesTo this Target
	//Put exact ID NAME as BP In World. Uses GetName()
	UPROPERTY(EditAnywhere, Category = "Owner")
	FString			OwningCharacterName;
	//In Which Order Character Will Arrive Here.
	UPROPERTY(EditAnywhere, Category = "Owner")
	int32			ArrivalOrder = 0;
	//Number Of Targets For Character in World
	int32			NumberOfTargets;
	//Counter for order
	bool			bHasBeenUsed = false;
};

