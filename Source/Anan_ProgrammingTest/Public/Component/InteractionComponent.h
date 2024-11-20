// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

/** Interaction Component takes care of Look At and Interact Functions*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANAN_PROGRAMMINGTEST_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Returns actor which is infront of the player*/
	UPROPERTY(BlueprintReadOnly)
	AActor* LookAtActor;

	/** Decides how long the Line Trace will be from the camera*/
	UPROPERTY(EditDefaultsOnly, Category = "InitializeComponent")
	float LineTraceDistance = 500;

	/** Mapping Context which Interaction Key*/
	UPROPERTY(EditDefaultsOnly, Category = "InitializeComponent|Input")
	const class UInputMappingContext* InteractionMappingContext;

	/** Interact Input Action*/
	UPROPERTY(EditDefaultsOnly, Category = "InitializeComponent|Input")
	const class UInputAction* InteractAction;

	//InteractionMessage Widget 
	UPROPERTY(EditDefaultsOnly, Category = "InitializeComponent|Widget")
	TSubclassOf<class UInteractionMessageWidget> InteractionWidgetClass;

	// Trace Collision Query Params
	FCollisionQueryParams TraceCollisionParams;

private:
	// LookAt Function will find what is infront of the player and stores the actor in LookAtActor Variable. This will be called in Tick.
	void LookAt();

	// This function will be trigged when the player press Interact Input Action
	void Interact();
	
	//Store the owning Character
	ACharacter* Character;

	//Holds Player Camera Component
	class UCameraComponent* PlayerCamera;

	//Player Controller
	APlayerController* PlayerController;

	//Hold Interaction Message Widget after creating it
	UInteractionMessageWidget* InteractionWidget;

	// To check whether we already in Interaction
	bool OnInteraction = false;

};
