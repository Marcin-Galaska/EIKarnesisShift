// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EIKSPlayerState.h"
#include "Entity/GAS/EIKSAbilitySystemComponent.h"

void AEIKSPlayerState::CurrentHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Current Health Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AEIKSPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Max Health Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AEIKSPlayerState::CurrentStaminaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Current Stamina Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AEIKSPlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Max Stamina Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AEIKSPlayerState::EntityLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Entity Level Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AEIKSPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if(NewCount > 0)
	{
		//Cancels normal abilities
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		//Stops uncancellable abilities from cancelling
		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCancelledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}

void AEIKSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	//Boilerplate
	if(AbilitySystemComponent)
	{
		CurrentHealthChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentHealthAttribute()).AddUObject(this,
			&AEIKSPlayerState::CurrentHealthChanged);
		MaxHealthChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this,
			&AEIKSPlayerState::MaxHealthChanged);
		CurrentStaminaChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentStaminaAttribute()).AddUObject(this,
			&AEIKSPlayerState::CurrentStaminaChanged);
		CurrentStaminaChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentStaminaAttribute()).AddUObject(this,
			&AEIKSPlayerState::CurrentStaminaChanged);
		EntityLevelChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetEntityLevelAttribute()).AddUObject(this,
			&AEIKSPlayerState::EntityLevelChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this,
			&AEIKSPlayerState::StunTagChanged);
	}
}

AEIKSPlayerState::AEIKSPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UEIKSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); //If you are making a multiplayer project, best set it to Minimal.

	AttributeSet = CreateDefaultSubobject<UEIKSAttributeSet>(TEXT("BaseAttributeSet"));

	NetUpdateFrequency = 100.0f;
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* AEIKSPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UEIKSAttributeSet* AEIKSPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

bool AEIKSPlayerState::IsAlive() const
{
	return (GetCurrentHealth() > 0.0f) ? true : false;
}

float AEIKSPlayerState::GetCurrentHealth() const
{
	return AttributeSet->GetCurrentHealth();
}

float AEIKSPlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float AEIKSPlayerState::GetCurrentStamina() const
{
	return AttributeSet->GetCurrentStamina();
}

float AEIKSPlayerState::GetMaxStamina() const
{
	return AttributeSet->GetMaxStamina();
}

int32 AEIKSPlayerState::GetEntityLevel() const
{
	return AttributeSet->GetEntityLevel();
}
