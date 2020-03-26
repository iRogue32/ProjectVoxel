// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkPos.h"

ChunkPos::ChunkPos()
{
	x = 0;
	y = 0;
}

ChunkPos::ChunkPos(int32 _x, int32 _y)
{
	x = _x;
	y = _y;
}

ChunkPos::~ChunkPos()
{
}

int64 ChunkPos::AsLong()
{
	return (int64)x & 4294967295LL | ((int64)y & 4294967295LL) << 32;
}

int32 ChunkPos::GetX(int64 num)
{
	return (int)(num & 4294967295LL);
}

int32 ChunkPos::GetY(int64 num)
{
	return (int)((num >> 32) & 4294967295LL);
}


