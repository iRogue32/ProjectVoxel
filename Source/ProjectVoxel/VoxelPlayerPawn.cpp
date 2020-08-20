// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelPlayerPawn.h"
#include "Engine/CollisionProfile.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Engine/Engine.h"

FName AVoxelPlayerPawn::characterMovementComponentName(TEXT("CharMoveComp"));

// Sets default values
AVoxelPlayerPawn::AVoxelPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	capsuleComponent->InitCapsuleSize(50.0f, 100.0f);
	capsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	capsuleComponent->CanCharacterStepUpOn = ECB_No;
	capsuleComponent->SetShouldUpdatePhysicsVolume(true);
	capsuleComponent->SetSimulatePhysics(true);
	capsuleComponent->SetCanEverAffectNavigation(false);
	capsuleComponent->bDynamicObstacle = true;

	RootComponent = capsuleComponent;

	arrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	arrowComponent->SetupAttachment(capsuleComponent);
	if (arrowComponent)
	{
		arrowComponent->ArrowColor = FColor(150, 200, 255);
		arrowComponent->bTreatAsASprite = true;
		//arrowComponent->SpriteInfo.Category = ConstructorStatics.ID_Characters;
		//arrowComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_Characters;
		arrowComponent->SetupAttachment(capsuleComponent);
		arrowComponent->bIsScreenSizeScaled = true;
	}

	firstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->SetupAttachment(RootComponent);
	firstPersonCameraComponent->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	firstPersonCameraComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// Movement Component
	movementComponent = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("MovementComponent"));
	// movementComponent->SetUpdatedComponent(capsuleComponent);

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
	PlayerInputComponent->BindAxis("MoveX", this, &AVoxelPlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveY", this, &AVoxelPlayerPawn::MoveRight);
	//PlayerInputComponent->BindAxis("Turn", this, &ATestCharacter::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &ATestCharacter::AddControllerPitchInput);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATestCharacter::StartJump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATestCharacter::StopJump);
}

UPawnMovementComponent* AVoxelPlayerPawn::GetMovementComponent() const
{
	return movementComponent;
}

void AVoxelPlayerPawn::MoveForward(float value)
{
	FString debugMsg = FString::Printf(TEXT("Move Forward value: %s"), *FString::SanitizeFloat(value));
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, debugMsg);

	//FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	//AddMovementInput(GetActorForwardVector(), value * 100.f);
	CurrentVelocity.X = FMath::Clamp(value, -1.0f, 1.0f) * 100.0f;
}

void AVoxelPlayerPawn::MoveRight(float value)
{
	FString debugMsg = FString::Printf(TEXT("Move Forward value: %s"), *FString::SanitizeFloat(value));
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(2, 0.0f, FColor::Blue, debugMsg);

	//FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//AddMovementInput(GetActorRightVector(), value);
	CurrentVelocity.Y = FMath::Clamp(value, -1.0f, 1.0f) * 100.0f;
}

