// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicGameEventLocation.generated.h"

UCLASS(Blueprintable)
class FIRSTUE5_API ADynamicGameEventLocation : public AActor
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	virtual void RegisterWithSubsystem();
};
