// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelPlayerPawn.h"
#include "Engine/CollisionProfile.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AVoxelPlayerPawn::AVoxelPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	capsuleComponent->InitCapsuleSize(50.0f, 100.0f);
	capsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	capsuleComponent->CanCharacterStepUpOn = ECB_No;
	capsuleComponent->SetShouldUpdatePhysicsVolume(true);
	capsuleComponent->SetCanEverAffectNavigation(false);
	capsuleComponent->bDynamicObstacle = true;

	RootComponent = capsuleComponent;

	arrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	arrowComponent->SetupAttachment(capsuleComponent);
	// Create a dummy root component we can attach things to.
	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	// firstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// visibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	// visibleComponent->SetSimulatePhysics(true);
	// visibleComponent->SetEnableGravity(true);
	// capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOUNDING BOX"));
	// capsuleComponent->InitCapsuleSize(50, 100);

	// Attach camera and visible object to our root component
	// visibleComponent->SetupAttachment(RootComponent);
	// firstPersonCameraComponent->SetupAttachment(RootComponent);
	// capsuleComponent->SetupAttachment(RootComponent);
	//firstPersonCameraComponent->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	//firstPersonCameraComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

}

// Called when the game starts or when spawned
void AVoxelPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoxelPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVoxelPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

