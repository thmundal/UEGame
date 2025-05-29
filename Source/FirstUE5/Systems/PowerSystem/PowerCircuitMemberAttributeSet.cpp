// Copyright 2025 Chaos games


#include "PowerCircuitMemberAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UPowerCircuitMemberAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UPowerCircuitMemberAttributeSet, PowerCapacity, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(UPowerCircuitMemberAttributeSet, PowerDemand, SharedParams);
}

void UPowerCircuitMemberAttributeSet::OnRep_PowerDemand(const FGameplayAttributeData& OldDemand)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPowerCircuitMemberAttributeSet, PowerDemand, OldDemand);
}

void UPowerCircuitMemberAttributeSet::OnRep_PowerCapacity(const FGameplayAttributeData& OldCapacity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPowerCircuitMemberAttributeSet, PowerCapacity, OldCapacity);
}
