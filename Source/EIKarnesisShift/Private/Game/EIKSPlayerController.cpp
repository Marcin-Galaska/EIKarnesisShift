// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EIKSPlayerController.h"
#include "AbilitySystemComponent.h"
#include "Game/EIKSPlayerState.h"

void AEIKSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if(const AEIKSPlayerState* TempPlayerState = GetPlayerState<AEIKSPlayerState>())
		TempPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerState, InPawn);
}