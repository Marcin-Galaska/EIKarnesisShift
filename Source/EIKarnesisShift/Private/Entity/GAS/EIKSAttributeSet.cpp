// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/GAS/EIKSAttributeSet.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

void UEIKSAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEIKSAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEIKSAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEIKSAttributeSet, CurrentStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEIKSAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEIKSAttributeSet, EntityLevel, COND_None, REPNOTIFY_Always);
}

void UEIKSAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldCurrentHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEIKSAttributeSet, CurrentHealth, OldCurrentHealth);
}

void UEIKSAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEIKSAttributeSet, MaxHealth, OldMaxHealth);
}

void UEIKSAttributeSet::OnRep_CurrentStamina(const FGameplayAttributeData& OldCurrentStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEIKSAttributeSet, CurrentStamina, OldCurrentStamina);
}

void UEIKSAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEIKSAttributeSet, MaxStamina, OldMaxStamina);
}

void UEIKSAttributeSet::OnRep_EntityLevel(const FGameplayAttributeData& OldEntityLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEIKSAttributeSet, EntityLevel, OldEntityLevel);
}