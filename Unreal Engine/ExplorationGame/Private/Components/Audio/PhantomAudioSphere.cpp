// Code Created By Diego Demarco


#include "Components/Audio/PhantomAudioSphere.h"

UPhantomAudioSphere::UPhantomAudioSphere()
{
	SphereRadius = 10000.f;

	this->OnComponentBeginOverlap.AddDynamic(this, &UPhantomAudioSphere::OnOverlapBegin);
	this->OnComponentEndOverlap.AddDynamic(this, &UPhantomAudioSphere::OnOverlapEnd);
}

void UPhantomAudioSphere::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->FindComponentByClass<UCustomSpotAudioComponent>())
	{

		UCustomSpotAudioComponent* TempSpotAudioComponent = OtherActor->FindComponentByClass<UCustomSpotAudioComponent>();

		if (!TempSpotAudioComponent->IsActive() || !TempSpotAudioComponent->IsPlaying())
		{
			TempSpotAudioComponent->Activate();
			TempSpotAudioComponent->Play();
		}

	}

}


void UPhantomAudioSphere::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->FindComponentByClass<UCustomSpotAudioComponent>())
	{
		UCustomSpotAudioComponent* TempSpotAudioComponent = OtherActor->FindComponentByClass<UCustomSpotAudioComponent>();

		if (TempSpotAudioComponent->IsActive() || TempSpotAudioComponent->IsPlaying())
		{
			TempSpotAudioComponent->Stop();
			TempSpotAudioComponent->Deactivate();
		}

	}
}