#pragma once
#include "InputAction.h"
#include "Engine/DataTable.h"

#include "UInputActionRow.generated.h"

USTRUCT(BlueprintType)
struct FInputActionRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* InputAction;
};
