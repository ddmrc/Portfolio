// Code Created By Diego Demarco


#include "Components/Audio/CustomSpotAudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"



void UCustomSpotAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	bAllowSpatialization = true;
	bAutoActivate = false;


	if (LoadSoundOnStart && CUE_OnStartLoad && !Sound)
	{
		SetSound(CUE_OnStartLoad);
	}

	if (!AttenuationSettings)
	{
		AttenuationSettings = Attenuation_OnStartLoad;
	}

	if (PhysicalMaterialsToScanFor.Num() < 1 && PM_OnStartLoad.Num() > 0)
	{
		for (int i = 0; i < PM_OnStartLoad.Num(); i++)
		{
			if (PM_OnStartLoad.IsValidIndex(i))
			{
				PhysicalMaterialsToScanFor.Add(PM_OnStartLoad[i]);
			}
		}
	}

}

int32 UCustomSpotAudioComponent::ScanAndReturnMaterialSwitch(UMeshComponent* MeshComponent)
{
	if (MeshComponent)
	{
		TArray<UMaterialInterface*>TempMaterialsArr = MeshComponent->GetMaterials();
		TArray<UPhysicalMaterial*> TempPhysicalMaterialsArr;

		for (int i = 0; i < TempMaterialsArr.Num(); i++)
		{
			if (TempMaterialsArr.IsValidIndex(i))
			{
				for (int j = 0; j < PhysicalMaterialsToScanFor.Num(); j++)
				{
					if (PhysicalMaterialsToScanFor.IsValidIndex(j) &&
						TempMaterialsArr[i]->GetPhysicalMaterial()->GetName() == PhysicalMaterialsToScanFor[j]->GetName())
					{
						TempPhysicalMaterialsArr.Add(TempMaterialsArr[i]->GetPhysicalMaterial());
					}
				}

			}
		}
		
		for (int i = 0;i < TempPhysicalMaterialsArr.Num(); i++)
		{
			if (TempPhysicalMaterialsArr.IsValidIndex(i))
			{

				if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Plastic")
				{
					return (int32)EMaterialType::Plastic;
				}

				else if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Vegetation")
				{
					return (int32)EMaterialType::Vegetation;
				}

				else if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Metal")
				{

					for (int n = 0;n < TempPhysicalMaterialsArr.Num(); n++)
					{
						if (TempPhysicalMaterialsArr[n]->GetName() == "PM_Glass")
						{
							return (int32)EMaterialType::MetalGlass;
						}
					}

					return (int32)EMaterialType::Metal;
				}

				else if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Glass")
				{
					for (int n = 0; n < TempPhysicalMaterialsArr.Num(); n++)
					{
						if (TempPhysicalMaterialsArr[n]->GetName() == "PM_Metal")
						{
							return (int32)EMaterialType::MetalGlass;
						}
					}
					return (int32)EMaterialType::Glass;
				}

				else if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Water")
				{
					return (int32)EMaterialType::Water;
				}
			}
		}
		
	}

	return NULL;
}

int32 UCustomSpotAudioComponent::ScanAndReturnArrayMaterialSwitch(TArray<UMeshComponent*>MeshComponents)
{
	TArray<UMaterialInterface*>TempMaterialsArr;
	TArray<UPhysicalMaterial*> TempPhysicalMaterialsArr;

		/*Get All Mats from each Mesh Component*/
		for (int i = 0; i < MeshComponents.Num();i++)
		{
			if (MeshComponents.IsValidIndex(i) && i == 0)
			{
				TempMaterialsArr = MeshComponents[i]->GetMaterials();
			}
			else if (MeshComponents.IsValidIndex(i) && i != 0)
			{
				TArray <UMaterialInterface*> ScannedMaterials = MeshComponents[i]->GetMaterials();

				if (ScannedMaterials.Num() > 0)
				{
					for (int j = 0; j < ScannedMaterials.Num();j++)
					{
						if (ScannedMaterials.IsValidIndex(j))
						{
							TempMaterialsArr.Add(ScannedMaterials[j]);
						}
					}
				}

			}
		}

		/*Scan for Physical Materials of each detected Material*/
		for (int i = 0; i < TempMaterialsArr.Num(); i++)
		{
			if (TempMaterialsArr.IsValidIndex(i))
			{
				for (int j = 0; j < PhysicalMaterialsToScanFor.Num(); j++)
				{
					if (PhysicalMaterialsToScanFor.IsValidIndex(j) &&
						TempMaterialsArr[i]->GetPhysicalMaterial()->GetName() == PhysicalMaterialsToScanFor[j]->GetName())
					{
						TempPhysicalMaterialsArr.Add(TempMaterialsArr[i]->GetPhysicalMaterial());
					}
				}

			}
		}

		/*Categorize Physical Materials and return an Index for Cue switch*/
		for (int i = 0;i < TempPhysicalMaterialsArr.Num(); i++)
		{
			if (TempPhysicalMaterialsArr.IsValidIndex(i))
			{

				if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Plastic")
				{
					return (int32)EMaterialType::Plastic;
				}

				else if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Vegetation")
				{
					return (int32)EMaterialType::Vegetation;
				}

				else if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Metal")
				{

					for (int n = 0;n < TempPhysicalMaterialsArr.Num(); n++)
					{
						if (TempPhysicalMaterialsArr[n]->GetName() == "PM_Glass")
						{
							return (int32)EMaterialType::MetalGlass;
						}
					}

					return (int32)EMaterialType::Metal;
				}

				else if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Glass")
				{
					for (int n = 0; n < TempPhysicalMaterialsArr.Num(); n++)
					{
						if (TempPhysicalMaterialsArr[n]->GetName() == "PM_Metal")
						{
							return (int32)EMaterialType::MetalGlass;
						}
					}
					return (int32)EMaterialType::Glass;
				}

				else if (TempPhysicalMaterialsArr[i]->GetName() == "PM_Water")
				{
					return (int32)EMaterialType::Water;
				}
			}
		}

	

	return NULL;
}

TArray<UMeshComponent*> UCustomSpotAudioComponent::GetOverlappingActorMeshComponents(AActor* OverlappingActor)
{
	AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0));
	TArray<UMeshComponent*> TempMeshArray;


	if (OverlappingActor && OverlappingActor != Player)
	{
		TArray<UActorComponent*> TempCompArr = OverlappingActor->GetComponentsByClass(UMeshComponent::StaticClass());

		if (TempCompArr.Num()> 0)
		{
			

			for (int i = 0; i < TempCompArr.Num(); i++)
			{
				if (TempCompArr.IsValidIndex(i))
				{
					TempMeshArray.Add(Cast<UMeshComponent>(TempCompArr[i]));
				}
			}

		}


	}

	
	return TempMeshArray;
}

USoundBase* UCustomSpotAudioComponent::GetSoundFromComponent() 
{
	if (!LoadSoundOnStart)
	{
		Sound = CUE_OnStartLoad;
	}

	if (Sound)
	{
		return Sound;
	}

	return NULL;
	
};

USoundAttenuation* UCustomSpotAudioComponent::GetAttenuationFromComponent()
{
	
		return Attenuation_OnStartLoad;

}
