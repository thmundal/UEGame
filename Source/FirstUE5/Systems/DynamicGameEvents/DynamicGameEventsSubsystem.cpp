// Copyright 2025 Chaos games

#include "DynamicGameEventsSubsystem.h"

#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogDynamicGameEvents);

void UDynamicGameEventsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogDynamicGameEvents, Verbose, TEXT("DynamicGameEventsSubsystem Initialized"));
}

void UDynamicGameEventsSubsystem::Deinitialize()
{
	if (GetWorld()->GetNetMode() == NM_Client)
	{
		if (bClientHasDeinitialized)
		{
			// Prevent duplicate deinitialization calls on client
			return;
		}
		bClientHasDeinitialized = true;
	}
	Super::Deinitialize();

	UE_LOG(LogDynamicGameEvents, Verbose, TEXT("DynamicGameEventsSubsystem Deinitialized"));
}

bool UDynamicGameEventsSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// Only create the subsystem if we are on the server
	return Super::ShouldCreateSubsystem(Outer);
}

void UDynamicGameEventsSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	if (!IsValid(World) || !World->HasBegunPlay())
	{
		// Do not tick without a world, or before world has begun play
		return;
	}

	UE_LOG(LogDynamicGameEvents, Verbose, TEXT("%s: DynamicGameEventsSubsystem Tick"), GetWorld()->GetNetMode() == NM_Client ? TEXT("Client") : TEXT("Server"));
}

void UDynamicGameEventsSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	if (InWorld.GetNetMode() == NM_Client)
	{
		// Don't initialize the subsystem on the client
		Deinitialize();
		return;
	}

	Super::OnWorldBeginPlay(InWorld);
}

TStatId UDynamicGameEventsSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UDynamicGameEventsSubsystem, STATGROUP_Tickables);
}

void UDynamicGameEventsSubsystem::RegisterDynamicGameEventLocation(ADynamicGameEventLocation* DynamicGameEventLocation)
{
	m_DynamicGameEventLocations.AddUnique(DynamicGameEventLocation);

	UE_LOG(LogDynamicGameEvents, Verbose, TEXT("Registered DynamicGameEventLocation: %s"), *DynamicGameEventLocation->GetName());
}

void UDynamicGameEventsSubsystem::UnregisterDynamicGameEventLocation(ADynamicGameEventLocation* DynamicGameEventLocation)
{
	m_DynamicGameEventLocations.Remove(DynamicGameEventLocation);

	UE_LOG(LogDynamicGameEvents, Verbose, TEXT("Unregistered DynamicGameEventLocation: %s"), *DynamicGameEventLocation->GetName());
}
