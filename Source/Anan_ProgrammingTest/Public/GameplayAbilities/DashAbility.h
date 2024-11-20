// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DashAbility.generated.h"

/**
 * 
 */
UCLASS()
class ANAN_PROGRAMMINGTEST_API UDashAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:

	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
