// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DataTableSettings.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS(Config="Game", DefaultConfig, meta = (DisplayName="Data table Settings"))
class FIRSTUE5_API UDataTableSettings final: public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Input")
	TSoftObjectPtr<UDataTable> m_InputActions;

	static const UDataTableSettings* Get();
	UDataTable* LoadDataTable(TSoftObjectPtr<UDataTable> DataTable) const;
};
