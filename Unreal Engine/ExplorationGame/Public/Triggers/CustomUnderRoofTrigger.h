// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomUnderRoofTrigger.generated.h"

UCLASS()
class RAINPROTOTYPE_API ACustomUnderRoofTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomUnderRoofTrigger();

protected:

	ACharacter* PlayerCharacter = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
