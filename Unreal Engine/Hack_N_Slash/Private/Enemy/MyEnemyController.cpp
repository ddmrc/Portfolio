// Code Created By Diego Demarco


#include "Enemy/MyEnemyController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/MyEnemyCharacterBase.h"



void AMyEnemyController::BeginPlay()
{
	Super::BeginPlay();

	//Setting All Enemies to AIPerception Team 8
	TeamID = 8;
	SetGenericTeamId(TeamID);

	if (UAIPerceptionComponent* ThisPerceptionComponent = GetPerceptionComponent())
	{
		ThisPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMyEnemyController::TargetPerceptionUpdated);
		AIState = ESimpleAIState::Roaming;
		GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("SimpleAIState")), (uint8)AIState);

	}


}

void AMyEnemyController::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	
	if (Actor == UGameplayStatics::GetPlayerCharacter(this, 0) && Stimulus.WasSuccessfullySensed())
	{
		if (AIState != ESimpleAIState::ChasingPlayer)
		{
			AIState = ESimpleAIState::ChasingPlayer;
			GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("SimpleAIState")), (uint8)AIState);

			float UpdateSpeed = 0.5f;
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyEnemyController::ChasingPlayerBehaviour, UpdateSpeed, true);
		}

	}
}

void AMyEnemyController::ChasingPlayerBehaviour()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!GetBlackboardComponent()->GetValueAsVector(FName(TEXT("LocationToMove"))).Equals(Player->GetActorLocation(), 50.f))
	{
		GetBlackboardComponent()->SetValueAsVector(FName(TEXT("LocationToMove")), Player->GetActorLocation());
		AMyEnemyCharacterBase* EnemyCharacter = Cast<AMyEnemyCharacterBase>(GetCharacter());
		/*if (EnemyCharacter)
			EnemyCharacter->SetHealthBarVisibility(true);*/
	}
}