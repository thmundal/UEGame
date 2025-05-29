// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerCircuitConnectionPointComponent.generated.h"


class UPowerCircuitComponent;
class UPowerCircuitMember;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTUE5_API UPowerCircuitConnectionPointComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerCircuitConnectionPointComponent();

	UFUNCTION(BlueprintCallable)
	void ConnectMember(UPowerCircuitMember* PowerCircuitMember);

	UFUNCTION(BlueprintCallable)
	void DisconnectMember(UPowerCircuitMember* PowerCircuitMember);

	UFUNCTION(BlueprintCallable)
	void SetPowerCircuit(UPowerCircuitComponent* PowerCircuit);

	UFUNCTION(BlueprintPure)
	UPowerCircuitComponent* GetPowerCircuit() const { return m_PowerCircuit; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<TObjectPtr<UPowerCircuitMember>> m_ConnectedPowerCircuitMembers;

	UPROPERTY()
	TObjectPtr<UPowerCircuitComponent> m_PowerCircuit;
};
