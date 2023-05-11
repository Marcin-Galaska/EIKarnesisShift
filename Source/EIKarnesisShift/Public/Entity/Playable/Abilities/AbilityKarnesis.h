// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/GAS/EIKSGameplayAbility.h"
#include "AbilityKarnesis.generated.h"

/**
 * 
 */
UCLASS()
class EIKARNESISSHIFT_API UAbilityKarnesis : public UEIKSGameplayAbility
{
private:
	GENERATED_BODY()

	//Vectors used to calculate and apply the force in correct direction
	FVector StartForwardVector;
	FVector EndForwardVector;
	FVector ImpulseVector;
protected:
	UMeshComponent* HitActorMesh = nullptr; //Mesh of the actor we hit with the line trace
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Karnesis")
		float Range = 2500.0f; //How far the target can be
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Karnesis")
		float Strength = 1000.0f; //How powerful should the impulse be
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Karnesis")
		float MinDirectionalVectorLength = 0.15f; //Dead zone in which the target is knocked away from the camera and not in a set direction
	
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
