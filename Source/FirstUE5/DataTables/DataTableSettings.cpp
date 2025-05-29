// Copyright 2025 Chaos games

#include "DataTableSettings.h"

#include <Runtime/Engine/Classes/Engine/DataTable.h>

const UDataTableSettings* UDataTableSettings::Get()
{
	return GetDefault<UDataTableSettings>();
}

UDataTable* UDataTableSettings::LoadDataTable(TSoftObjectPtr<UDataTable> DataTable) const
{
	return DataTable.LoadSynchronous();
}
