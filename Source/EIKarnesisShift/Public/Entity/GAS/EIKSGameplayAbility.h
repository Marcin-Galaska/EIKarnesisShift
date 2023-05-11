// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EIKSAbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbility.h"
#include "EIKarnesisShift/EIKarnesisShift.h"
#include "EIKSGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class EIKARNESISSHIFT_API UEIKSGameplayAbility : public UGameplayAbility
{
private:
	GENERATED_BODY()
public:
	UEIKSGameplayAbility();

	//Ability ID and keybind, must be filled in ability blueprint.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
		EAbilityID AbilityID = EAbilityID::None;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
		EAbilityID AbilityInputID = EAbilityID::None;

	//Whether this ability should trigger immediately after being granted to the character.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ability")
		bool bActivateAbilityOnGranted = false;
	
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
