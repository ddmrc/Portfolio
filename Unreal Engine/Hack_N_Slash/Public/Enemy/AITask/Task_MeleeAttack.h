// Code Created By Diego Demarco
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API UTask_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Distance")
		float AttackRange = 200.f;

	UTask_MeleeAttack(const FObjectInitializer& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
