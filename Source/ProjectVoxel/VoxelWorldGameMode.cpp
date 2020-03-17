// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelWorldGameMode.h"
#include "ProjectVoxelHUD.h"
#include "ProjectVoxelCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVoxelWorldGameMode::AVoxelWorldGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectVoxelHUD::StaticClass();
}

