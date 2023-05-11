// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Playable/EIKSPlayable.h"
#include <ciso646>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayEffectTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Entity/GAS/EIKSAbilitySystemComponent.h"
#include "Entity/GAS/EIKSAttributeSet.h"
#include "Entity/GAS/EIKSGameplayAbility.h"
#include "Game/EIKSPlayerController.h"
#include "Game/EIKSPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

void AEIKSPlayable::HandleLookActionPressed(const FInputActionValue& Value)
{
	if(Value.GetMagnitude() != 0.0f)
	{
		AddControllerPitchInput(-1.0f * Value[1]);
		AddControllerYawInput(Value[0]);
	}
}

void AEIKSPlayable::HandleMoveActionPressed(const FInputActionValue& Value)
{
	if(Value.GetMagnitude() != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value[1]);
		AddMovementInput(GetActorRightVector(), Value[0]);
	}
}

void AEIKSPlayable::HandlePrimaryActionPressed()
{
	SendLocalInputToASC(true, EAbilityID::Primary);
}

void AEIKSPlayable::HandleSecondaryActionPressed()
{
	SendLocalInputToASC(true, EAbilityID::Secondary);
}

void AEIKSPlayable::HandleKarnesisActionPressed()
{
	SendLocalInputToASC(true, EAbilityID::Karnesis);
}

void AEIKSPlayable::HandleKarnesisActionReleased()
{
	SendLocalInputToASC(false, EAbilityID::Karnesis);
}

void AEIKSPlayable::HandleShiftActionPressed()
{
	SendLocalInputToASC(true, EAbilityID::Shift);
}

void AEIKSPlayable::HandleShiftActionReleased()
{
	SendLocalInputToASC(false, EAbilityID::Shift);
}

void AEIKSPlayable::SendLocalInputToASC(bool bIsPressed, const EAbilityID AbilityInputID)
{
	if(!AbilitySystemComponent.Get())
		return;

	if(bIsPressed)
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(AbilityInputID));
	else
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(AbilityInputID));
}

void AEIKSPlayable::InitializeASC(AEIKSPlayerState* TempPlayerState)
{
	//Initialize GAS
	AbilitySystemComponent = Cast<UEIKSAbilitySystemComponent>(TempPlayerState->GetAbilitySystemComponent());
	TempPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TempPlayerState, this);
	AttributeSet = TempPlayerState->GetAttributeSet();
	
	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);
	
	InitializeAttributes();
	
	SetCurrentHealth(GetMaxHealth());
	SetCurrentStamina(GetMaxStamina());
}

void AEIKSPlayable::BeginPlay()
{
	Super::BeginPlay();

	Controller->SetControlRotation(FRotator(180, 0, 0));

	//Save starting camera settings
	//Useful when you make abilities that change the camera position
	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
	StartingCameraBoomRotation = CameraBoom->GetComponentRotation();
}

//Replication
void AEIKSPlayable::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if(AEIKSPlayerState* TempPlayerState = GetPlayerState<AEIKSPlayerState>())
	{
		InitializeASC(TempPlayerState);
	}
}

void AEIKSPlayable::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
			Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
		}
	}
}

AEIKSPlayable::AEIKSPlayable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0,0,70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void AEIKSPlayable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	if(UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(PrimaryAction)
			PlayerEnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &AEIKSPlayable::HandlePrimaryActionPressed);

		if(SecondaryAction)
			PlayerEnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &AEIKSPlayable::HandleSecondaryActionPressed);

		if(MovementAction)
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AEIKSPlayable::HandleMoveActionPressed);

		if(LookingAction)
			PlayerEnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered, this, &AEIKSPlayable::HandleLookActionPressed);

		if(KarnesisAction)
		{
			PlayerEnhancedInputComponent->BindAction(KarnesisAction, ETriggerEvent::Triggered, this, &AEIKSPlayable::HandleKarnesisActionPressed);
			PlayerEnhancedInputComponent->BindAction(KarnesisAction, ETriggerEvent::Completed, this, &AEIKSPlayable::HandleKarnesisActionReleased);
		}

		if(ShiftAction)
		{
			PlayerEnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Triggered, this, &AEIKSPlayable::HandleShiftActionPressed);
			PlayerEnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AEIKSPlayable::HandleShiftActionReleased);
		}
		
		/* Alternative way
		if (SecondaryAction)
		{
			PlayerEnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, TEXT("Secondary Action"));
		}*/
	}
}

void AEIKSPlayable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEIKSPlayable::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(AEIKSPlayerState* TempPlayerState = GetPlayerState<AEIKSPlayerState>())
	{
		InitializeASC(TempPlayerState);
		AddStartupEffects();
		GiveAbilities();
	}
}

USpringArmComponent* AEIKSPlayable::GetCameraBoom() const
{
	return CameraBoom;
}

UCameraComponent* AEIKSPlayable::GetFollowCamera() const
{
	return FollowCamera;
}

float AEIKSPlayable::GetStartingCameraBoomArmLength() const
{
	return StartingCameraBoomArmLength;
}

FVector AEIKSPlayable::GetStartingCameraBoomLocation() const
{
	return StartingCameraBoomLocation;
}

FRotator AEIKSPlayable::GetStartingCameraBoomRotation() const
{
	return StartingCameraBoomRotation;
}

