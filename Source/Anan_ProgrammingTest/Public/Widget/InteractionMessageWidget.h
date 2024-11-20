// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionMessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANAN_PROGRAMMINGTEST_API UInteractionMessageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeConstruct() override;

	/** Text Widget to show the interaction Message and binding it with the blueprint one*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TXT_InteractionMessage;

	/** Use this function to show the Interaction Message with the provided text*/
	UFUNCTION(BlueprintCallable)
	void ShowInteractionMessage(FText Message);

	/** Use this function to hide the Interaction Message*/
	UFUNCTION(BlueprintCallable)
	void HideInteractionMessage();
};
