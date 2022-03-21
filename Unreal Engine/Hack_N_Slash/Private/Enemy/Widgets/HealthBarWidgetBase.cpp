// Code Created By Diego Demarco


#include "Enemy/Widgets/HealthBarWidgetBase.h"

float	UHealthBarWidgetBase::ModifyHealthBar(float Amount)
{
	HealthBar->SetPercent(Amount);
	return (HealthBar->Percent);
}

float	UHealthBarWidgetBase::ModifyEnergyBar(float Amount)
{
	EnergyBar->SetPercent(Amount);
	return (EnergyBar->Percent);
}
