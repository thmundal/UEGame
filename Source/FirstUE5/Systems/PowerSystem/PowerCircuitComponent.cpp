// Copyright 2025 Chaos games


#include "PowerCircuitComponent.h"

#include "AbilitySystemComponent.h"
#include "PowerConsumerComponent.h"
#include "FirstUE5/ASpaceRepairGameMode.h"

DECLARE_LOG_CATEGORY_CLASS(LogPowerCircuit, Log, All)

// Sets default values for this component's properties
UPowerCircuitComponent::UPowerCircuitComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetIsReplicatedByDefault(true);
}

void UPowerCircuitComponent::AttachPowerCircuitMember(UPowerCircuitMember* PowerCircuitMember)
{
	if (IsValid(PowerCircuitMember))
	{
		if (HasAuthority())
		{
			m_PowerCircuitMembers.AddUnique(PowerCircuitMember);
		}
	}
}

void UPowerCircuitComponent::DetachPowerCircuitMember(UPowerCircuitMember* PowerCircuitMember)
{
	if (IsValid(PowerCircuitMember))
	{
		if (HasAuthority())
		{
			m_PowerCircuitMembers.Remove(PowerCircuitMember);
		}
	}
}

float UPowerCircuitComponent::GetPowerDemand() const
{
	return GetAttributeValue(PowerDemandAttribute);
}

float UPowerCircuitComponent::GetPowerCapacity() const
{
	return GetAttributeValue(PowerCapacityAttribute);
}

bool UPowerCircuitComponent::HasAuthority()
{
	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return false;
	}

	return Owner->HasAuthority();
}

void UPowerCircuitComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}
	
	if (Owner->HasAuthority())
	{
		// register this component with the game mode
		ASpaceRepairGameMode* GameMode = Cast<ASpaceRepairGameMode>(GetWorld()->GetAuthGameMode());

		if (IsValid(GameMode))
		{
			GameMode->AddPowerCircuit(this);
		}
		else
		{
			UE_LOG(LogPowerCircuit, Warning, TEXT("PowerCircuitComponent::BeginPlay - GameMode is not valid"));
		}
	}

	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PowerDemandAttribute).AddUObject(this, &UPowerCircuitComponent::OnPowerDemandChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PowerCapacityAttribute).AddUObject(this, &UPowerCircuitComponent::OnPowerCapacityChanged);
	}
}

void UPowerCircuitComponent::OnPowerDemandChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	BroadcastPowerBalanceChanged();
}

void UPowerCircuitComponent::OnPowerCapacityChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	BroadcastPowerBalanceChanged();
}

void UPowerCircuitComponent::BroadcastPowerBalanceChanged()
{
	m_OnPowerBalanceChanged.Broadcast();
}

void UPowerCircuitComponent::MulticastPowerBalanceChanged_Implementation()
{
	BroadcastPowerBalanceChanged();
}

void UPowerCircuitComponent::DisableMember(UPowerCircuitMember* PowerCircuitMember)
{
	if (HasAuthority() && m_PowerCircuitMembers.Contains(PowerCircuitMember))
	{
		RemoveGameplayEffect(PowerCircuitMember->GetInitialAttributeEffectClass(), PowerCircuitMember->GetAbilitySystemComponent());
	}
}

void UPowerCircuitComponent::EnableMember(UPowerCircuitMember* PowerCircuitMember)
{
	if (HasAuthority() && m_PowerCircuitMembers.Contains(PowerCircuitMember))
	{
		ApplyGameplayEffect(PowerCircuitMember->GetInitialAttributeEffectClass(), PowerCircuitMember->GetEffectLevel(), PowerCircuitMember->GetAbilitySystemComponent());
	}
}

FPowerBalanceChangedDelegate& UPowerCircuitComponent::GetPowerBalanceChangedDelegate()
{
	return m_OnPowerBalanceChanged;
}
