// Copyright Epic Games, Inc. All Rights Reserved.

#include "Anan_ProgrammingTestCharacter.h"
#include "Anan_ProgrammingTestProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Component/InteractionComponent.h"
#include "AttributeSet/BaseAttributeSet.h"
#include "GameplayAbilities/DashAbility.h"
#include "GameplayAbilities/ThrowGameplayAbility.h"
#include "Widget/PlayerHUDWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AAnan_ProgrammingTestCharacter



AAnan_ProgrammingTestCharacter::AAnan_ProgrammingTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// Create an InteractionComponent
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

}

//////////////////////////////////////////////////////////////////////////// Input

void AAnan_ProgrammingTestCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}



void AAnan_ProgrammingTestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// Giving All Gameplay Abilities stored in the "StartingGameplayAbilities" Array to the Player
		for (int i = 0; i < StartingGameplayAbilities.Num(); i++)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartingGameplayAbilities[i]));
		}
	}

	
	PlayerHUD = CreateWidget<UPlayerHUDWidget>(Cast<APlayerController>(GetController()),PlayerHUDWidget);
	PlayerHUD->AddToViewport();
}

void AAnan_ProgrammingTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnan_ProgrammingTestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAnan_ProgrammingTestCharacter::Look);
		
		//Dashing
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AAnan_ProgrammingTestCharacter::Dash);

		//Molotov 
		EnhancedInputComponent->BindAction(MolotovInputAction, ETriggerEvent::Triggered, this, &AAnan_ProgrammingTestCharacter::Molotov);

		//SmokeGrenade 
		EnhancedInputComponent->BindAction(SmokeGrenadeInputAction, ETriggerEvent::Triggered, this, &AAnan_ProgrammingTestCharacter::SmokeGrenade);

		//Melee
		EnhancedInputComponent->BindAction(MeleeInputAction, ETriggerEvent::Triggered, this, &AAnan_ProgrammingTestCharacter::Melee);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AAnan_ProgrammingTestCharacter::Move(const FInputActionValue& Value)
{

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	PlayerMoveInputValues = MovementVector;

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);

	}
}

void AAnan_ProgrammingTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAnan_ProgrammingTestCharacter::Dash()
{
	// Try Activate Dash Ability
	AbilitySystemComponent->TryActivateAbilityByClass(UDashAbility::StaticClass());
}

void AAnan_ProgrammingTestCharacter::Molotov()
{
	AbilitySystemComponent->TryActivateAbilityByClass(MolotovAbility.Get());
}

void AAnan_ProgrammingTestCharacter::SmokeGrenade()
{
	AbilitySystemComponent->TryActivateAbilityByClass(SmokeGrenadeAbility.Get());
}

void AAnan_ProgrammingTestCharacter::Melee()
{
	AbilitySystemComponent->CancelAbilityHandle(AbilitySystemComponent->FindAbilitySpecFromClass(MolotovAbility)->Handle);
	AbilitySystemComponent->CancelAbilityHandle(AbilitySystemComponent->FindAbilitySpecFromClass(SmokeGrenadeAbility)->Handle);
}
