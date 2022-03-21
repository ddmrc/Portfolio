// Code Created By Diego Demarco

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"
#include "CustomSpotAudioComponent.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMaterialType :uint8
{
	Plastic,
	Vegetation,
	Metal,
	MetalGlass,
	Glass,
	Water,
};

UCLASS(ClassGroup = (Audio, Common), hidecategories = (LOD), ShowCategories = (Object, ActorComponent, Physics, Rendering, Mobility, Trigger), meta = (BlueprintSpawnableComponent))
class RAINPROTOTYPE_API UCustomSpotAudioComponent : public UAudioComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Sound Material")
	bool LoadSoundOnStart = true;

	UPROPERTY(EditAnywhere, Category = "Sound Material")
	USoundCue* CUE_OnStartLoad;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound Material")
	USoundAttenuation* Attenuation_OnStartLoad;

	UPROPERTY(EditAnywhere, Category = "Material Switch")
	TArray <UPhysicalMaterial*> PM_OnStartLoad;

	TArray <UPhysicalMaterial*> PhysicalMaterialsToScanFor;

	UFUNCTION(BlueprintCallable, Category = "Material Scanner")
	int32 ScanAndReturnMaterialSwitch(UMeshComponent*MeshComponent);

	UFUNCTION(BlueprintCallable, Category = "Material Scanner")
	int32 ScanAndReturnArrayMaterialSwitch(TArray<UMeshComponent*>MeshComponents);

	UFUNCTION(BlueprintCallable, Category = "Material Scanner")
	TArray<UMeshComponent*> GetOverlappingActorMeshComponents(AActor* OverlappingActor);

	UFUNCTION(BlueprintCallable, Category = "Play Sound")
		USoundBase* GetSoundFromComponent();

	UFUNCTION(BlueprintCallable, Category = "Play Sound")
		USoundAttenuation* GetAttenuationFromComponent();
	

	

protected:

	virtual void BeginPlay() override;

};
