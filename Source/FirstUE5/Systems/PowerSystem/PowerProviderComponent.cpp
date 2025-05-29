// Copyright 2025 Chaos games

#include "PowerProviderComponent.h"

#include "FirstUE5/MyGameMode.h"

UPowerProviderComponent::UPowerProviderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

float UPowerProviderComponent::GetPowerCapacity() const
{
	const UAttributeSet* AttrSet = GetAttributeSet();
	if (!IsValid(AttrSet))
	{
		return 0.f;
	}

	return PowerCapacityAttribute.GetNumericValue(AttrSet);
}
