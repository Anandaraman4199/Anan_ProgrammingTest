// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MoveCharacterAbilityTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskCompletedDelegated, bool, bCancelled);
/**
 * 
 */
UCLASS()
class ANAN_PROGRAMMINGTEST_API UMoveCharacterAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

private:

	// Variables needed to run this task

	FVector TargetLocation;

	float MovementSpeed;
	
	AActor* Character;

protected:

	void Activate() override;

	void TickTask(float DeltaTime) override;


public:

	/** This function moves the character to the Target Location in the Given Speed*/
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "Move Character", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UMoveCharacterAbilityTask* MoveCharacter(UGameplayAbility* OwningAbility, AActor* Character, FVector TargetLocation, float MovementSpeed);

	/** This Delegate will broadcasted when this task ends*/
	UPROPERTY(BlueprintAssignable)
	FOnTaskCompletedDelegated OnCompleted;
};
