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

	/** Max Distance that we can grab the objects from using this Gun*/
	UPROPERTY(EditAnywhere, Category = "Initialize Variable", meta = (AllowPrivateAccess = "true"))
	float GrabDistance = 1000;

	/** Offset to hold the physics object infront*/
	UPROPERTY(EditAnywhere, Category = "Initialize Variable", meta = (AllowPrivateAccess = "true"))
	float GrabOffsetDistance = 300;

	/** ThrowForce when grabbing an object*/
	UPROPERTY(EditAnywhere, Category = "Initialize Variable", meta = (AllowPrivateAccess = "true"))
	float ThrowForce = 500000.0;

	/** ShootForce when not grabbing an object*/
	UPROPERTY(EditAnywhere, Category = "Initialize Variable", meta = (AllowPrivateAccess = "true"))
	float ShootForce = 250000.0;

	/** Object Types to impact when shooting*/
	UPROPERTY(EditAnywhere, Category = "Initialize Variable", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EObjectTypeQuery> ObjectType;

	/** Weapon Input Mapping Context*/
	UPROPERTY(EditAnywhere, Category = "Initialize Variable|Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* WeaponMappingContext;

	/** Grab Input Action*/
	UPROPERTY(EditAnywhere, Category = "Initialize Variable|Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* GrabInputAction;

	/** Shoot Input Action*/
	UPROPERTY(EditAnywhere, Category = "Initialize Variable|Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootInputAction;


public:	
	// Sets default values for this actor's properties
	AGravityGun();

	/** Gun Skeletal Mesh*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	USkeletalMeshComponent* SkeletalMeshComponent;

	/** Sphere Collision for the gun*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	class USphereComponent* SphereComponent;

	/** Physics Handle will take care of holding a physics actor in front of the player*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	class UPhysicsHandleComponent* PhysicsHandleComponent;

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

private:

	// Handles the gravity gun's Grab logic
	void Grab();

	// Handles the gravity gun's Grab Release logic
	void GrabRelease();

	// Handles the gravity gun's Throw logic
	void Throw();

	// Handles the gravity gun's Shoot logic
	void Shoot();

	// Set the Physics Handle Target Location and Rotation
	void SetTargetLocationAndRotation();

	bool bIsGrabbing = false;

};
