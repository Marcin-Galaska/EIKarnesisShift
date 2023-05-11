// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Playable/Abilities/ShiftIndicatorActor.h"
#include "Camera/CameraComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AShiftIndicatorActor::AShiftIndicatorActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShiftIndicatorActor::SetParams(AEIKSPlayable* InOwner, UParticleSystem* InVFX, float InRange)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OwnerActor = InOwner;
	Indicator_VFX = InVFX;
	Range = InRange;
}

void AShiftIndicatorActor::BeginPlay()
{
	Super::BeginPlay();
	
	UCameraComponent* PlayerCamera = OwnerActor->GetFollowCamera();
	
	//Set parameters for line tracing
	FVector LineTraceStart = PlayerCamera->GetComponentLocation();
	FVector LineTraceEnd = LineTraceStart + Range * UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation());
	
	FCollisionQueryParams LineTraceParams(FName(TEXT("ShiftIndicator_LT")), true, OwnerActor);
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

	if(HitResult.bBlockingHit)
		Indicator = UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(), //world
			Indicator_VFX, //particle system
			HitResult.Location, 
			FRotator(0, 0, 0), //spawn transform
			FVector(1, 1, 1),
			true,
			EPSCPoolMethod::None,
			true
		);
	else
		Indicator = UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			Indicator_VFX,
			HitResult.TraceEnd,
			FRotator(0, 0, 0),
			FVector(1, 1, 1),
			true,
			EPSCPoolMethod::None,
			true
		);
}

void AShiftIndicatorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!Indicator)
		return;
	
	UCameraComponent* PlayerCamera = OwnerActor->GetFollowCamera();
	
	//Set parameters for line tracing
	FVector LineTraceStart = PlayerCamera->GetComponentLocation();
	FVector LineTraceEnd = LineTraceStart + Range * UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation());
	
	FCollisionQueryParams LineTraceParams(FName(TEXT("ShiftIndicator_LT")), true, OwnerActor);
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

	if(HitResult.bBlockingHit)
		Indicator->SetWorldLocation(HitResult.Location);
	else
		Indicator->SetWorldLocation(HitResult.TraceEnd);
}

void AShiftIndicatorActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if(Indicator)
		Indicator->DestroyComponent();
}

FVector AShiftIndicatorActor::GetIndicatorWorldLocation() const
{
	return Indicator->GetComponentLocation();
}

