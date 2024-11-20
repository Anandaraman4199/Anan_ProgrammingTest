// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InteractionMessageWidget.h"
#include "Components/TextBlock.h"

void UInteractionMessageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Set the TXT_InteractionMessage visisbility to Hidden
	TXT_InteractionMessage->SetVisibility(ESlateVisibility::Hidden);
}

void UInteractionMessageWidget::ShowInteractionMessage(FText Message)
{	
	TXT_InteractionMessage->SetText(Message);
	TXT_InteractionMessage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UInteractionMessageWidget::HideInteractionMessage()
{
	TXT_InteractionMessage->SetVisibility(ESlateVisibility::Hidden);
}
