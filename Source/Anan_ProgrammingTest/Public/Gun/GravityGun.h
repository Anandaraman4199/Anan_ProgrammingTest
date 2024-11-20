// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "GravityGun.generated.h"

UCLASS()
class ANAN_PROGRAMMINGTEST_API AGravityGun : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravityGun();

	/** Gun Skeletal Mesh*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	USkeletalMeshComponent* SkeletalMeshComponent;

	/** Sphere Collision for the gun*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	class USphereComponent* SphereComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Interaction Interface Function
		Look At function will decide what to do when we look at Interactable Actors
		It will return a bool, whether we can interact with it or not */
	void LookAt_Implementation(bool& CanInteract, FText& WidgetMessage);

	/** Interaction Interface Function 
		Use this function to interact with the Interactable Actors.
		Make sure that this object is interactable using LookAt function */
	void Interact_Implementation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
