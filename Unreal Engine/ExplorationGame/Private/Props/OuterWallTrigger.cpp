// Code Created By Diego Demarco


#include "Props/OuterWallTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOuterWallTrigger::AOuterWallTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOuterWallTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	}

	if (MainBoxMesh == nullptr)
	{
		if (GetComponentsByTag(UStaticMeshComponent::StaticClass(), "MainBox").IsValidIndex(0))
		{
			MainBoxMesh = Cast<UStaticMeshComponent>(GetComponentsByTag(UStaticMeshComponent::StaticClass(), "MainBox")[0]);
		
		}
	}

	

	for (int i = 0; i < TriggerPoints.Num();i++)
	{
		if (TriggerPoints.IsValidIndex(i))
		{
			FName TagToSearch = FName(*TriggerPoints[i].TagForTriggerPoint);
			
			TArray<UActorComponent*> TempCompArr = GetComponentsByTag(UStaticMeshComponent::StaticClass(), TagToSearch);
			
			if (TempCompArr.IsValidIndex(0))
			{

				FInternalTriggerSoundBind TempComponent;
				TempComponent.MeshComponent = Cast<UStaticMeshComponent>(TempCompArr[0]);

				TempComponent.MeshComponent->SetGenerateOverlapEvents(false);
				TempComponent.MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				TempComponent.MeshComponent->SetVisibility(false);


				TempComponent.SoundCue = TriggerPoints[i].SoundToSpawn;
				if (TempComponent.Attenuation)
				{
					TempComponent.Attenuation = TriggerPoints[i].AttenuationSettings;
				}
				
				TempComponent.SoundLocationOffset = TriggerPoints[i].SoundLocationOffset;
				TempComponent.RandomRangeOffset = TriggerPoints[i].RandomRangeOffset;
				TempComponent.EnableRandomSoundSpawn = TriggerPoints[i].EnableRandomSoundSpawn;
				TempComponent.bTriggerAtSpecificLocation = TriggerPoints[i].TriggerAtSpecificLocation;

				InternalTriggerSoundBindArr.Add(TempComponent);
			}
		}
	}
	
	

}

// Called every frame
void AOuterWallTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	PlayerDetectionWithinTriggerArea();

	if (bIsPlayerIn)
	{

		int i = 0;
		TriggerSound(TriggerSound1, i);
		
		i = 1;
		TriggerSound(TriggerSound2, i);

		i = 2;
		TriggerSound(TriggerSound3, i);

		i = 3;
		TriggerSound(TriggerSound4, i);

		i = 4;
		TriggerSound(TriggerSound5, i);

		i = 5;
		TriggerSound(TriggerSound6, i);

		i = 6;
		TriggerSound(TriggerSound7, i);


		
	
		
	
	}

	//if (GetComponentsByTag(UBoxComponent::StaticClass(), "Trigger1"))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Good"));
	//}


}

void AOuterWallTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (OtherActor == Player)
	{
		bIsPlayerIn = true;

		SetProperBoxExtent();
		SetProperRelativeStartPoint();
		SetPlayerOffset();
		SetTriggersLocation();
		
		
	}



	
}

void AOuterWallTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (OtherActor == Player)
	{
		bIsPlayerIn = false;
		PlayerDistanceOffset = 0.f;
	}
}

void AOuterWallTrigger::PlayerDetectionWithinTriggerArea()
{
	if (bIsPlayerIn)
	{
		if (!OverrideWithAxisY)
		{
			

			PlayerDistanceTraveled = FMath::Abs(PlayerCharacter->GetActorLocation().X - RefLocationPlayer + PlayerDistanceOffset);

			PlayerDotProduct = (PlayerDistanceTraveled - BoxExtenteDistance)/ BoxExtenteDistance;
			PlayerDotProduct = FMath::Clamp(PlayerDotProduct, -1.f, 1.f) +1.f;


			
		}

		else
		{
			PlayerDistanceTraveled = FMath::Abs(PlayerCharacter->GetActorLocation().Y - RefLocationPlayer + PlayerDistanceOffset);

			PlayerDotProduct = (PlayerDistanceTraveled - BoxExtenteDistance) / BoxExtenteDistance;
			PlayerDotProduct = FMath::Clamp(PlayerDotProduct, -1.f, 1.f);


		}


		if (GEngine && DebugLocation)
		{


			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("Dot Product: %f"), PlayerDotProduct));
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("DistanceInsideBox: %f"), PlayerDistanceTraveled));

		}



	


	}
	
	
}

void AOuterWallTrigger::SetProperBoxExtent() 
{
	if (!OverrideWithAxisY)
	{
		BoxExtenteDistance = MainBoxMesh->Bounds.GetBox().GetExtent().X;

	}
	else
	{
		BoxExtenteDistance = MainBoxMesh->Bounds.GetBox().GetExtent().Y;
	
	}

}

