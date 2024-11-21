// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/GravityGun.h"
#include "Components/SphereComponent.h"
#include "Anan_ProgrammingTest/Anan_ProgrammingTestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Component/InteractionComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AGravityGun::AGravityGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates skeletal mesh component and making it as a root
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	SetRootComponent(SkeletalMeshComponent);

	// Create Sphere collision component for the gun
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Gun Collision"));
	SphereComponent->SetupAttachment(RootComponent);

	// Creates Physics Handle component
	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handle"));


}

// Called when the game starts or when spawned
void AGravityGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGravityGun::LookAt_Implementation(bool& CanInteract, FText& WidgetMessage)
{
	CanInteract = true;
	WidgetMessage = FText::FromString("Press E To Grab the Gravity Gun");
}


void AGravityGun::Interact_Implementation()
{	

	AAnan_ProgrammingTestCharacter* PlayerCharacter = Cast<AAnan_ProgrammingTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Attach to the Player Character Mesh
	SkeletalMeshComponent->AttachToComponent(PlayerCharacter->GetMesh1P(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName(TEXT("GripPoint")));

	// Setting this value, which can be used by the animation blueprint
	PlayerCharacter->HasRifle = true;

	//Adding this actor to ignore when we do Look At Line Trace by the player
	PlayerCharacter->InteractionComponent->TraceCollisionParams.AddIgnoredActor(this);

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetLocalPlayer());
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->InputComponent);

	if (SubSystem)
	{
		SubSystem->AddMappingContext(WeaponMappingContext, 1);
	}
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(GrabInputAction, ETriggerEvent::Started, this, &AGravityGun::Grab);
		EnhancedInputComponent->BindAction(ShootInputAction, ETriggerEvent::Triggered, this, &AGravityGun::Throw);
		EnhancedInputComponent->BindAction(GrabInputAction, ETriggerEvent::Completed, this, &AGravityGun::GrabRelease);
	}

	UUserWidget* TutorialWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GravityGunTutorialWidgetClass);
	TutorialWidget->AddToViewport(1);
}

// Called every frame
void AGravityGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGrabbing)
	{
		SetTargetLocationAndRotation();
	}

}

// Handles the gravity gun's Grab logic
void AGravityGun::Grab()
{

	// Initializing Values for Line Trace

	FHitResult OutHit;
	FVector StartLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	FVector EndLocation = StartLocation + (UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * PickUpDistance);
	FCollisionQueryParams CollisionQueryParams = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass<UInteractionComponent>()->TraceCollisionParams;

	// Line Trace

	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionQueryParams))
	{
		
		// If the hit component has the collision object type of Physics Body, then grab that component using Physics Handle and Set IsGrabbing to true
		if (OutHit.Component->GetCollisionObjectType() == ECC_PhysicsBody)
		{
			PhysicsHandleComponent->GrabComponentAtLocationWithRotation(OutHit.Component.Get(), NAME_None, OutHit.Component->GetComponentLocation(), OutHit.Component->GetComponentRotation());
			bIsGrabbing = true;
		}
	}
}

void AGravityGun::GrabRelease()
{
	// Store the grabbed component
	USceneComponent* GrabbedComponent = PhysicsHandleComponent->GetGrabbedComponent();

	// Release the physics handle
	PhysicsHandleComponent->ReleaseComponent();

	if (GrabbedComponent)
	{
		//Set Exisiting Velocity to zero
		Cast<UPrimitiveComponent>(GrabbedComponent)->SetPhysicsLinearVelocity(FVector(0, 0, 0));
		Cast<UPrimitiveComponent>(GrabbedComponent)->SetPhysicsAngularVelocityInDegrees(FVector(0, 0, 0));
	}

}

// Handles the gravity gun's Throw logic
void AGravityGun::Throw()
{
	// Store the grabbed component
	USceneComponent* GrabbedComponent = PhysicsHandleComponent->GetGrabbedComponent();

	if (GrabbedComponent)
	{
		// Release the physics handle
		PhysicsHandleComponent->ReleaseComponent();

		//Set Exisiting Velocity to zero
		Cast<UPrimitiveComponent>(GrabbedComponent)->SetPhysicsLinearVelocity(FVector(0, 0, 0));
		Cast<UPrimitiveComponent>(GrabbedComponent)->SetPhysicsAngularVelocityInDegrees(FVector(0, 0, 0));

		// Add impulse in the forward vector of the camera
		Cast<UPrimitiveComponent>(GrabbedComponent)->AddImpulseAtLocation((UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * ThrowForce),
			GrabbedComponent->GetComponentLocation());
	}	
	else
	{
		Shoot();
	}

	// Plays Fire Animation Montage for the Player Mesh
	if (FireMontage)
	{
		Cast<AAnan_ProgrammingTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetMesh1P()->GetAnimInstance()->Montage_Play(FireMontage);
	}

}


// Handles the gravity gun's Shoot logic
void AGravityGun::Shoot()
{
	//Find what are the Object around the Player which are in the Object Type
	FVector StartLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.AddUnique(ObjectType);
	TArray<FHitResult> HitResults;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), StartLocation, StartLocation, PickUpDistance,
		ObjectTypes, false, TArray<AActor*>(), EDrawDebugTrace::None, HitResults, false))
	{
		// Find what are the objects are infront of the player using dot product
		for (int i = 0; i < HitResults.Num(); i++)
		{
			FVector DirectionVector = HitResults[i].Component->GetComponentLocation() - UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
			DirectionVector.Normalize();
			FVector ForwardVector = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector();
			ForwardVector.Normalize();

			float DotProduct = FVector::DotProduct(ForwardVector, DirectionVector);

			//Add Impulse to all the objects
			if (DotProduct > 0.75f)
			{

				Cast<UPrimitiveComponent>(HitResults[i].Component)->AddImpulseAtLocation((DirectionVector * ShootForce),
					HitResults[i].Component->GetComponentLocation());
			}
		}

	}
}

// Set the Physics Handle Target Location and Rotation
void AGravityGun::SetTargetLocationAndRotation()
{
	FVector TargetLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation() + (UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector() * HoldOffset);
	PhysicsHandleComponent->SetTargetLocationAndRotation(TargetLocation, UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation());
}

