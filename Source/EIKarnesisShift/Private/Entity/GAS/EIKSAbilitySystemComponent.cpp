// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/GAS/EIKSAbilitySystemComponent.h"

void UEIKSAbilitySystemComponent::ReceiveDamage(UEIKSAbilitySystemComponent* Instigator, float UnmitigatedDamage,
	float MitigatedDamage)
{
	ReceivedDamage.Broadcast(Instigator, UnmitigatedDamage, MitigatedDamage);
}
