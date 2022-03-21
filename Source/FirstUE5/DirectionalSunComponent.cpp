// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalSunComponent.h"

// Sets default values for this component's properties
UDirectionalSunComponent::UDirectionalSunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDirectionalSunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDirectionalSunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FRotator RotationValues(0, m_TimeScale * DeltaTime, 0);
	FQuat QuatRotation = FQuat(RotationValues);
	AActor* Owner = GetOwner();

	if (IsValid(Owner))
	{
		GetOwner()->AddActorLocalRotation(FQuat::MakeFromEuler(FVector3d(0, m_TimeScale * DeltaTime, 0)));
	}
}

