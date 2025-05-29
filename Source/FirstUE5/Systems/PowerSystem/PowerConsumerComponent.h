// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PowerCircuitMember.h"
#include "PowerConsumerComponent.generated.h"

class ASpaceRepairGameMode;
class UPowerCircuitComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTUE5_API UPowerConsumerComponent : public UPowerCircuitMember
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerConsumerComponent();

	UFUNCTION(BlueprintCallable)
	float GetPowerDemand() const;

	UFUNCTION(BlueprintCallable)
	bool IsPowered() const;

protected:
	UFUNCTION()
	void OnPowerBalanceChanged();

	UFUNCTION()
	void OnPowerCircuitChanged(UPowerCircuitComponent* PowerCircuit);

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	FGameplayAttribute PowerDemandAttribute;
};
