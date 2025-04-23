// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OpenableDoor.generated.h"

class UActorSequenceComponent;
UENUM()
enum class EDoorState : uint8
{
	Uninitialized,
	Open,
	Closed
};


UCLASS()
class FIRSTUE5_API AOpenableDoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOpenableDoor(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	UActorSequenceComponent* m_ActorSequenceComponent;
	
	UPROPERTY(ReplicatedUsing=OnRep_DoorState)
	EDoorState m_DoorState = EDoorState::Uninitialized;

	UFUNCTION()
	void OnRep_DoorState();

public:
	UFUNCTION(Server, Reliable)
	void ServerToggleState();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Open();
	void Close();
	void ToggleOpen();
};
