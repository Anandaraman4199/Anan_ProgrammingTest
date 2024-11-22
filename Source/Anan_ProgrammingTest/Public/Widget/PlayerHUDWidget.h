// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANAN_PROGRAMMINGTEST_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPlayerHUDWidget(const FObjectInitializer& ObjIni);

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponChanged(const FString& NewWeaponName);

	UFUNCTION(BlueprintImplementableEvent)
	void CooldownValues(class UGameplayAbility* OwningAbility, const FString& AbilityName);
	
};
