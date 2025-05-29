// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StationRoom.generated.h"

class UPowerCircuitConnectionPointComponent;
class UAttributeSetHolder;

UCLASS()
class FIRSTUE5_API AStationRoom : public AActor
{
	GENERATED_BODY()

public:
	AStationRoom();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UAttributeSetHolder* m_AttributeSetHolderComponent;

	UPROPERTY()
	UPowerCircuitConnectionPointComponent* m_PowerCircuitConnectionPoint;

	UPROPERTY()
	TArray<TObjectPtr<AStationRoom>> m_ConnectedRooms;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> m_ContainedActors;
};
