// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "MyEnemyController.generated.h"

UENUM()
enum class ESimpleAIState : uint8
{
	Idle,
	Roaming,
	ChasingPlayer,
};

UCLASS()
class SOUNDDEMO_TWO_API AMyEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

public:

	//Used For AI Perception
	FGenericTeamId TeamID;
	
	ESimpleAIState AIState;

	virtual void ChasingPlayerBehaviour();
};
