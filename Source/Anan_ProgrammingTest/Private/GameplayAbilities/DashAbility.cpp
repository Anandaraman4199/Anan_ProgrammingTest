// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/DashAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Anan_ProgrammingTest/Anan_ProgrammingTestCharacter.h"

UDashAbility::UDashAbility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	//Set Dash Cooldown class from Player Character

	AAnan_ProgrammingTestCharacter* Player = Cast<AAnan_ProgrammingTestCharacter>(GetAvatarActorFromActorInfo());

	CooldownGameplayEffectClass = Player->DashCooldownClass;


	// Check are we already on a Cooldown

	if (!CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, false))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}


	//Get Player Input Values from the Player Character and Calculate the direction and apply it to the Velocity of Character Movement Component

	UCharacterMovementComponent* PlayerCharacterMovement = GetAvatarActorFromActorInfo()->GetComponentByClass<UCharacterMovementComponent>();
	
	FVector2D InputValues = Player->PlayerMoveInputValues;

	FVector Direction = GetAvatarActorFromActorInfo()->GetActorForwardVector() * InputValues.Y +GetAvatarActorFromActorInfo()->GetActorRightVector() * InputValues.X;

	Direction.Normalize();

	PlayerCharacterMovement->Velocity = Direction * Player->DashSpeed;

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);

}
