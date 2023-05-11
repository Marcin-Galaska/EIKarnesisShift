// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Playable/Abilities/AbilityShift.h"
#include <iso646.h>
#include "Camera/CameraComponent.h"
#include "Entity/Playable/EIKSPlayable.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

void UAbilityShift::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UAbilityShift::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	//Get the player character and its camera
	AEIKSPlayable* PlayerInstigator = Cast<AEIKSPlayable>(ActorInfo->AvatarActor);
	if(!PlayerInstigator)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}
	UCameraComponent* PlayerCamera = PlayerInstigator->GetFollowCamera();

	//Set parameters for line tracing
	FVector LineTraceStart = PlayerCamera->GetComponentLocation();
	FVector LineTraceEnd = LineTraceStart + Range * UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation());
	
	FCollisionQueryParams LineTraceParams(FName(TEXT("ShiftIndicator_LT")), true, PlayerInstigator);
	LineTraceParams.bTraceComplex = true;
	LineTraceParams.bReturnPhysicalMaterial = false;

	//Declare hit result
	FHitResult HitResult(ForceInit);

	//Call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel
	(
		HitResult, //result
		LineTraceStart, //start
		LineTraceEnd, //end
		ECC_Pawn, //collision channel
		LineTraceParams //params
	);

	//We use deferred spawn for the indicator since we need to give it the VFX and range of this ability
	//Deferred spawn ensures we set indicator params before it finishes spawning
	const FTransform SpawnLocAndRot
	(
		FRotator(0),
		(HitResult.bBlockingHit) ? HitResult.Location : HitResult.TraceEnd  //If the line trace hit something, set the location the the hit location
	);																		//Otherwise set it to the end of the trace
    ShiftActor = GetWorld()->SpawnActorDeferred<AShiftIndicatorActor>(AShiftIndicatorActor::StaticClass(), SpawnLocAndRot,
    	PlayerInstigator, PlayerInstigator, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	ShiftActor->SetParams(PlayerInstigator, Indicator_VFX, Range);
    ShiftActor->FinishSpawning(SpawnLocAndRot);
}

void UAbilityShift::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(bWasCancelled)
		return;

	//Teleport the player and destroy indicator actor
	ActorInfo->AvatarActor->SetActorLocation(ShiftActor->GetIndicatorWorldLocation(), false, nullptr, ETeleportType::ResetPhysics);
	ShiftActor->Destroy();
}
