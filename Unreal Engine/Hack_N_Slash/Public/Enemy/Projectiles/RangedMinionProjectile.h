// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangedMinionProjectile.generated.h"

UCLASS()
class SOUNDDEMO_TWO_API ARangedMinionProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangedMinionProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	ACharacter* Player;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere)
	float DamageToPlayer = 40.f;

	bool bEmergencyDestroy = false;

};
