// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VoxelPlayerPawn.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;
class UArrowComponent;

UCLASS()
class PROJECTVOXEL_API AVoxelPlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* visibleComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* firstPersonCameraComponent;

	// Capsule Component (bounding box)
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* capsuleComponent;

	UPROPERTY()
	UArrowComponent* arrowComponent;

	// Input Variables
	FVector CurrentVelocity;

protected:
	/** DefaultPawn movement component */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* movementComponent;

public:
	static FName characterMovementComponentName;

public:
	// Sets default values for this pawn's properties
	AVoxelPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Begin Pawn overrides
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);
};
