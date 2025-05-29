// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PowerCircuitMember.h"
#include "Components/ActorComponent.h"
#include "PowerProviderComponent.generated.h"

class ASpaceRepairGameMode;
class UPowerCircuitComponent;
class UAbilitySystemComponent;
class UPowerCircuitMemberAttributeSet;
class UGameplayEffect;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTUE5_API UPowerProviderComponent : public UPowerCircuitMember
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerProviderComponent();

	UFUNCTION(BlueprintCallable)
	float GetPowerCapacity() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Power")
	FGameplayAttribute PowerCapacityAttribute;
};
