// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Attributes/AttributeMacros.h"
#include "PowerCircuitMemberAttributeSet.generated.h"

UCLASS()
class FIRSTUE5_API UPowerCircuitMemberAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Attribute definitions
	UPROPERTY(ReplicatedUsing = OnRep_PowerCapacity, BlueprintReadOnly, EditDefaultsOnly, Category = "Attributes")
	FGameplayAttributeData PowerCapacity;
	ATTRIBUTE_ACCESSORS(UPowerCircuitMemberAttributeSet, PowerCapacity)

	UPROPERTY(ReplicatedUsing = OnRep_PowerDemand, BlueprintReadOnly, EditDefaultsOnly, Category = "Attributes")
	FGameplayAttributeData PowerDemand;
	ATTRIBUTE_ACCESSORS(UPowerCircuitMemberAttributeSet, PowerDemand)
	
protected:
	UFUNCTION()
	void OnRep_PowerDemand(const FGameplayAttributeData& OldDemand);

	UFUNCTION()
	void OnRep_PowerCapacity(const FGameplayAttributeData& OldCapacity);
};
