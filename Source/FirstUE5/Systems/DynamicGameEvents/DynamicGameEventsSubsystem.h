// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "DynamicGameEventLocation.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DynamicGameEventsSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDynamicGameEvents, Log, All);

UCLASS()
class FIRSTUE5_API UDynamicGameEventsSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual TStatId GetStatId() const override;

public:
	void RegisterDynamicGameEventLocation(ADynamicGameEventLocation* DynamicGameEventLocation);
	void UnregisterDynamicGameEventLocation(ADynamicGameEventLocation* DynamicGameEventLocation);
	
private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<ADynamicGameEventLocation>> m_DynamicGameEventLocations;

	bool bClientHasDeinitialized = false;
};
