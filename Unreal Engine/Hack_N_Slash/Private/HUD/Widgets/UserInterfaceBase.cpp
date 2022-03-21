// Code Created By Diego Demarco


#include "HUD/Widgets/UserInterfaceBase.h"

float	UUserInterfaceBase::ModifyHealthBar(float Amount)
{
	HealthBar->SetPercent(Amount);
	return (HealthBar->Percent);
}

float	UUserInterfaceBase::ModifyEnergyBar(float Amount)
{
	EnergyBar->SetPercent(Amount);
	return (EnergyBar->Percent);
}
