// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTVOXEL_API ChunkPos
{
public:
	int32 x;
	int32 y;

public:
	ChunkPos();
	ChunkPos(int32 x, int32 y);
	~ChunkPos();

public:
	int64 AsLong();
	static int32 GetX(int64 num);
	static int32 GetY(int64 num);
};
