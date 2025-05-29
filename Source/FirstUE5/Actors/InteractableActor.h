// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "FirstUE5/Systems/Interaction/IInteractableInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

class ITriggerReceiverInterface;
class AOpenableDoor;
UCLASS()
class FIRSTUE5_API AInteractableActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableActor();

	virtual void OnInteract(AActor* InteractingActor) override;
	
	UFUNCTION(BlueprintNativeEvent)
	void BP_OnInteract(AActor* InteractingActor);

	void ExecuteTriggerReceiver(UObject* TriggerPayload = nullptr);
	
protected:
	UPROPERTY(EditAnywhere, meta = (MustImplement = "TriggerReceiverInterface"))
	TObjectPtr<AActor> m_TriggerReceiver;
	
private:
	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InteractingActor);
};
