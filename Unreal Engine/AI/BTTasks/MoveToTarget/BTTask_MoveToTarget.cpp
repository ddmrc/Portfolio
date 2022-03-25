// Written by Diego Demarco *2022.

#include "AI/BTTasks/Locomotion/BTTask_MoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "AIController.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget(const FObjectInitializer& objectInitializer)
{
	NodeName = "MoveToTarget";
	bNotifyTick = true;
}

EBTNodeResult::Type	UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		if (Targets.Num() == 0)
			GetAllTargets(Character);
		Target = GetCorrectTarget(Character);
		if (Target)
			MoveToLocation = GetMoveToLocations(Target, Character);
		BlackboardComp->SetValueAsVector(FName(BB_KeyLocationName), MoveToLocation);
	}

	if (!MyMemory->bWaitingForPath)
	{
		NodeResult = PerformMoveTask(OwnerComp, NodeMemory);
		MoveToLocation = FVector::ZeroVector;
	}
	return (NodeResult);
}

FVector	UBTTask_MoveToTarget::GetMoveToLocations(AMoveToTarget* CurrentTarget, ACharacter* Character)
{
	FVector		Location;

	Location = FVector(CurrentTarget->GetActorLocation().X, CurrentTarget->GetActorLocation().Y,
					Character->GetActorLocation().Z);
	return (Location);
}

void	UBTTask_MoveToTarget::GetAllTargets(ACharacter* Character)
{
	TArray<AActor*> 	Temp;

	UGameplayStatics::GetAllActorsOfClass(Character->GetWorld(), AMoveToTarget::StaticClass(), Temp);
	for (int i = 0; i < Temp.Num(); i++)
	{
		if (Temp.IsValidIndex(i) && Cast<AMoveToTarget>(Temp[i]))
		{
			if (Cast<AMoveToTarget>(Temp[i])->OwningCharacterName == Character->GetName())
				Targets.Add(Cast<AMoveToTarget>(Temp[i]));
		}
	}
	ReorderTargets();
}

void	UBTTask_MoveToTarget::ReorderTargets()
{
	AMoveToTarget*		Temp;

	Temp = nullptr;
	for (int i = 0; i < Targets.Num(); i++)
	{
		for (int j = i + 1; j < Targets.Num(); j++)
		{
			if (Targets.IsValidIndex(i) && Targets.IsValidIndex(j))
			{
				if (Targets[i]->ArrivalOrder > Targets[j]->ArrivalOrder)
				{
					Temp = Targets[i];
					Targets[i] = Targets[j];
					Targets[j] = Temp;
				}
			}
		}
	}
}

AMoveToTarget *UBTTask_MoveToTarget::GetCorrectTarget(ACharacter *Character)
{
	int32			TargetIndex;
	AMoveToTarget		*CurrentTarget;

	TargetIndex = 0;
	if (Targets.IsValidIndex(0))
		TargetIndex = Targets[0]->ArrivalOrder;
	CurrentTarget = nullptr;
	for (int i = 0; i < Targets.Num(); i++)
	{
		if (Targets.IsValidIndex(i) && Targets[i]->ArrivalOrder == TargetIndex)
		{
			if (!Targets[i]->bHasBeenUsed)
			{
				Targets[i]->bHasBeenUsed = true;
				CurrentTarget = Targets[i];
				break ;
			}
			TargetIndex++;
			Targets.RemoveAt(i, 1, true);
			i = -1;
		}
	}
	if (Targets.Num() <= 1)
		ResetTargets(Character);
	return (CurrentTarget);
}

void	UBTTask_MoveToTarget::ResetTargets(ACharacter *Character)
{
	Targets.Empty();
	GetAllTargets(Character);
	for (int i = 0; i < Targets.Num(); i++)
	{
		if (Targets.IsValidIndex(i))
			Targets[i]->bHasBeenUsed = false;
	}
}

