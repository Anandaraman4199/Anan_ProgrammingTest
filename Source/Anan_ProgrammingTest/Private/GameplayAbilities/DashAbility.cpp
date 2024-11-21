// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/DashAbility.h"
#include "AbilityTasks/MoveCharacterAbilityTask.h"

void UDashAbility::OnTaskCompleted(bool IsCancelled)
{
	UE_LOG(LogTemp, Warning, TEXT("Dash Completed"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	UE_LOG(LogTemp, Warning, TEXT("Dash Started"));

	FVector TargetLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + GetAvatarActorFromActorInfo()->GetActorForwardVector() * 500;
	UMoveCharacterAbilityTask* Task = UMoveCharacterAbilityTask::MoveCharacter(this, GetAvatarActorFromActorInfo(), TargetLocation , 500);
	Task->OnCompleted.AddDynamic(this, &UDashAbility::OnTaskCompleted);
	Task->ReadyForActivation();
	
}
