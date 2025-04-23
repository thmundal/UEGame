// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHudSettings.h"
#include "PlayerHudWidget.h"
#include "PlayerMenuWidget.h"


TSubclassOf<UPlayerMenuWidget> UGameHudSettings::GetPlayerMenuWidget() const
{
	return m_PlayerMenuWidget;
}

TSubclassOf<UPlayerHudWidget> UGameHudSettings::GetOverlayHud() const
{
	return m_OvelayHud;
}

TSubclassOf<UUserWidget> UGameHudSettings::GetInteractionPromptWidget() const
{
	return m_InteractionPromptWidget;
}

const UGameHudSettings* UGameHudSettings::Get()
{
	return GetDefault<UGameHudSettings>();
}

FName UGameHudSettings::GetCategoryName() const
{
	return TEXT("Game");
}
