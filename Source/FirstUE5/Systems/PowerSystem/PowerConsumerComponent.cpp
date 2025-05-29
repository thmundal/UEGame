// Copyright 2025 Chaos games


#include "PowerConsumerComponent.h"

#include "AbilitySystemComponent.h"
#include "PowerCircuitComponent.h"
#include "FirstUE5/MyGameMode.h"

UPowerConsumerComponent::UPowerConsumerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

float UPowerConsumerComponent::GetPowerDemand() const
{
	const UAttributeSet* AttrSet = GetAttributeSet();
	if (!IsValid(AttrSet))
	{
		return 0.f;
	}

	return PowerDemandAttribute.GetNumericValue(AttrSet);
}

bool UPowerConsumerComponent::IsPowered() const
{
	const UPowerCircuitComponent* PowerCircuit = GetPowerCircuit();
	if (!IsValid(PowerCircuit))
	{
		return false;
	}

	const float PowerDemand = GetPowerDemand();
	const float PowerCapacity = PowerCircuit->GetPowerCapacity();

	if (PowerDemand <= PowerCapacity)
	{
		return PowerDemand <= PowerCapacity;
	}

	return false;
}

void UPowerConsumerComponent::OnPowerBalanceChanged()
{
	if (!bEnabled && IsPowered())
	{
		Enable();
	}
	else if (bEnabled && !IsPowered())
	{
		Disable();
	}
}

void UPowerConsumerComponent::OnPowerCircuitChanged(UPowerCircuitComponent* PowerCircuit)
{
	if (IsValid(PowerCircuit))
	{
		PowerCircuit->GetPowerBalanceChangedDelegate().AddDynamic(this, &UPowerConsumerComponent::OnPowerBalanceChanged);
	}
	else if (IsValid(GetPowerCircuit()))
	{
		GetPowerCircuit()->GetPowerBalanceChangedDelegate().RemoveDynamic(this, &UPowerConsumerComponent::OnPowerBalanceChanged);
	}
}

void UPowerConsumerComponent::BeginPlay()
{
	m_OnPowerCircuitChanged.AddDynamic(this, &UPowerConsumerComponent::OnPowerCircuitChanged);
	Super::BeginPlay();
}
