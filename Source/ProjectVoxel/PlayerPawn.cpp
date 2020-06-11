// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	class UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	visibleComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VisibleComponent"));

	// Attach camera and visible object to our root component. Offset and rotate the camera.

	camera->SetupAttachment(RootComponent);
	//camera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	//camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float currentScale = visibleComponent->GetComponentScale().X;
	if (bGrowing)
		currentScale += DeltaTime;
	else
		currentScale -= (DeltaTime * 0.5f);

	currentScale = FMath::Clamp(currentScale, 1.0f, 2.0f);

	visibleComponent->SetWorldScale3D(FVector(currentScale));

	if (!CurrentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(newLocation);
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Grow" key is pressed or released
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &APlayerPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &APlayerPawn::StopGrowing);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY"
	PlayerInputComponent->BindAxis("MoveX", this, &APlayerPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerPawn::Move_YAxis);
}

void APlayerPawn::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void APlayerPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void APlayerPawn::StartGrowing()
{
	bGrowing = true;
}

void APlayerPawn::StopGrowing()
{
	bGrowing = false;
}