// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTVOXEL_API BlockPos
{
public:
	int x;
	int y;
	int z;

public:
	BlockPos();
	BlockPos(int32 x, int32 y, int32 z);
	BlockPos(float x, float y, float z);
};
