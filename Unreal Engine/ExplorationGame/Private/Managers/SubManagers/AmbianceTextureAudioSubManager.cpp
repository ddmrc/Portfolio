// Code Created By Diego Demarco


#include "Managers/SubManagers/AmbianceTextureAudioSubManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAmbianceTextureAudioSubManager::UAmbianceTextureAudioSubManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAmbianceTextureAudioSubManager::BeginPlay()
{
	Super::BeginPlay();


	
		TArray<AActor*> TempArr;

		UGameplayStatics::GetAllActorsOfClass(this, AAmbientSound::StaticClass(), TempArr);

		for (int i = 0; i < TempArr.Num(); i++)
		{
			if (TempArr.IsValidIndex(i))
			{
				if (TempArr[i]->Tags[0] == "AmbientDroneSound")
				{
					if (DroneAmbientSound == nullptr)
					{
						DroneAmbientSound = Cast<AAmbientSound>(TempArr[i]);
						TempArr.RemoveAt(i);
					}
					if (DroneAmbientSound)
					{
						
					}

				}
				else if (TempArr[i]->Tags[0] == "AmbientRadiationSound")
				{
					if (RadiationAmbientSound == nullptr)
					{
						RadiationAmbientSound = Cast<AAmbientSound>(TempArr[i]);
						TempArr.RemoveAt(i);
					}
				}
			}
		}

	
}


// Called every frame
void UAmbianceTextureAudioSubManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

