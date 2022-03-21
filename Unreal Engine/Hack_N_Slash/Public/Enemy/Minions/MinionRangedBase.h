// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Enemy/MyEnemyCharacterBase.h"
#include "Enemy/Projectiles/RangedMinionProjectile.h"
#include "MinionRangedBase.generated.h"

/**
 * 
 */
UCLASS()
class SOUNDDEMO_TWO_API AMinionRangedBase : public AMyEnemyCharacterBase
{
	GENERATED_BODY()
public:
	AMinionRangedBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime)override;

	bool bIsAttacking = false;

	UFUNCTION(BlueprintCallable, Category = "Attack")
		virtual void AttackPlayer() override;

	TSubclassOf<ARangedMinionProjectile> Projectile;
};
