// Copyright 2025 Chaos games


#include "PowerCircuitConnectionPointComponent.h"

#include "PowerCircuitComponent.h"
#include "PowerCircuitMember.h"

UPowerCircuitConnectionPointComponent::UPowerCircuitConnectionPointComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPowerCircuitConnectionPointComponent::ConnectMember(UPowerCircuitMember* PowerCircuitMember)
{
	if (IsValid(m_PowerCircuit) && IsValid(PowerCircuitMember))
	{
		PowerCircuitMember->AttachToPowerCircuit(m_PowerCircuit);
		m_ConnectedPowerCircuitMembers.AddUnique(PowerCircuitMember);
	}
}

void UPowerCircuitConnectionPointComponent::DisconnectMember(UPowerCircuitMember* PowerCircuitMember)
{
	if (IsValid(m_PowerCircuit) && IsValid(PowerCircuitMember))
	{
		PowerCircuitMember->DetachFromPowerCircuit();
		m_ConnectedPowerCircuitMembers.Remove(PowerCircuitMember);
	}
}

void UPowerCircuitConnectionPointComponent::SetPowerCircuit(UPowerCircuitComponent* PowerCircuit)
{
	const bool bCircuitChanged = (m_PowerCircuit.Get() != PowerCircuit);
	const bool bCircuitAdded = PowerCircuit != nullptr;

	if (!bCircuitChanged)
	{
		return;
	}

	for (UPowerCircuitMember* const Member : m_ConnectedPowerCircuitMembers)
	{
		if (IsValid(Member))
		{
			if (bCircuitAdded)
			{
				Member->AttachToPowerCircuit(PowerCircuit);
			}
			else
			{
				Member->DetachFromPowerCircuit();
			}
		}
	}

	m_PowerCircuit = PowerCircuit;
}

void UPowerCircuitConnectionPointComponent::BeginPlay()
{
	Super::BeginPlay();
}
