// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "Attributes/AttributeSetHolder.h"
#include "LifeSupportComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTUE5_API ULifeSupportComponent : public UAttributeSetHolder
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULifeSupportComponent();
};
