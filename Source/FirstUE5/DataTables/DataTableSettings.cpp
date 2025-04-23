// Fill out your copyright notice in the Description page of Project Settings.

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
