// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseCharacter.h"
#include "AbilitySystemComponent.h"

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create an Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Add a new base attribute set to the Ability System Component, if there isn't one
	if (AbilitySystemComponent)
	{
		BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();

		if (!BaseAttributeSet)
		{
			BaseAttributeSet = AbilitySystemComponent->AddSet<UBaseAttributeSet>();
		}

	}

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

