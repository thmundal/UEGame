// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AttributeSetHolder.h"
#include "UObject/Interface.h"
#include "PowerCircuitMember.generated.h"

class ASpaceRepairGameMode;
class UPowerCircuitComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPowerCircuitChangedDelegate, UPowerCircuitComponent*, PowerCircuit);

UCLASS(Abstract)
class FIRSTUE5_API UPowerCircuitMember : public UAttributeSetHolder
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool AttachToFirstAvailablePowerCircuit(ASpaceRepairGameMode* const GameMode);

	UFUNCTION(BlueprintCallable)
	void AttachToPowerCircuit(UPowerCircuitComponent* PowerCircuit);

	UFUNCTION(BlueprintCallable)
	void DetachFromPowerCircuit();

	UFUNCTION(BlueprintCallable)
	void Disable();

	UFUNCTION(BlueprintCallable)
	void Enable();
	
	UFUNCTION(BlueprintPure)
	UPowerCircuitComponent* GetPowerCircuit() const { return m_PowerCircuit; }

	UFUNCTION(BlueprintPure)
	bool GetIsEnabled() const { return bEnabled; }

public:
	UPROPERTY(BlueprintAssignable)
	FOnPowerCircuitChangedDelegate m_OnPowerCircuitChanged;

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Transient, Replicated)
	TObjectPtr<UPowerCircuitComponent> m_PowerCircuit;

protected:
	UPROPERTY(Transient, Replicated);
	bool bEnabled = false;

	UPROPERTY(EditAnywhere, Category = "PowerCircuit")
	bool bAutoAttachToPowerCircuit = false;
};
