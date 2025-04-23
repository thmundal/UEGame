// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"

#include "OpenableDoor.h"


// Sets default values
AInteractableActor::AInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableActor::ServerInteract_Implementation(AActor* InteractingActor)
{
	OnInteract(InteractingActor);
}

void AInteractableActor::OnInteract(AActor* InteractingActor)
{
	AOpenableDoor* Door = Cast<AOpenableDoor>(m_Door);
	if (IsValid(Door))
	{
		Door->ServerToggleState();		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid door set"));
	}
	UE_LOG(LogTemp, Warning, TEXT("It was interacted with!"));
}

