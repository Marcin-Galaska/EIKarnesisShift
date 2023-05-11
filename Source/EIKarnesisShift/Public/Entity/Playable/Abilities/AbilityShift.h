// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShiftIndicatorActor.h"
#include "Entity/GAS/EIKSGameplayAbility.h"
#include "AbilityShift.generated.h"

/**
 * 
 */
UCLASS()
class EIKARNESISSHIFT_API UAbilityShift : public UEIKSGameplayAbility
{
private:
	GENERATED_BODY()
protected:
	AShiftIndicatorActor* ShiftActor = nullptr; //Actor that indicates teleport location
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shift")
		 UParticleSystem* Indicator_VFX; //Particle system that follows camera and point the teleport location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shift")
		float Range = 1200; //Max teleport range
	
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
