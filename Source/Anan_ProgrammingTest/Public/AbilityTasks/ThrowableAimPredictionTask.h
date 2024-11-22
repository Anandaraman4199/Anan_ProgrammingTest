// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ThrowableAimPredictionTask.generated.h"


/**
 * 
 */
UCLASS()
class ANAN_PROGRAMMINGTEST_API UThrowableAimPredictionTask : public UAbilityTask
{
	GENERATED_BODY()

	float ThrowVelocity, ProjectileRadius;

	FVector StartOffset;

	UMaterial* DecalMaterial;

protected:

	void Activate() override;

	void TickTask(float DeltaTime) override;

public:

	class UDecalComponent* TargetDecalComponent;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "ThrowableAimPrediction", DefaultToSelf = "OwningAbility", HidePin = "OwningAbility"))
	static UThrowableAimPredictionTask* ThrowableAimPrediction(UGameplayAbility* OwningAbility,float ThrowVelocity, float ProjectileRadius, FVector StartOffset, UMaterial* DecalMaterial);
	
};
