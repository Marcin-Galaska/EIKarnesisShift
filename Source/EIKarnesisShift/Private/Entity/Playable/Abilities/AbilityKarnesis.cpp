// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Playable/Abilities/AbilityKarnesis.h"
#include <ciso646>
#include "Camera/CameraComponent.h"
#include "Entity/Playable/EIKSPlayable.h"
#include "Kismet/KismetMathLibrary.h"

void UAbilityKarnesis::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UAbilityKarnesis::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//Get the player character and its camera
	AEIKSPlayable* PlayerInstigator = Cast<AEIKSPlayable>(ActorInfo->AvatarActor);
	if(!PlayerInstigator)
		return;
		
	UCameraComponent* PlayerCamera = PlayerInstigator->GetFollowCamera();

	//Set parameters for line tracing
	FVector LineTraceStart = PlayerCamera->GetComponentLocation();
	FVector LineTraceEnd = LineTraceStart + Range * UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation());
	
	FCollisionQueryParams LineTraceParams(FName(TEXT("LineTrace")), true, ActorInfo->AvatarActor.Get());
	LineTraceParams.bTraceComplex = true;
	LineTraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
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

	//If we didn't hit anything in range, cancel the ability
	if(!HitResult.bBlockingHit)
		return;

	//Get HitResult's mesh and check, whether it's movable
	UActorComponent* Component = HitResult.GetActor()->GetComponentByClass(UMeshComponent::StaticClass());
	HitActorMesh = Cast<UMeshComponent>(Component);
	if(!HitActorMesh or HitActorMesh->Mobility != EComponentMobility::Movable)
		return;

	//Vector that will be the start of ImpulseVector
	StartForwardVector = UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation());
	
	CommitAbility(Handle, ActorInfo, ActivationInfo);
}

void UAbilityKarnesis::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(bWasCancelled or !HitActorMesh)
		return;

	//Get the player character and its camera
	AEIKSPlayable* PlayerInstigator = Cast<AEIKSPlayable>(ActorInfo->AvatarActor);
	if(!PlayerInstigator)
		return;
	
	UCameraComponent* PlayerCamera = PlayerInstigator->GetFollowCamera();

	//Vector that will be the end of ImpulseVector
	EndForwardVector = UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation());

	//Vector given to the target
	ImpulseVector = EndForwardVector - StartForwardVector;

	//If the impulse vector is shorter than the set minimum, it is treated like 0 and the impulse vector is set to be parallel to the ability instigator
	//In short, the vector is short, so we knock the target away instead of in the desired direction
	if(ImpulseVector.Length() <= MinDirectionalVectorLength)
	{
		ImpulseVector = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation
			(
			PlayerCamera->GetComponentLocation(), HitActorMesh->GetComponentLocation()
			)
		);
	}

	//Set the ImpulseVector's length accordingly to set ability strength
	ImpulseVector.Normalize(0.0001);
	ImpulseVector *= Strength;

	//Apply the impulse. We first set the velocities to 0 to get the desired effect if the target is moving
	HitActorMesh->SetAllPhysicsLinearVelocity(FVector(0, 0, 0), false);
	HitActorMesh->AddImpulse(ImpulseVector, NAME_None, true);
}