void AOuterWallTrigger::SetProperRelativeStartPoint() 
{
	

	if (!OverrideWithAxisY)
	{
		PlayerForwardVector = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorForwardVector().X;
		RefLocationPlayer = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation().X;

		if (FMath::IsNegativeFloat(PlayerForwardVector))
		{
			RelativeBoxStartingLocationA = GetActorLocation().X + MainBoxMesh->Bounds.GetBox().GetExtent().X;
			RelativeBoxStartingLocationB = GetActorLocation().X - MainBoxMesh->Bounds.GetBox().GetExtent().X;
		}
		else
		{
			RelativeBoxStartingLocationA = GetActorLocation().X - MainBoxMesh->Bounds.GetBox().GetExtent().X;
			RelativeBoxStartingLocationB = GetActorLocation().X + MainBoxMesh->Bounds.GetBox().GetExtent().X;
		}
	}
	else
	{
		RefLocationPlayer = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation().Y;
		PlayerForwardVector = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorForwardVector().Y;


		if (FMath::IsNegativeFloat(PlayerForwardVector))
		{
			RelativeBoxStartingLocationA = GetActorLocation().Y + MainBoxMesh->Bounds.GetBox().GetExtent().Y;
			RelativeBoxStartingLocationB = GetActorLocation().Y - MainBoxMesh->Bounds.GetBox().GetExtent().Y;
		}
		else
		{
			RelativeBoxStartingLocationA = GetActorLocation().Y - MainBoxMesh->Bounds.GetBox().GetExtent().Y;
			RelativeBoxStartingLocationB = GetActorLocation().Y + MainBoxMesh->Bounds.GetBox().GetExtent().Y;
		}
	}

}

void AOuterWallTrigger::SetPlayerOffset()
{
	if (!OverrideWithAxisY)
	{
		if (FMath::IsNearlyEqual(PlayerCharacter->GetActorLocation().X, RelativeBoxStartingLocationA, 100.f) ||
			FMath::IsNearlyEqual(PlayerCharacter->GetActorLocation().X, RelativeBoxStartingLocationB, 100.f))
		{
			PlayerDistanceOffset = 0.f;
		}
		else
		{
			PlayerDistanceOffset = PlayerCharacter->GetActorLocation().X - RelativeBoxStartingLocationA;
		}
	}
	else
	{
		if (FMath::IsNearlyEqual(PlayerCharacter->GetActorLocation().Y, RelativeBoxStartingLocationA, 100.f) ||
			FMath::IsNearlyEqual(PlayerCharacter->GetActorLocation().Y, RelativeBoxStartingLocationB, 100.f))
		{
			PlayerDistanceOffset = 0.f;
		}
		else
		{
			//float DistanceToPointA = FMath::Abs(PlayerCharacter->GetActorLocation().Y - RelativeBoxStartingLocationA);
			//float DistanceToPointB = FMath::Abs(PlayerCharacter->GetActorLocation().Y - RelativeBoxStartingLocationB);

			PlayerDistanceOffset = PlayerCharacter->GetActorLocation().Y - RelativeBoxStartingLocationA;

		}
	}

}

