// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Runtime/Engine/Classes/Engine/DataTable.h>

#include "InputMappingContext.h"
#include "MyCharacter.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;

UCLASS()
class FIRSTUE5_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UEnhancedInputComponent* m_InputComponent;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UDataTable> m_InputActions;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* m_InputContext;
	
public:
	// Sets default values for this character's properties
	AMyCharacter();

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

	TMap<FName, FText> InputMap;
};
