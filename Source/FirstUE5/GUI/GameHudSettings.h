// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameHudSettings.generated.h"

class UPlayerMenuWidget;
class UUserWidget;
class UPlayerHudWidget;

/**
 * 
 */
UCLASS(Config="Game", DefaultConfig, meta = (DisplayName="Game HUD Settings"))
class FIRSTUE5_API UGameHudSettings final : public UDeveloperSettings
{
	GENERATED_BODY()

protected:
	/* The widget for the main player menu */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UPlayerMenuWidget> m_PlayerMenuWidget;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UPlayerHudWidget> m_OvelayHud;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> m_InteractionPromptWidget;
	
public:
	TSubclassOf<UPlayerMenuWidget> GetPlayerMenuWidget() const;
	TSubclassOf<UPlayerHudWidget> GetOverlayHud() const;
	TSubclassOf<UUserWidget> GetInteractionPromptWidget() const;
	
	static const UGameHudSettings* Get();

	virtual FName GetCategoryName() const override;
};
