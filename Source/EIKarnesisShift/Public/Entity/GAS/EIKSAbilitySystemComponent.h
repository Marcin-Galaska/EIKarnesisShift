// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EIKSAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UEIKSAbilitySystemComponent*, Instigator, float, UnmitigatedDamage, float, MitigatedDamage);

/**
 * 
 */
UCLASS()
class EIKARNESISSHIFT_API UEIKSAbilitySystemComponent : public UAbilitySystemComponent
{
private:
	GENERATED_BODY()
public:
	bool bAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;
	
	virtual void ReceiveDamage(UEIKSAbilitySystemComponent* Instigator, float UnmitigatedDamage, float MitigatedDamage);
};
