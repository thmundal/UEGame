// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstUE5/Systems/Interaction/IInteractableInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

class AOpenableDoor;
UCLASS()
class FIRSTUE5_API AInteractableActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableActor();
	virtual void OnInteract(AActor* InteractingActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AOpenableDoor> m_Door;
	
private:
	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InteractingActor);
};
