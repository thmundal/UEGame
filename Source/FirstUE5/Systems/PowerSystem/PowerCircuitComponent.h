// Copyright 2025 Chaos games

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "PowerProviderComponent.h"
#include "Attributes/AttributeSetHolder.h"
#include "PowerCircuitComponent.generated.h"

class UPowerCircuitMember;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPowerBalanceChangedDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTUE5_API UPowerCircuitComponent : public UAttributeSetHolder
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerCircuitComponent();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void AttachPowerCircuitMember(UPowerCircuitMember* PowerCircuitMember);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void DetachPowerCircuitMember(UPowerCircuitMember* PowerCircuitMember);
	
	UFUNCTION(BlueprintCallable)
	float GetPowerDemand() const;

	UFUNCTION(BlueprintCallable)
	float GetPowerCapacity() const;

	UFUNCTION(BlueprintCallable)
	bool CanSupportPower(float Power) const
	{
		return GetPowerCapacity() - GetPowerDemand() >= Power;
	}

	UFUNCTION(BlueprintCallable)
	bool HasAuthority();

	UFUNCTION(BlueprintCallable)
	void BroadcastPowerBalanceChanged();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPowerBalanceChanged();

	UFUNCTION(BlueprintCallable)
	void DisableMember(UPowerCircuitMember* PowerCircuitMember);

	UFUNCTION(BlueprintCallable)
	void EnableMember(UPowerCircuitMember* PowerCircuitMember);

	FPowerBalanceChangedDelegate& GetPowerBalanceChangedDelegate();

protected:
	virtual void BeginPlay() override;

	void OnPowerDemandChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	void OnPowerCapacityChanged(const FOnAttributeChangeData& OnAttributeChangeData);

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UPowerCircuitMember>> m_PowerCircuitMembers;

	UPROPERTY(BlueprintAssignable)
	FPowerBalanceChangedDelegate m_OnPowerBalanceChanged;

	UPROPERTY(EditDefaultsOnly)
	FGameplayAttribute PowerDemandAttribute;

	UPROPERTY(EditDefaultsOnly)
	FGameplayAttribute PowerCapacityAttribute;
};
