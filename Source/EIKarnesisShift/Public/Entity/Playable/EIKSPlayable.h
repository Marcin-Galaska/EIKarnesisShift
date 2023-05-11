// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Entity/EIKSEntity.h"
#include "EIKSPlayable.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS(config=GAME)
class EIKARNESISSHIFT_API AEIKSPlayable : public AEIKSEntity
{
private:
	GENERATED_BODY()
protected:
	//Camera transform settings
	UPROPERTY(BlueprintReadOnly, Category = "Playable|Camera")
		float StartingCameraBoomArmLength;
	UPROPERTY(BlueprintReadOnly, Category = "Playable|Camera")
		FVector StartingCameraBoomLocation;
	UPROPERTY(BlueprintReadOnly, Category = "Playable|Camera")
		FRotator StartingCameraBoomRotation;

	//Components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Playable|Camera")
		class USpringArmComponent* CameraBoom;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Playable|Camera")
		class UCameraComponent* FollowCamera;

	//Enhanced Input
	void HandleMoveActionPressed(const FInputActionValue& Value);
	void HandleLookActionPressed(const FInputActionValue& Value);
	void HandlePrimaryActionPressed();
	void HandleSecondaryActionPressed();
	void HandleKarnesisActionPressed();
	void HandleKarnesisActionReleased();
	void HandleShiftActionPressed();
	void HandleShiftActionReleased();

	void SendLocalInputToASC(bool bIsPressed, const EAbilityID AbilityInputID);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* MovementAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* LookingAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* PrimaryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* SecondaryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* ShiftAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* KarnesisAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Mappings")
		UInputMappingContext* BaseMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Mappings")
		int32 BaseMappingPriority = 0;
	
	//Helpers
	void InitializeASC(class AEIKSPlayerState* TempPlayerState);

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void PawnClientRestart() override;
public:
	AEIKSPlayable(const class FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaSeconds) override;

	//Getters
	class USpringArmComponent* GetCameraBoom() const;
	class UCameraComponent* GetFollowCamera() const;

	UFUNCTION(BlueprintCallable, Category = "Playable|Camera")
		float GetStartingCameraBoomArmLength() const;
	UFUNCTION(BlueprintCallable, Category = "Playable|Camera")
		FVector GetStartingCameraBoomLocation() const;
	UFUNCTION(BlueprintCallable, Category = "Playable|Camera")
		FRotator GetStartingCameraBoomRotation() const;
};
