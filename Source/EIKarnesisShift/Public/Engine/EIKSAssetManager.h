// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "Engine/AssetManager.h"
#include "EIKSAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class EIKARNESISSHIFT_API UEIKSAssetManager : public UAssetManager
{
private:
	GENERATED_BODY()
public:
	virtual void StartInitialLoading() override;
};

inline void UEIKSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	UAbilitySystemGlobals::Get().InitGlobalData();

	//This will appear in your output log if you have set this below '[/Script/Engine.Engine]' in 'Config/DefaultEngine.ini':
	//AssetManagerClassName=/Script/<Project Name>.<Asset Manager Class>
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] %s() called."), *FString(__FUNCTION__));
}
