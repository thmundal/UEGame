#pragma once

#include "IInteractableInterface.generated.h"

UENUM()
enum class EInteractMode : uint8
{
	Server,
	Client,
	ServerAndClient
};

UINTERFACE()
class FIRSTUE5_API UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class FIRSTUE5_API IInteractableInterface
{
	GENERATED_BODY()

	EInteractMode m_InteractMode = EInteractMode::Server;

public:
	virtual void OnInteract(AActor* InteractingActor) = 0;
};
