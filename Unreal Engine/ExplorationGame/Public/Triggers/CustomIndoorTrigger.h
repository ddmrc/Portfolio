// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomIndoorTrigger.generated.h"

UCLASS()
class RAINPROTOTYPE_API ACustomIndoorTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomIndoorTrigger();

	ACharacter* PlayerCharacter = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
