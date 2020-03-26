// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTVOXEL_API VoxelData
{
public:
	/*
	static const FVector VOXEL_VERTICES[8] =
	{
		FVector(0.0f, 0.0f, 0.0f),
		FVector(0.0f, 100.0f, 0.0f),
		FVector(0.0f, 100.0f, 100.0f),
		FVector(0.0f, 0.0f, 100.0f),
		FVector(100.0f, 100.0f, 0.0f),
		FVector(100.0f, 0.0f, 0.0f),
		FVector(100.0f, 0.0f, 100.0f),
		FVector(100.0f, 100.0f, 100.0f)
	};

	int32 VOXEL_TRIANGLES[6][4] =
	{
		{0, 1, 2, 3}, // Front Face
		{4, 5, 6, 7}, // Back Face
		{3, 2, 7, 6}, // Top Face
		{5, 4, 1, 0}, // Bottom Face
		{5, 0, 3, 6}, // Left Face
		{1, 4, 7, 2}  // Right Face
	};

	FVector2D VOXEL_UVS[4] =
	{
		FVector2D(0.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(1.0f, 0.0f),
		FVector2D(0.0f, 0.0f)
	};

	FVector VOXEL_NORMALS[6] =
	{
		FVector(-1,  0,  0),
		FVector(1,  0,  0),
		FVector(0,  0,  1),
		FVector(0,  0, -1),
		FVector(0, -1,  0),
		FVector(0,  1,  0)
	};

	FVector VOXEL_FACE_CHECK[6] =
	{
		FVector(-100, 0, 0),
		FVector(100, 0, 0),
		FVector(0, 0, 100),
		FVector(0, 0, -100),
		FVector(0, -100, 0),
		FVector(0, 100, 0)
	};
	*/
public:
	VoxelData();
	~VoxelData();
};
