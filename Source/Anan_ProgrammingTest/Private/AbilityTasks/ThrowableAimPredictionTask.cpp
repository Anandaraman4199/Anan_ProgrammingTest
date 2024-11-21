// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/ThrowableAimPredictionTask.h"
#include "Kismet/GameplayStatics.h"

void UThrowableAimPredictionTask::Activate()
{
	bTickingTask = true;
}

void UThrowableAimPredictionTask::TickTask(float DeltaTime)
{
	FVector StartLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation() +
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * StartOffset.X +
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorRightVector() * StartOffset.Y +
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorUpVector() * StartOffset.Z;

	FVector Velocity = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * ThrowVelocity;

	FPredictProjectilePathParams PathParam(ProjectileRadius,StartLocation,Velocity,5,ECC_WorldStatic, UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FPredictProjectilePathResult PathResult;

	UGameplayStatics::PredictProjectilePath(GetWorld(), PathParam, PathResult);

	for (int i = 0; i < PathResult.PathData.Num(); i++)
	{
		DrawDebugSphere(GetWorld(), PathResult.PathData[i].Location, ProjectileRadius, 12, FColor::Green, false, -1);
	}

	DrawDebugSphere(GetWorld(), PathResult.HitResult.Location, ProjectileRadius, 12, FColor::Red, false, -1);
}

UThrowableAimPredictionTask* UThrowableAimPredictionTask::ThrowableAimPrediction(UGameplayAbility* OwningAbility, float ThrowVelocity, float ProjectileRadius, FVector StartOffset)
{
	UThrowableAimPredictionTask* Task = NewAbilityTask<UThrowableAimPredictionTask>(OwningAbility);
	Task->ThrowVelocity = ThrowVelocity;
	Task->ProjectileRadius = ProjectileRadius;
	Task->StartOffset = StartOffset;
	return Task;
}
