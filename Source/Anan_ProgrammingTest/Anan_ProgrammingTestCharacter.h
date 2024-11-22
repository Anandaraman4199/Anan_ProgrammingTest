// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Actor/BaseCharacter.h"
#include "Anan_ProgrammingTestCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AAnan_ProgrammingTestCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditDefaultsOnly, Category= "Input|Default", meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, Category= "Input|Default", meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Dash Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	/** Molotov ability*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwables|Molotov", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UThrowGameplayAbility> MolotovAbility;

	/** Molotov Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwables|Molotov", meta = (AllowPrivateAccess = "true"))
	UInputAction* MolotovInputAction;

	/** Smoke Grenade ability*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwables|SmokeGrenade", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UThrowGameplayAbility> SmokeGrenadeAbility;

	/** Smoke Grenade Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwables|SmokeGrenade", meta = (AllowPrivateAccess = "true"))
	UInputAction* SmokeGrenadeInputAction;

	/** Melee or Gun Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Default", meta = (AllowPrivateAccess = "true"))
	UInputAction* MeleeInputAction;

	/** Player HUD Widget*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlayerHUDWidget;

	/** Provide all the Default Gameplay Abilities in this array*/
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystemComponent|GameplayAbilities", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayAbility>> StartingGameplayAbilities;


public:
	AAnan_ProgrammingTestCharacter();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Dash input */
	void Dash();

	/** Called when switching to Molotov input */
	void Molotov();

	/** Called when switching to SmokeGrenade input */
	void SmokeGrenade();


	void BeginPlay() override;

protected:
	
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


public:

	class AGravityGun* CurrentGun;

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** This will be used for Animation Blueprint*/
	UPROPERTY(BlueprintReadOnly, Category = "Animation Values")
	bool HasRifle = false;

	/** Interaction Component which takes care of Look At and Interact Functions*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AdditionalComponents)
	class UInteractionComponent* InteractionComponent;

	/** Store Player Move Input Values*/
	UPROPERTY(BlueprintReadOnly, Category = "InputValues")
	FVector2D PlayerMoveInputValues;

	/** Dash Speed*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashSpeed = 10000;

	/** Cooldown between dashes in seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	TSubclassOf<class UGameplayEffect> DashCooldownClass;

	/** ThrowableMappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Throwable")
	UInputMappingContext* ThrowableMappingContext;

	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Throwable")
	UInputAction* AimAction;

	/** Throw Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Throwable")
	UInputAction* ThrowAction;

	/** Throwables items Throw Start Offset*/
	UPROPERTY(EditDefaultsOnly, Category = "Throwables")
	FVector ThrowStartOffset;

	/** Holds reference to current Player HUD Widget*/
	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	class UPlayerHUDWidget* PlayerHUD;

	/** Called when switching to Melee input */
	void Melee();

};

