// Copyright 2025 Chaos games

#include "DynamicGameEventLocation.h"
#include "DynamicGameEventsSubsystem.h"

class UDynamicGameEventsSubsystem;

void ADynamicGameEventLocation::BeginPlay()
{
	Super::BeginPlay();

}

void ADynamicGameEventLocation::RegisterWithSubsystem()
{
	UWorld* World = GetWorld();

	if (!IsValid(World))
	{
		return;
	}

	UDynamicGameEventsSubsystem* DynamicGameEventsSubsystem = World->GetSubsystem<UDynamicGameEventsSubsystem>();
	if (!IsValid(DynamicGameEventsSubsystem))
	{
		return;
	}

	DynamicGameEventsSubsystem->RegisterDynamicGameEventLocation(this);
}
