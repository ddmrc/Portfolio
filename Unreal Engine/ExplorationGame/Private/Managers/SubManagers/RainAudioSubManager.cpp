// Code Created By Diego Demarco


#include "Managers/SubManagers/RainAudioSubManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URainAudioSubManager::URainAudioSubManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URainAudioSubManager::BeginPlay()
{
	Super::BeginPlay();

	if (AmbientRainAudio == nullptr)
	{
		TArray<AActor*> TempArr;

		UGameplayStatics::GetAllActorsOfClass(this, AAmbientSound::StaticClass(), TempArr);

		for (int i = 0; i < TempArr.Num(); i++)
		{
			if (TempArr.IsValidIndex(i))
			{
				if (TempArr[i]->Tags[0] == "AmbientRainAudio")
				{
					AmbientRainAudio = Cast<AAmbientSound>(TempArr[i]);
					TempArr.RemoveAt(i);
				}
			}
		}
	}
	
}


// Called every frame
void URainAudioSubManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OldSwitchParam != NewSwitchParam)
	{
		AmbianceRainSwitchValue.Broadcast((float)OldSwitchParam, (float)NewSwitchParam, AlphaSwitchParam);
		OldSwitchParam = NewSwitchParam;
	}
}

