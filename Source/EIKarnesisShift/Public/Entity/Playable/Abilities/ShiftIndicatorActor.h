// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Playable/EIKSPlayable.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "ShiftIndicatorActor.generated.h"

UCLASS()
class EIKARNESISSHIFT_API AShiftIndicatorActor : public AActor 
{
private:
	GENERATED_BODY()
	AEIKSPlayable* OwnerActor = nullptr; //Actor that spawns this indicator i.e. the player
	UParticleSystem* Indicator_VFX = nullptr; //Particle system that follows camera and point the teleport location
	float Range = 1200; //Max teleport range
protected:
	UParticleSystemComponent* Indicator = nullptr; //The component whose location we teleport to

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Sets default values for this actor's properties
	AShiftIndicatorActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SetParams(AEIKSPlayable* InOwner, UParticleSystem* InVFX, float InRange = 1200); //Used to match params with its owner actor
	FVector GetIndicatorWorldLocation() const;
};
