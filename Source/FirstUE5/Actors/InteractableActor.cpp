// Copyright 2025 Chaos games

#include "InteractableActor.h"

#include "OpenableDoor.h"
#include "FirstUE5/Systems/Interaction/TriggerReceiverInterface.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
}

void AInteractableActor::OnInteract(AActor* InteractingActor)
{
	BP_OnInteract(InteractingActor);
}

void AInteractableActor::BP_OnInteract_Implementation(AActor* InteractingActor)
{
	ExecuteTriggerReceiver();
}

void AInteractableActor::ExecuteTriggerReceiver(UObject* TriggerPayload)
{
	if (m_TriggerReceiver && m_TriggerReceiver->Implements<UTriggerReceiverInterface>())
	{
		ITriggerReceiverInterface::Execute_OnTriggerReceived(m_TriggerReceiver, TriggerPayload);
	}
}

void AInteractableActor::ServerInteract_Implementation(AActor* InteractingActor)
{
	OnInteract(InteractingActor);
}
