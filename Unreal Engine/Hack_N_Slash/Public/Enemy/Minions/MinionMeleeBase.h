// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Enemy/MyEnemyCharacterBase.h"
#include "MinionMeleeBase.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API AMinionMeleeBase : public AMyEnemyCharacterBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Attack")
		virtual void AttackPlayer() override;

	virtual void BeginPlay() override;

	
};