void AOuterWallTrigger::SetTriggersLocation()
{

	for (int i = 0; i < InternalTriggerSoundBindArr.Num();i++)
	{
		if (InternalTriggerSoundBindArr.IsValidIndex(i) && !InternalTriggerSoundBindArr[i].bTriggerAtSpecificLocation)
		{

			if (!OverrideWithAxisY)
			{
				//this number gets the real scale of the Relative Location in World in X Axis.
				float MagicScaleNumber = 35.5f;
				if (FMath::IsNegativeFloat(PlayerForwardVector))
				{
					float TriggerLocation = BoxExtenteDistance - (InternalTriggerSoundBindArr[i].MeshComponent->GetRelativeLocation().X * MagicScaleNumber);
					
					FFinalTriggerPoint TempStruct;
					TempStruct.TriggerPoint = TriggerLocation;
					TempStruct.SoundCue = InternalTriggerSoundBindArr[i].SoundCue;
					TempStruct.Attenuation = InternalTriggerSoundBindArr[i].Attenuation;
					TempStruct.SoundLocationOffset = InternalTriggerSoundBindArr[i].SoundLocationOffset;
					TempStruct.EnableRandomSoundSpawn = InternalTriggerSoundBindArr[i].EnableRandomSoundSpawn;
					TempStruct.RandomRangeOffset = InternalTriggerSoundBindArr[i].RandomRangeOffset;

					TriggerLocations.Add(TempStruct);
				}
				else
				{
					float TriggerLocation = BoxExtenteDistance + (InternalTriggerSoundBindArr[i].MeshComponent->GetRelativeLocation().X * MagicScaleNumber);
					
					FFinalTriggerPoint TempStruct;
					TempStruct.TriggerPoint = TriggerLocation;
					TempStruct.SoundCue = InternalTriggerSoundBindArr[i].SoundCue;
					TempStruct.Attenuation = InternalTriggerSoundBindArr[i].Attenuation;
					TempStruct.SoundLocationOffset = InternalTriggerSoundBindArr[i].SoundLocationOffset;
					TempStruct.EnableRandomSoundSpawn = InternalTriggerSoundBindArr[i].EnableRandomSoundSpawn;
					TempStruct.RandomRangeOffset = InternalTriggerSoundBindArr[i].RandomRangeOffset;

					TriggerLocations.Add(TempStruct);
				}
			}
			else
			{
				//this number gets the real scale of the Relative Location in World in Y Axis.
				float MagicScaleNumber = 16.f;

				if (FMath::IsNegativeFloat(PlayerForwardVector))
				{
					float TriggerLocation = BoxExtenteDistance - (InternalTriggerSoundBindArr[i].MeshComponent->GetRelativeLocation().Y * MagicScaleNumber);
					
					FFinalTriggerPoint TempStruct;
					TempStruct.TriggerPoint = TriggerLocation;
					TempStruct.SoundCue = InternalTriggerSoundBindArr[i].SoundCue;
					TempStruct.Attenuation = InternalTriggerSoundBindArr[i].Attenuation;
					TempStruct.SoundLocationOffset = InternalTriggerSoundBindArr[i].SoundLocationOffset;
					TempStruct.EnableRandomSoundSpawn = InternalTriggerSoundBindArr[i].EnableRandomSoundSpawn;
					TempStruct.RandomRangeOffset = InternalTriggerSoundBindArr[i].RandomRangeOffset;

					TriggerLocations.Add(TempStruct);

				}
				else
				{
					float TriggerLocation = BoxExtenteDistance + (InternalTriggerSoundBindArr[i].MeshComponent->GetRelativeLocation().Y * MagicScaleNumber);
				
					FFinalTriggerPoint TempStruct;
					TempStruct.TriggerPoint = TriggerLocation;
					TempStruct.SoundCue = InternalTriggerSoundBindArr[i].SoundCue;
					TempStruct.Attenuation = InternalTriggerSoundBindArr[i].Attenuation;
					TempStruct.SoundLocationOffset = InternalTriggerSoundBindArr[i].SoundLocationOffset;
					TempStruct.EnableRandomSoundSpawn = InternalTriggerSoundBindArr[i].EnableRandomSoundSpawn;
					TempStruct.RandomRangeOffset = InternalTriggerSoundBindArr[i].RandomRangeOffset;

					TriggerLocations.Add(TempStruct);

				}
			}


		}
		else if (InternalTriggerSoundBindArr.IsValidIndex(i) && InternalTriggerSoundBindArr[i].bTriggerAtSpecificLocation)
		{
			// Trigger with 2D Vector
		}
	}

}

void AOuterWallTrigger::TriggerSound(bool bActivated,float index)
{
	if (bActivated && TriggerLocations.IsValidIndex(index))
	{
		//For Location Get a RandomLocation Around The Player
		FVector LocationForSound = PlayerCharacter->GetActorLocation() + TriggerLocations[index].SoundLocationOffset;

		if (TriggerLocations[index].EnableRandomSoundSpawn)
		{
			FVector RandLocation = PlayerCharacter->GetActorLocation() + TriggerLocations[index].RandomRangeOffset;

			LocationForSound = FVector(
				FMath::RandRange(LocationForSound.X, RandLocation.X),
				FMath::RandRange(LocationForSound.Y, RandLocation.Y),
				FMath::RandRange(LocationForSound.Z, RandLocation.Z));

		}

		PlayTriggerSoundAtLocation(TriggerLocations[index], LocationForSound, 0.f);
	
	}
}

void AOuterWallTrigger::PlayTriggerSoundAtLocation(FFinalTriggerPoint Trigger, FVector SoundLocation, float StartTime)
{
	if (FMath::IsNearlyEqual(PlayerDistanceTraveled, Trigger.TriggerPoint, 50.f))
	{
		UGameplayStatics::PlaySoundAtLocation(this, Trigger.SoundCue,SoundLocation, Trigger.SoundCue->VolumeMultiplier,
			Trigger.SoundCue->PitchMultiplier, StartTime, Trigger.Attenuation);

	}
}

