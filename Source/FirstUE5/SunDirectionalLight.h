// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SunDirectionalLight.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTUE5_API USunDirectionalLight : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "DayCycle")
	float m_TimeScale;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int m_Test;
};
