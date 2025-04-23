// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenableDoor.h"

#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "Net/UnrealNetwork.h"

PRAGMA_DISABLE_OPTIMIZATION

// Sets default values
AOpenableDoor::AOpenableDoor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAlwaysRelevant = true;
	bReplicates = true;
}

void AOpenableDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AOpenableDoor, m_DoorState);
}

// Called when the game starts or when spawned
void AOpenableDoor::BeginPlay()
{
	Super::BeginPlay();

	m_ActorSequenceComponent = FindComponentByClass<UActorSequenceComponent>();
}

void AOpenableDoor::OnRep_DoorState()
{
	ToggleOpen();
}

void AOpenableDoor::ServerToggleState_Implementation()
{
	ENetMode NetMode = GetNetMode();
	if (m_DoorState == EDoorState::Open || m_DoorState == EDoorState::Uninitialized)
	{
		m_DoorState = EDoorState::Closed;
	}
	else
	{
		m_DoorState = EDoorState::Open;
	}
}

// Called every frame
void AOpenableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOpenableDoor::Open()
{
	if (IsValid(m_ActorSequenceComponent))
	{
		UMovieSceneSequencePlayer* MovieSceneSequencePlayer = m_ActorSequenceComponent->GetSequencePlayer();

		if (IsValid(MovieSceneSequencePlayer))
		{
			MovieSceneSequencePlayer->Play();
		}
	}
}

void AOpenableDoor::Close()
{
	if (IsValid(m_ActorSequenceComponent))
	{
		UMovieSceneSequencePlayer* MovieSceneSequencePlayer = m_ActorSequenceComponent->GetSequencePlayer();

		if (IsValid(MovieSceneSequencePlayer))
		{
			MovieSceneSequencePlayer->PlayReverse();
		}
	}
}

void AOpenableDoor::ToggleOpen()
{
	if (m_DoorState > EDoorState::Uninitialized)
	{
		if (m_DoorState == EDoorState::Closed)
		{
			Open();
		}
		else
		{
			Close();
		}
	}
}

PRAGMA_ENABLE_OPTIMIZATION