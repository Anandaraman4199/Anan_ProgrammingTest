// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/ThrowGameplayAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Anan_ProgrammingTest/Anan_ProgrammingTestCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilityTasks/ThrowableAimPredictionTask.h"
#include "Actor/ThrowableActor.h"



UThrowGameplayAbility::UThrowGameplayAbility(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UThrowGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Player = Cast<AAnan_ProgrammingTestCharacter>(GetAvatarActorFromActorInfo());

	// Get Player Enhanced Input Component 

	SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetLocalPlayer());
	InputComp = Cast<UEnhancedInputComponent>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->InputComponent);

	// Check Cooldown
	if (!CheckCooldown(Handle, ActorInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	// Get Mapping Context and Input Actions from the Player
	// Set Throwable Input Mapping Context with Priority 2

	SubSystem->AddMappingContext(Player->ThrowableMappingContext, 2);

	// Bind those Aim and Throw Function to this ability Functions

	InputComp->BindAction(Player->AimAction, ETriggerEvent::Started, this, &UThrowGameplayAbility::AimPressed);
	InputComp->BindAction(Player->AimAction, ETriggerEvent::Completed, this, &UThrowGameplayAbility::AimReleased);
	InputComp->BindAction(Player->ThrowAction, ETriggerEvent::Triggered, this, &UThrowGameplayAbility::Throw);
}

void UThrowGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	SubSystem->RemoveMappingContext(Player->ThrowableMappingContext);

	InputComp->ClearBindingsForObject(this);
}

void UThrowGameplayAbility::AimPressed()
{
	Task = UThrowableAimPredictionTask::ThrowableAimPrediction(this, ThrowVelocity, ProjectileRadius,Player->ThrowStartOffset);
	Task->ReadyForActivation();
}

void UThrowGameplayAbility::AimReleased()
{
	Task->EndTask();
}

void UThrowGameplayAbility::Throw()
{
	

	//Calculate StartLocation
	FVector StartLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation() +
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * Player->ThrowStartOffset.X +
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorRightVector() * Player->ThrowStartOffset.Y +
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorUpVector() * Player->ThrowStartOffset.Z;

	//Calculate StartRotation
	FRotator SpawnRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector().Rotation();

	AThrowableActor* SpawnedActor = GetWorld()->SpawnActorDeferred<AThrowableActor>(ThrowableProjectileClass.Get(), 
		FTransform(SpawnRotation, StartLocation, FVector(1, 1, 1)), 
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (SpawnedActor)
	{
		SpawnedActor->ProjectileMovementComp->InitialSpeed = ThrowVelocity;
		SpawnedActor->ProjectileMovementComp->MaxSpeed = ThrowVelocity;

		UGameplayStatics::FinishSpawningActor(SpawnedActor, FTransform(SpawnRotation, StartLocation, FVector(1, 1, 1)));
	}

	CommitAbilityCooldown(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}