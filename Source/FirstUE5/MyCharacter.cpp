// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "MyPlayerController.h"
#include "UInputActionRow.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	const APlayerController* PlayerController = GetLocalViewingPlayerController();
	if(IsValid(PlayerController) && IsValid(m_InputComponent))
	{
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if(IsValid(LocalPlayer))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				BindInputActions(Subsystem, m_InputComponent);
			}
		}
	}
	
}

PRAGMA_DISABLE_OPTIMIZATION
void AMyCharacter::BindInputActions(UEnhancedInputLocalPlayerSubsystem* InInputSystem, UEnhancedInputComponent* InInputComponent)
{
	const UDataTable* InputActions = m_InputActions.Get();
	if(IsValid(InputActions))
	{
		// InputActions->ForeachRow<FInputActionRow>(TEXT("Something went booboo"),
		// 	[&](const FName& Key, const FInputActionRow& Value) {
		// 		InInputComponent->BindAction(Value.InputAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveForwardInputFunction);
		// 	}
		// );

		const FInputActionRow* ForwardActionRow = InputActions->FindRow<FInputActionRow>(TEXT("Forward"), TEXT("THIS DID NOT WORK"));
		InInputComponent->BindAction(ForwardActionRow->InputAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveForwardInputFunction);
		
		const FInputActionRow* MouseLookActionRow = InputActions->FindRow<FInputActionRow>(TEXT("MouseLook"), TEXT("THIS DID NOT WORK"));
		InInputComponent->BindAction(MouseLookActionRow->InputAction, ETriggerEvent::Triggered, this, &AMyCharacter::MouseLookInputFunction);

		const FInputActionRow* JumpActionRow = InputActions->FindRow<FInputActionRow>(TEXT("Jump"), TEXT("THIS DID NOT WORK"));
		InInputComponent->BindAction(JumpActionRow->InputAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);

		InInputSystem->AddMappingContext(m_InputContext, 1, false);
	}
}
PRAGMA_ENABLE_OPTIMIZATION

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		m_InputComponent = PlayerEnhancedInputComponent;
	}
}

void AMyCharacter::MoveForwardInputFunction(const FInputActionValue& ActionValue)
{
	const FVector2d InputAxis = ActionValue.Get<FVector2d>();
	const FVector RawInput = FVector(InputAxis.X, InputAxis.Y, 0);
	const FVector MovementDirection = GetActorQuat() * RawInput;
	AddMovementInput(MovementDirection);
}

void AMyCharacter::MouseLookInputFunction(const FInputActionValue& ActionValue)
{
	const FVector2d InputAxis = ActionValue.Get<FVector2d>();
	AddControllerPitchInput(-InputAxis.Y);
	AddControllerYawInput(InputAxis.X);
}
