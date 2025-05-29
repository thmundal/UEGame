// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "TriggerReceiverInterface.generated.h"

UINTERFACE()
class FIRSTUE5_API UTriggerReceiverInterface : public UInterface
{
	GENERATED_BODY()
};

class FIRSTUE5_API ITriggerReceiverInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnTriggerReceived(UObject* TriggerPayload);
};