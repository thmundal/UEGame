// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "InteractionComponent.generated.h"


class IInteractableInterface;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTUE5_API UInteractionComponent : public USphereComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float m_InteractionDistance;

	TSet<IInteractableInterface*> m_PotentialInteractionActors;
	IInteractableInterface* m_CurrentInteractionTarget;
	
private:
	UFUNCTION()
	void OnTriggerOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ExecuteInteraction();

	UFUNCTION(Server, Reliable)
	void ServerExecuteInteraction() const;
	
protected:
	void BindInputActions(UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem, UEnhancedInputComponent* EnhancedInputComponent);
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	float m_InteractionDetectionRadius = 100.0f;
	
	// Sets default values for this component's properties
	UInteractionComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
