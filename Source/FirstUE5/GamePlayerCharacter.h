// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "FirstUE5/Systems/Interaction/InteractionComponent.h"
#include "GamePlayerCharacter.generated.h"

class UHUDManager;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UEnhancedInputComponent;
class UInputMappingContext;
class UDataTable;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerInputComponentSetupDelegate, UEnhancedInputLocalPlayerSubsystem*, UEnhancedInputComponent*);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerInputComponentSetupDelegate, UEnhancedInputLocalPlayerSubsystem*, A, UEnhancedInputComponent*, B);


UCLASS()
class FIRSTUE5_API AGamePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category="Interaction")
	UInteractionComponent* m_InteractionComponent;
	
	UPROPERTY(Transient)
	UEnhancedInputComponent* m_InputComponent;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UDataTable> m_InputActions;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* m_InputContext;

	UPROPERTY(EditDefaultsOnly)
	UHUDManager* m_HudManager;
	
	FOnPlayerInputComponentSetupDelegate m_OnPlayerInputComponentSetup;
	
public:
	// Sets default values for this character's properties
	AGamePlayerCharacter();

	FOnPlayerInputComponentSetupDelegate& OnPlayerInputComponentSetup() { return m_OnPlayerInputComponentSetup; }
	UEnhancedInputComponent* GetInputComponent() const { return m_InputComponent; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BindInputActions(UEnhancedInputLocalPlayerSubsystem* InInputSystem, UEnhancedInputComponent* InInputComponent);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForwardInputFunction(const FInputActionValue& ActionValue);
	void MouseLookInputFunction(const FInputActionValue& ActionValue);

	// Getters
	UHUDManager* GetHudManager() const { return m_HudManager; }

	TMap<FName, FText> InputMap;
};
