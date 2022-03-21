// Code Created By Diego Demarco


#include "Enemy/AITask/Task_MeleeAttack.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Minions/MinionMeleeBase.h"
#include "Kismet/GameplayStatics.h"


UTask_MeleeAttack::UTask_MeleeAttack(const FObjectInitializer& objectInitializer)
{
	NodeName = "MeleeAttack";
	bNotifyTick = true;

}

EBTNodeResult::Type UTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Super::ExecuteTask(OwnerComp, NodeMemory);
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	AMinionMeleeBase*Character = Cast<AMinionMeleeBase>(OwnerComp.GetAIOwner()->GetCharacter());
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