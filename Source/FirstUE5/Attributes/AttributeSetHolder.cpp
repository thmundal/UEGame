// Copyright 2025 Chaos games


#include "AttributeSetHolder.h"

#include "AbilitySystemComponent.h"

DECLARE_LOG_CATEGORY_CLASS(LogAttributeSetHolder, Log, All)

void UAttributeSetHolder::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, const UAbilitySystemComponent* const Instigator)
{
	if (!IsValid(m_AbilitySystemComponent))
	{
		UE_LOG(LogAttributeSetHolder, Error, TEXT("ApplyGameplayEffect called on %s without a valid AbilitySystemComponent"), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = m_AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(Instigator);
	EffectContext.AddInstigator(Instigator->GetAvatarActor(), Instigator->GetAvatarActor());

	FGameplayEffectSpecHandle EffectSpec = m_AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContext);
	if (EffectSpec.IsValid())
	{
		m_AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
	}
}

void UAttributeSetHolder::RemoveGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass, UAbilitySystemComponent* const Instigator)
{
	if (!IsValid(m_AbilitySystemComponent))
	{
		UE_LOG(LogAttributeSetHolder, Error, TEXT("RemoveGameplayEffect called on %s without a valid AbilitySystemComponent"), *GetName());
		return;
	}

	m_AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(GameplayEffectClass, Instigator);
}

float UAttributeSetHolder::GetAttributeValue(const FGameplayAttribute& Attribute) const
{
	if (IsValid(m_AbilitySystemComponent))
	{
		return m_AbilitySystemComponent->GetNumericAttribute(Attribute);
	}

	return 0.0f;
}

void UAttributeSetHolder::BindOnAttributeChanged(FGameplayAttribute Attribute)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UAttributeSetHolder::OnAttributeChanged);
	}
	else
	{
		UE_LOG(LogAttributeSetHolder, Error, TEXT("BindOnAttributeChanged called on %s without a valid AbilitySystemComponent"), *GetName());
	}
}

void UAttributeSetHolder::InitializeWithAbilitySystem()
{
	if (!IsValid(m_AbilitySystemComponent))
	{
		UE_LOG(LogAttributeSetHolder, Error, TEXT("InitializeWithAbilitySystem called on %s without a valid AbilitySystemComponent"), *GetName());
		return;
	}

	for (const TSubclassOf<UAttributeSet>& AttributeSetClass : m_AttributeSetClasses)
	{
		if (IsValid(AttributeSetClass))
		{
			m_AbilitySystemComponent->AddAttributeSetSubobject(NewObject<UAttributeSet>(m_AbilitySystemComponent->GetOwner(), AttributeSetClass));
		}
		else
		{
			UE_LOG(LogAttributeSetHolder, Error, TEXT("InitializeWithAbilitySystem called on %s without a valid AttributeSetClass"), *GetName());
		}
	}

	if (IsValid(m_InitialAttributeEffectClass))
	{
		ApplyGameplayEffect(m_InitialAttributeEffectClass, m_EffectLevel, m_AbilitySystemComponent);
	}
}


// Called when the game starts
void UAttributeSetHolder::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (IsValid(Owner))
	{
		m_AbilitySystemComponent = Owner->FindComponentByClass<UAbilitySystemComponent>();

		if (Owner->HasAuthority())
		{
			InitializeWithAbilitySystem();
		}
	}
}

void UAttributeSetHolder::OnAttributeChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	m_OnAttributeChangedDelegate.Broadcast(FOnAttributeChangeDataWrapper(
		AttributeChangeData.Attribute,
		AttributeChangeData.NewValue,
		AttributeChangeData.OldValue));
}
