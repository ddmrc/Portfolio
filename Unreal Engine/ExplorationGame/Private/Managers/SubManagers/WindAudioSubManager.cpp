// Code Created By Diego Demarco


#include "Managers/SubManagers/WindAudioSubManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWindAudioSubManager::UWindAudioSubManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWindAudioSubManager::BeginPlay()
{
	Super::BeginPlay();

	if (AmbientWindAudio == nullptr)
	{
		TArray<AActor*> TempArr;

		UGameplayStatics::GetAllActorsOfClass(this, AAmbientSound::StaticClass(), TempArr);

		for (int i = 0; i < TempArr.Num(); i++)
		{
			if (TempArr.IsValidIndex(i))
			{
				if (TempArr[i]->Tags[0] == "AmbientWindAudio")
				{
					AmbientWindAudio = Cast<AAmbientSound>(TempArr[i]);
					TempArr.RemoveAt(i);
				}
			}
		}
	}
	
}


// Called every frame
void UWindAudioSubManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (OldSwitchParam != NewSwitchParam)
	{
		AmbianceWindSwitchValue.Broadcast((float)OldSwitchParam, (float)NewSwitchParam, AlphaSwitchParam);
		OldSwitchParam = NewSwitchParam;
	}
	
}

