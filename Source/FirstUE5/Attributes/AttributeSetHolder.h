// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/ActorComponent.h"
#include "AttributeSetHolder.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FOnAttributeChangeDataWrapper
{
	GENERATED_BODY()

	FOnAttributeChangeDataWrapper() = default;

	FOnAttributeChangeDataWrapper(const FGameplayAttribute& InAttribute, float InNewValue, float InOldValue)
		: Attribute(InAttribute)
		, NewValue(InNewValue)
		, OldValue(InOldValue)
	{ }

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(BlueprintReadOnly)
	float	NewValue;
	
	UPROPERTY(BlueprintReadOnly)
	float	OldValue;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedDelegate, const FOnAttributeChangeDataWrapper&, Change);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable)
class FIRSTUE5_API UAttributeSetHolder : public UActorComponent
{
	GENERATED_BODY()

public:
	void ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, const UAbilitySystemComponent* const Instigator);
	void RemoveGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass, UAbilitySystemComponent* const Instigator);

	TSubclassOf<UGameplayEffect> GetInitialAttributeEffectClass() const
	{
		return m_InitialAttributeEffectClass;
	}

	float GetEffectLevel() const
	{
		return m_EffectLevel;
	}
	
	UAbilitySystemComponent* GetAbilitySystemComponent() const
	{
		return m_AbilitySystemComponent;
	}

	float GetAttributeValue(const FGameplayAttribute& Attribute) const;

	UFUNCTION(BlueprintCallable)
	void BindOnAttributeChanged(FGameplayAttribute Attribute);

protected:
	void InitializeWithAbilitySystem();

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TArray<TSubclassOf<UAttributeSet>> m_AttributeSetClasses;

	void OnAttributeChanged(const FOnAttributeChangeData& AttributeChangeData);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> m_InitialAttributeEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float m_EffectLevel = 1.0f;

	UPROPERTY()
	UAbilitySystemComponent* m_AbilitySystemComponent;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedDelegate m_OnAttributeChangedDelegate;
};
