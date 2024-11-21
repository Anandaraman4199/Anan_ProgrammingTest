// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/MoveCharacterAbilityTask.h"
#include "GameFramework/Character.h"


void UMoveCharacterAbilityTask::Activate()
{
	UE_LOG(LogTemp, Warning, TEXT("Dashing Activate"));
	// This allows the Tick Task to run
	bTickingTask = true;
}

void UMoveCharacterAbilityTask::TickTask(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Dashing"));

	if (!Character)
	{
		OnCompleted.Broadcast(true);
		EndTask();
		return;
	}

	FVector NewLocation = FMath::VInterpConstantTo(Character->GetActorLocation(), TargetLocation, DeltaTime, MovementSpeed);


	if (!Character->SetActorLocation(NewLocation, true))
	{
		OnCompleted.Broadcast(true);
		EndTask();
		return;
	}

	if (Character->GetActorLocation().Equals(TargetLocation))
	{
		OnCompleted.Broadcast(false);
		EndTask();
	}


}

UMoveCharacterAbilityTask* UMoveCharacterAbilityTask::MoveCharacter(UGameplayAbility* OwningAbility, AActor* Character, FVector TargetLocation, float MovementSpeed)
{
	UMoveCharacterAbilityTask* Task = NewAbilityTask<UMoveCharacterAbilityTask>(OwningAbility);
	Task->Character = Character;
	Task->TargetLocation = TargetLocation;
	Task->MovementSpeed = MovementSpeed;
	return Task;
}
