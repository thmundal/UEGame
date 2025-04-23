// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "IInteractableInterface.h"
#include "FirstUE5/GamePlayerCharacter.h"
#include "FirstUE5/InputActionNames.h"
#include "FirstUE5/UInputActionRow.h"
#include "FirstUE5/DataTables/DataTableSettings.h"
#include "FirstUE5/GUI/HUDManager.h"
#include "FirstUE5/GUI/PlayerHudWidget.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInteractionComponent::OnTriggerOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IInteractableInterface* InteractableActor = Cast<IInteractableInterface>(OtherActor))
	{
		// Register this actor as a potential interaction target
		m_PotentialInteractionActors.Add(InteractableActor);
	}
}

void UInteractionComponent::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(const IInteractableInterface* InteractableActor = Cast<IInteractableInterface>(OtherActor))
	{
		// Register this actor as a potential interaction target
		m_PotentialInteractionActors.Remove(InteractableActor);
	}
}

void UInteractionComponent::ExecuteInteraction()
{
	ServerExecuteInteraction();
}

void UInteractionComponent::ServerExecuteInteraction_Implementation() const
{
	if (m_CurrentInteractionTarget != nullptr)
	{
		m_CurrentInteractionTarget->OnInteract(GetOwner());
	}
}

void UInteractionComponent::BindInputActions(UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem,
                                             UEnhancedInputComponent* EnhancedInputComponent)
{
	const UDataTableSettings* DataTableSettings = UDataTableSettings::Get();

	if (!IsValid(DataTableSettings))
	{
		return;
	}
	
	const UDataTable* InputActions = DataTableSettings->LoadDataTable(DataTableSettings->m_InputActions);

	if (!IsValid(InputActions))
	{
		return;
	}
	
	const FInputActionRow* InteractActionRow = InputActions->FindRow<FInputActionRow>(InputAction::Interact, TEXT("Could not find input action for MovementForward"));

	if (InteractActionRow != nullptr)
	{
		EnhancedInputComponent->BindAction(InteractActionRow->InputAction, ETriggerEvent::Triggered, this, &UInteractionComponent::ExecuteInteraction);
	}
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnTriggerOverlapStart);
	OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnTriggerOverlapEnd);
	SetSphereRadius(m_InteractionDetectionRadius);

	AGamePlayerCharacter* const PlayerCharacter = Cast<AGamePlayerCharacter>(GetOwner());
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->OnPlayerInputComponentSetup().AddUObject(this, &UInteractionComponent::BindInputActions);
	}
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const AGamePlayerCharacter* const PlayerCharacter = Cast<AGamePlayerCharacter>(GetOwner());

	if (!IsValid(PlayerCharacter))
	{
		return;
	}

	UHUDManager* const HudManager = PlayerCharacter->GetHudManager();
	if (!IsValid(HudManager))
	{
		return;
	}

	HudManager->HideInteractionPrompt();
	m_CurrentInteractionTarget = nullptr;
	for(IInteractableInterface* InteractableActor : m_PotentialInteractionActors)
	{
		const AActor* InteractionActor = Cast<AActor>(InteractableActor);
		if(FVector::DistSquared(InteractionActor->GetActorLocation(), GetOwner()->GetActorLocation()) < m_InteractionDistance * m_InteractionDistance)
		{
			HudManager->DisplayInteractionPrompt(InteractionActor->GetActorLocation());
			m_CurrentInteractionTarget = InteractableActor;
		}
	}
}

