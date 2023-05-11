// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EIKSAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class EIKARNESISSHIFT_API UEIKSAttributeSet : public UAttributeSet
{
private:
	GENERATED_BODY()
public:
	//Used for attribute replication (multiplayer).
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//Default attributes - health, stamina, level and two types of damage.
	//These are examples, use whatever attributes you desire.
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_CurrentHealth)
		FGameplayAttributeData CurrentHealth;
		ATTRIBUTE_ACCESSORS(UEIKSAttributeSet, CurrentHealth)
	UFUNCTION()
		virtual void OnRep_CurrentHealth(const FGameplayAttributeData& OldCurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
		ATTRIBUTE_ACCESSORS(UEIKSAttributeSet, MaxHealth)
	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stamina", ReplicatedUsing = OnRep_CurrentStamina)
		FGameplayAttributeData CurrentStamina;
		ATTRIBUTE_ACCESSORS(UEIKSAttributeSet, CurrentStamina)
	UFUNCTION()
		virtual void OnRep_CurrentStamina(const FGameplayAttributeData& OldCurrentStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stamina", ReplicatedUsing = OnRep_MaxStamina)
		FGameplayAttributeData MaxStamina;
		ATTRIBUTE_ACCESSORS(UEIKSAttributeSet, MaxStamina)
	UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|EntityLevel", ReplicatedUsing = OnRep_EntityLevel)
		FGameplayAttributeData EntityLevel;
		ATTRIBUTE_ACCESSORS(UEIKSAttributeSet, EntityLevel)
	UFUNCTION()
		virtual void OnRep_EntityLevel(const FGameplayAttributeData& OldEntityLevel);
};
