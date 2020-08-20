// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectVoxelGameMode.h"
#include "ProjectVoxelHUD.h"
#include "ProjectVoxelCharacter.h"
#include "TestCharacter.h"
#include "VoxelPlayerPawn.h"
#include "UObject/ConstructorHelpers.h"

AProjectVoxelGameMode::AProjectVoxelGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;
	DefaultPawnClass = ATestCharacter::StaticClass();
	//DefaultPawnClass = AVoxelPlayerPawn::StaticClass();
	//DefaultPawnClass = ACharacter::StaticClass();

	// use our custom HUD class
	HUDClass = AProjectVoxelHUD::StaticClass();
}
