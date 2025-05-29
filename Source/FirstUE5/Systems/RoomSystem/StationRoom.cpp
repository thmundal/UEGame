// Copyright 2025 Chaos games


#include "StationRoom.h"

#include "Attributes/AttributeSetHolder.h"

AStationRoom::AStationRoom()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	bReplicates = true;

	m_AttributeSetHolderComponent = CreateDefaultSubobject<UAttributeSetHolder>(TEXT("AttributeSetHolderComponent"));
}

void AStationRoom::BeginPlay()
{
	Super::BeginPlay();
}
