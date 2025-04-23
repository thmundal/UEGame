// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HUDManager.generated.h"

class UPlayerMenuWidget;
class UDataTable;
class UGameHudSettings;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UPlayerHudWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class FIRSTUE5_API UHUDManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHUDManager();
	
protected:
	void PlayerMenuToggle();

	UFUNCTION()
	void BindInputActions(UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem, UEnhancedInputComponent* EnhancedInputComponent);
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPlayerHudWidget* GetOverlayHud() const { return m_GameHUD; };
	void DisplayInteractionPrompt(FVector WorldPosition);
	void HideInteractionPrompt();
	
private:
	UUserWidget* m_CachedInteractionPromptWidget;
	
	UPROPERTY()
	const UGameHudSettings* m_GameHudSettings = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UDataTable> m_InputActions;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* m_InputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	int32 m_InputContextPriority = 0;
	
	UPROPERTY()
	UPlayerMenuWidget* m_PlayerMenuWidget;

	UPROPERTY()
	UPlayerHudWidget* m_GameHUD;
};
