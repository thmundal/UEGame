// Fill out your copyright notice in the Description page of Project Settings.


#include "SunDirectionalLight.h"

void USunDirectionalLight::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	FRotator RotationValues(0, 0, m_TimeScale * DeltaTime);
	
	AActor* Owner = GetOwner();

	if (IsValid(Owner))
	{
		GetOwner()->AddActorLocalRotation(RotationValues);
	}
}
