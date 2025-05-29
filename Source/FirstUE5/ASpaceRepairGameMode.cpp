// Copyright 2025 Chaos games


#include "ASpaceRepairGameMode.h"

void ASpaceRepairGameMode::AddPowerCircuit(UPowerCircuitComponent* PowerCircuit)
{
	m_PowerCircuits.AddUnique(PowerCircuit);

	OnPowerCircuitAdded.Broadcast(PowerCircuit);
	OnPowerCircuitAdded.Clear();
}

void ASpaceRepairGameMode::RemovePowerCircuit(UPowerCircuitComponent* PowerCircuit)
{
	m_PowerCircuits.Remove(PowerCircuit);
}

const TArray<UPowerCircuitComponent*>& ASpaceRepairGameMode::GetPowerCircuits() const
{
	return m_PowerCircuits;
}
