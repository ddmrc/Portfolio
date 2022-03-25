// Written by Diego Demarco *2022.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "AI/BTTasks/Locomotion/Actor_MoveToTarget.h"
#include "BTTask_MoveToTarget.generated.h"

UCLASS()
class AOS_PROTOTYPE_API UBTTask_MoveToTarget : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UBTTask_MoveToTarget(const FObjectInitializer& objectInitializer);

public:
	//Name of the BlackBoard Key Vector
	UPROPERTY(EditAnywhere, Category = "Location")
	FString							BB_KeyLocationName;
	//Key for BlackBoard
	FVector							MoveToLocation = FVector::ZeroVector;
	//TArray For Targets
	TArray <AMoveToTarget*>			Targets;
	//Focused Targer
	AMoveToTarget					*Target;

protected:
	virtual	EBTNodeResult::Type		ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//Get Location From Focus Target
	FVector							GetMoveToLocations(AMoveToTarget* Target, ACharacter* Character);
	//Scan All Targets
	void							GetAllTargets(ACharacter *Character);
	//Reorder Targets Arr
	void							ReorderTargets();
	//Get Focus Target
	AMoveToTarget					*GetCorrectTarget(ACharacter *Character);
	//Reset MoveTo Cycle
	void							ResetTargets(ACharacter *Character);
};

