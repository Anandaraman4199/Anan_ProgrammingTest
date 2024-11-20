// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun/GravityGun.h"
#include "Components/SphereComponent.h"
#include "Anan_ProgrammingTest/Anan_ProgrammingTestCharacter.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AGravityGun::AGravityGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates skeletal mesh component
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	SetRootComponent(SkeletalMeshComponent);

	// Create Sphere collision component for the gun and making it as a root
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Gun Collision"));
	SphereComponent->SetupAttachment(RootComponent);



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
}

// Called every frame
void AGravityGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

