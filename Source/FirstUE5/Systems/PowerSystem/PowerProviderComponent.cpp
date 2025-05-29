// Copyright 2025 Chaos games

#include "PowerProviderComponent.h"

UPowerProviderComponent::UPowerProviderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

float UPowerProviderComponent::GetPowerCapacity() const
{
	return GetAttributeValue(PowerCapacityAttribute);
}
