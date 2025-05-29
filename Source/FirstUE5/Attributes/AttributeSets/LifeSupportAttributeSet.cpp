// Copyright 2025 Chaos games


#include "LifeSupportAttributeSet.h"

#include "Net/UnrealNetwork.h"

void ULifeSupportAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(ULifeSupportAttributeSet, MaxHealth, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ULifeSupportAttributeSet, CurrentHealth, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ULifeSupportAttributeSet, MaxOxygen, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ULifeSupportAttributeSet, CurrentOxygen, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ULifeSupportAttributeSet, MaxTemperature, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ULifeSupportAttributeSet, CurrentTemperature, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ULifeSupportAttributeSet, OxygenDrainRate, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ULifeSupportAttributeSet, OxygenRegenRate, SharedParams);
}
