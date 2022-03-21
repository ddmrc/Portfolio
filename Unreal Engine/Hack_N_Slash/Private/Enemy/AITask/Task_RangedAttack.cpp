// Code Created By Diego Demarco


#include "Enemy/AITask/Task_RangedAttack.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Minions/MinionRangedBase.h"
#include "Kismet/GameplayStatics.h"


UTask_RangedAttack::UTask_RangedAttack(const FObjectInitializer& objectInitializer)
{
	NodeName = "RangedAttack";
	bNotifyTick = true;

}

EBTNodeResult::Type UTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Super::ExecuteTask(OwnerComp, NodeMemory);
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	AMinionRangedBase* Character = Cast<AMinionRangedBase>(OwnerComp.GetAIOwner()->GetCharacter());
	ACharacter* Player = nullptr;
	if (OwnerComp.GetWorld())
		Player = UGameplayStatics::GetPlayerCharacter(OwnerComp.GetWorld(), 0);

	if (Player && Character)
	{
		FVector CharLocation = Character->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		if (CharLocation.Equals(PlayerLocation, AttackRange) && !Character->bHasAttacked)
		{
			Character->AttackPlayer();
			NodeResult = EBTNodeResult::Succeeded;
		}
		else
			NodeResult = EBTNodeResult::Succeeded;
	}
	else
		NodeResult = EBTNodeResult::Succeeded;


	return NodeResult;

}