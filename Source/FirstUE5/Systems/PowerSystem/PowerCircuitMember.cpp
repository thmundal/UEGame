// Copyright 2025 Chaos games

#include "PowerCircuitMember.h"

#include "MyGameMode.h"
#include "PowerCircuitComponent.h"
#include "Net/UnrealNetwork.h"


// Add default functionality here for any IPowerCircuitMemberInterface functions that are not pure virtual.
bool UPowerCircuitMember::AttachToFirstAvailablePowerCircuit(AMyGameMode* const GameMode)
{
	AActor* Owner = GetOwner();
	if (IsValid(Owner) && Owner->HasAuthority() && IsValid(GameMode))
	{
		if (IsValid(m_PowerCircuit))
		{
			m_PowerCircuit->DetachPowerCircuitMember(this);
			m_PowerCircuit = nullptr;
		}

		TArray<UPowerCircuitComponent*> PowerCircuits = GameMode->GetPowerCircuits();
		for (UPowerCircuitComponent* PowerCircuit : PowerCircuits)
		{
			if (IsValid(PowerCircuit))
			{
				AttachToPowerCircuit(PowerCircuit);
				return true;
			}
		}
	}

	return false;
}

void UPowerCircuitMember::AttachToPowerCircuit(class UPowerCircuitComponent* PowerCircuit)
{
	if (IsValid(PowerCircuit))
	{
		m_PowerCircuit = PowerCircuit;
		PowerCircuit->AttachPowerCircuitMember(this);
		Enable();
		m_OnPowerCircuitChanged.Broadcast(PowerCircuit);
	}
}

void UPowerCircuitMember::DetachFromPowerCircuit()
{
	if (IsValid(m_PowerCircuit))
	{
		m_OnPowerCircuitChanged.Broadcast(nullptr);
		m_PowerCircuit->DetachPowerCircuitMember(this);
		Disable();
		m_PowerCircuit = nullptr;
	}
}

void UPowerCircuitMember::Disable()
{
	if (IsValid(m_PowerCircuit))
	{
		m_PowerCircuit->DisableMember(this);
		bEnabled = false;
	}
}

void UPowerCircuitMember::Enable()
{
	if (IsValid(m_PowerCircuit))
	{
		m_PowerCircuit->EnableMember(this);
		bEnabled = true;
	}
}

void UPowerCircuitMember::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (IsValid(Owner) && Owner->HasAuthority())
	{
		AMyGameMode* GameMode = Cast<AMyGameMode>(Owner->GetWorld()->GetAuthGameMode());
		if (IsValid(GameMode) && !AttachToFirstAvailablePowerCircuit(GameMode))
		{
			GameMode->GetOnPowerCircuitAddedDelegate().AddUniqueDynamic(this, &UPowerCircuitMember::AttachToPowerCircuit);
		}
	}
}

void UPowerCircuitMember::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPowerCircuitMember, m_PowerCircuit);
	DOREPLIFETIME(UPowerCircuitMember, bEnabled);
}
