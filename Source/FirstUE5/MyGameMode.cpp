// Copyright 2025 Chaos games


#include "MyGameMode.h"

void AMyGameMode::AddPowerCircuit(UPowerCircuitComponent* PowerCircuit)
{
	m_PowerCircuits.AddUnique(PowerCircuit);

	OnPowerCircuitAdded.Broadcast(PowerCircuit);
	OnPowerCircuitAdded.Clear();
}

void AMyGameMode::RemovePowerCircuit(UPowerCircuitComponent* PowerCircuit)
{
	m_PowerCircuits.Remove(PowerCircuit);
}

const TArray<UPowerCircuitComponent*>& AMyGameMode::GetPowerCircuits() const
{
	return m_PowerCircuits;
}
