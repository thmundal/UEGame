// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "Attributes/AttributeMacros.h"
#include "LifeSupportAttributeSet.generated.h"

UCLASS()
class FIRSTUE5_API ULifeSupportAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// State attributes
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ULifeSupportAttributeSet, MaxHealth)

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(ULifeSupportAttributeSet, CurrentHealth)

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxOxygen;
	ATTRIBUTE_ACCESSORS(ULifeSupportAttributeSet, MaxOxygen)

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData CurrentOxygen;
	ATTRIBUTE_ACCESSORS(ULifeSupportAttributeSet, CurrentOxygen)

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxTemperature;
	ATTRIBUTE_ACCESSORS(ULifeSupportAttributeSet, MaxTemperature)

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData CurrentTemperature;
	ATTRIBUTE_ACCESSORS(ULifeSupportAttributeSet, CurrentTemperature)

	// Regen attributes
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData OxygenRegenRate;
	ATTRIBUTE_ACCESSORS(ULifeSupportAttributeSet, OxygenRegenRate)

	// Drain attributes
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData OxygenDrainRate;
	ATTRIBUTE_ACCESSORS(ULifeSupportAttributeSet, OxygenDrainRate)
};
