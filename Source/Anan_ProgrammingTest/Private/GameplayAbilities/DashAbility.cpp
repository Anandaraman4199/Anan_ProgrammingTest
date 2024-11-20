// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/DashAbility.h"

void UDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("Dash Ability"));
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
