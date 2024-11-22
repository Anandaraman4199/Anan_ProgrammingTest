// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/ThrowableAimPredictionTask.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

void UThrowableAimPredictionTask::Activate()
{
	bTickingTask = true;

	TargetDecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(1, 1, 1), FVector(0, 0, 0));
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

	TargetDecalComponent->SetWorldScale3D(FVector(75, 75, 75));
	TargetDecalComponent->SetWorldLocationAndRotation(PathResult.HitResult.Location, PathResult.HitResult.Normal.Rotation());

}

UThrowableAimPredictionTask* UThrowableAimPredictionTask::ThrowableAimPrediction(UGameplayAbility* OwningAbility, float ThrowVelocity, float ProjectileRadius, FVector StartOffset, UMaterial* DecalMaterial)
{
	UThrowableAimPredictionTask* Task = NewAbilityTask<UThrowableAimPredictionTask>(OwningAbility);
	Task->ThrowVelocity = ThrowVelocity;
	Task->ProjectileRadius = ProjectileRadius;
	Task->StartOffset = StartOffset;
	Task->DecalMaterial = DecalMaterial;
	return Task;
}
