// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerCharacter.h"

#include <Runtime/Engine/Classes/Engine/DataTable.h>

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputActionNames.h"
#include "InputTriggers.h"
#include "UInputActionRow.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "MyPlayerController.h"
#include "GUI/HUDManager.h"

PRAGMA_DISABLE_OPTIMIZATION

// Sets default values
AGamePlayerCharacter::AGamePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bReplicates = true;
	m_HudManager = CreateDefaultSubobject<UHUDManager>(TEXT("HudManager"));
}

// Called when the game starts or when spawned
void AGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	ENetMode NetMode = GetNetMode();

	m_InteractionComponent = FindComponentByClass<UInteractionComponent>();
}

void AGamePlayerCharacter::BindInputActions(UEnhancedInputLocalPlayerSubsystem* InInputSystem, UEnhancedInputComponent* InInputComponent)
{
	const UDataTable* InputActions = m_InputActions.LoadSynchronous();
	if(IsValid(InputActions))
	{
		const FInputActionRow* ForwardActionRow = InputActions->FindRow<FInputActionRow>(InputAction::MovementForward, TEXT("Could not find input action for MovementForward"));
		if (ForwardActionRow != nullptr)
		{
			InInputComponent->BindAction(ForwardActionRow->InputAction, ETriggerEvent::Triggered, this, &AGamePlayerCharacter::MoveForwardInputFunction);
		}
		
		const FInputActionRow* MouseLookActionRow = InputActions->FindRow<FInputActionRow>(InputAction::MouseLook, TEXT("Could not find input action for MouseLook"));
		if (MouseLookActionRow != nullptr)
		{
			InInputComponent->BindAction(MouseLookActionRow->InputAction, ETriggerEvent::Triggered, this, &AGamePlayerCharacter::MouseLookInputFunction);
		}

		const FInputActionRow* JumpActionRow = InputActions->FindRow<FInputActionRow>(InputAction::Jump, TEXT("Could not find input action for Jump"));
		if (JumpActionRow != nullptr)
		{
			InInputComponent->BindAction(JumpActionRow->InputAction, ETriggerEvent::Triggered, this, &AGamePlayerCharacter::Jump);
		}

		FModifyContextOptions ContextOptions;
		ContextOptions.bForceImmediately = false;
		ContextOptions.bIgnoreAllPressedKeysUntilRelease = false;
		InInputSystem->AddMappingContext(m_InputContext, 1, ContextOptions);
	}
}

// Called every frame
void AGamePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGamePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		m_InputComponent = PlayerEnhancedInputComponent;
	
		const APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if(IsValid(PlayerController) && IsValid(m_InputComponent))
		{
			const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
			if(IsValid(LocalPlayer))
			{
				if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
				{
					BindInputActions(Subsystem, m_InputComponent);
					
					if (m_OnPlayerInputComponentSetup.IsBound())
					{
						m_OnPlayerInputComponentSetup.Broadcast(Subsystem, PlayerEnhancedInputComponent);
					}
				}
			}
		}
	}
}

void AGamePlayerCharacter::MoveForwardInputFunction(const FInputActionValue& ActionValue)
{
	const FVector2d InputAxis = ActionValue.Get<FVector2d>();
	const FVector RawInput = FVector(InputAxis.X, InputAxis.Y, 0);
	const FVector MovementDirection = GetActorQuat() * RawInput;
	AddMovementInput(MovementDirection);
}

void AGamePlayerCharacter::MouseLookInputFunction(const FInputActionValue& ActionValue)
{
	const FVector2d InputAxis = ActionValue.Get<FVector2d>();
	AddControllerPitchInput(-InputAxis.Y);
	AddControllerYawInput(InputAxis.X);
}

PRAGMA_ENABLE_OPTIMIZATION