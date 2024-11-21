// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ThrowGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ANAN_PROGRAMMINGTEST_API UThrowGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
	class UEnhancedInputLocalPlayerSubsystem* SubSystem;

	class UEnhancedInputComponent* InputComp;

	class AAnan_ProgrammingTestCharacter* Player;

	class UThrowableAimPredictionTask* Task;


protected:

	 /** Specify the Projectile Class here */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AThrowableActor> ThrowableProjectileClass;

	/** This will be the Initial and Max Speed of the Projectile Movement */
	UPROPERTY(EditDefaultsOnly)
	float ThrowVelocity;

	/** This radius will be used for the Path Prediction*/
	UPROPERTY(EditDefaultsOnly)
	float ProjectileRadius;

	// Manage Aiming
	void AimPressed();

	// Cancels the aiming
	void AimReleased();

	// Manage Throw functionality
	void Throw();

	UThrowGameplayAbility(const FObjectInitializer& ObjectInitializer);

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

};
