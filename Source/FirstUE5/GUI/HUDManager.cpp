// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDManager.h"

#include "EnhancedInputSubsystems.h"
#include <Runtime/Engine/Classes/Engine/DataTable.h>
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"

#include "GameHudSettings.h"
#include "FirstUE5/GamePlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "PlayerHudWidget.h"
#include "PlayerMenuWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "FirstUE5/InputActionNames.h"
#include "FirstUE5/UInputActionRow.h"


// Sets default values for this component's properties
UHUDManager::UHUDManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHUDManager::PlayerMenuToggle()
{
	if (m_PlayerMenuWidget != nullptr)
	{
		if (m_PlayerMenuWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			m_PlayerMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			m_PlayerMenuWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UHUDManager::BindInputActions(UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem,
                                   UEnhancedInputComponent* EnhancedInputComponent)
{
	const UDataTable* InputActions = m_InputActions.LoadSynchronous();
	if (IsValid(InputActions) && IsValid(EnhancedInputComponent) && IsValid(EnhancedInputLocalPlayerSubsystem))
	{
		const FInputActionRow* PlayerMenuToggleRow = InputActions->FindRow<FInputActionRow>(InputAction::PlayerMenuToggle, TEXT("Could not find input action for PlayerMenuToggle"));

		if (PlayerMenuToggleRow != nullptr)
		{
			EnhancedInputComponent->BindAction(PlayerMenuToggleRow->InputAction, ETriggerEvent::Triggered, this, &UHUDManager::PlayerMenuToggle);
			
			FModifyContextOptions ContextOptions;
			ContextOptions.bForceImmediately = false;
			ContextOptions.bIgnoreAllPressedKeysUntilRelease = false;
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(m_InputContext, m_InputContextPriority, ContextOptions);
		}
	}
}


// Called when the game starts
void UHUDManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	m_GameHudSettings = UGameHudSettings::Get();

	const TSubclassOf<UPlayerMenuWidget> PlayerMenuWidgetPtr = m_GameHudSettings->GetPlayerMenuWidget();
	if (IsValid(PlayerMenuWidgetPtr))
	{
		m_PlayerMenuWidget = CreateWidget<UPlayerMenuWidget>(GetWorld(), PlayerMenuWidgetPtr);

		if (m_PlayerMenuWidget != nullptr)
		{
			m_PlayerMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
			m_PlayerMenuWidget->AddToViewport();
		}
	}

	const TSubclassOf<UPlayerHudWidget> GameHUDPtr = m_GameHudSettings->GetOverlayHud();
	if (IsValid(GameHUDPtr))
	{
		m_GameHUD = CreateWidget<UPlayerHudWidget>(GetWorld(), GameHUDPtr);

		if (m_GameHUD != nullptr)
		{
			m_GameHUD->AddToViewport();
		}
	}

	AGamePlayerCharacter* PlayerCharacter = Cast<AGamePlayerCharacter>(GetOwner());
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->OnPlayerInputComponentSetup().AddUObject(this, &UHUDManager::BindInputActions);
	}
}


// Called every frame
void UHUDManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHUDManager::DisplayInteractionPrompt(FVector WorldPosition)
{
	const AGamePlayerCharacter* PlayerCharacter = Cast<AGamePlayerCharacter>(GetOwner());
	if (!IsValid(PlayerCharacter))
	{
		return;
	}

	APlayerController* PlayerController = PlayerCharacter->GetLocalViewingPlayerController();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
	if (!IsValid(m_CachedInteractionPromptWidget))
	{
		const TSubclassOf<UUserWidget> InteractionPromptWidgetPtr = m_GameHudSettings->GetInteractionPromptWidget();
		if (!IsValid(InteractionPromptWidgetPtr))
		{
			return;
		}
		// Create widget here
		m_CachedInteractionPromptWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionPromptWidgetPtr);
		if (!IsValid(m_CachedInteractionPromptWidget))
		{
			return;
		}
		m_CachedInteractionPromptWidget->AddToViewport();
	}


	if (IsValid(m_CachedInteractionPromptWidget))
	{
		m_CachedInteractionPromptWidget->SetVisibility(ESlateVisibility::Visible);
		FVector2D ScreenPosition;
		if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerController, WorldPosition, ScreenPosition, true))
		{
			m_CachedInteractionPromptWidget->SetPositionInViewport(ScreenPosition);
		}
		else
		{
			HideInteractionPrompt();
		}
	}
	
}

void UHUDManager::HideInteractionPrompt()
{
	if (IsValid(m_CachedInteractionPromptWidget))
	{
		m_CachedInteractionPromptWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
