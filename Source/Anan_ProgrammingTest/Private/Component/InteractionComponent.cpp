// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InteractionComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Interface/InteractionInterface.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Widget/InteractionMessageWidget.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetComponentTickInterval(0.1f);

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	//Initialize Variables
	Character = Cast<ACharacter>(GetOwner());
	PlayerController = Cast<APlayerController>(Character->GetController());
	PlayerCamera = GetOwner()->GetComponentByClass<UCameraComponent>();
	
	if (InteractionWidgetClass)
	{ 
		InteractionWidget = CreateWidget<UInteractionMessageWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InteractionWidgetClass);
		InteractionWidget->AddToViewport();
	}
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Find and store the interactable actor which is infront of the player
	LookAt();
}

void UInteractionComponent::LookAt()
{
	// Initialize Parameters needed for Line Trace
	FHitResult OutHit;
	FVector StartLocation = PlayerCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + (PlayerCamera->GetForwardVector() * LineTraceDistance);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(Character);
	bool CanInteract = false;
	FText WidgetMessage;

	//Line Trace and check the Hit Actor has Interaction Interface
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Camera, CollisionQueryParams))
	{
		if (OutHit.GetActor()->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_LookAt(OutHit.GetActor(), CanInteract, WidgetMessage);
		}
		
	}

	// If it has add interaction mapping context to the player or remove it

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);

	LookAtActor = (CanInteract) ? OutHit.GetActor() : nullptr;

	if (CanInteract)
	{
		Subsystem->AddMappingContext(InteractionMappingContext, 1);
		
		// Interaction Action Binding
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &UInteractionComponent::Interact);

		InteractionWidget->ShowInteractionMessage(WidgetMessage);
	}
	else
	{
		Subsystem->RemoveMappingContext(InteractionMappingContext);
		InteractionWidget->HideInteractionMessage();
	}
}

void UInteractionComponent::Interact()
{
	if (LookAtActor)
	{
		IInteractionInterface::Execute_Interact(LookAtActor);
	}
}

