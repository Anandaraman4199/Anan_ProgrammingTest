// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ANAN_PROGRAMMINGTEST_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/** Look At function will decide what to do when we look at Interactable Actors
	It will return a bool, whether we can interact with it or not */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LookAt(bool& CanInteract, FText& WidgetMessage);

	/** Use this function to interact with the Interactable Actors.
		Make sure that this object is interactable using LookAt function */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();

};
