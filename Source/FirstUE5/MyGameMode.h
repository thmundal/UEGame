// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

class UPowerCircuitComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPowerCircuitAddedDelegate, UPowerCircuitComponent*, PowerCircuit);

UCLASS()
class FIRSTUE5_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPowerCircuit(UPowerCircuitComponent* PowerCircuit);
	
	UFUNCTION(BlueprintCallable)
	void RemovePowerCircuit(UPowerCircuitComponent* PowerCircuit);

	UFUNCTION(BlueprintCallable)
	const TArray<UPowerCircuitComponent*>& GetPowerCircuits() const;

	FOnPowerCircuitAddedDelegate& GetOnPowerCircuitAddedDelegate() { return OnPowerCircuitAdded; }

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UPowerCircuitComponent>> m_PowerCircuits;

	UPROPERTY(BlueprintAssignable)
	FOnPowerCircuitAddedDelegate OnPowerCircuitAdded;
};
