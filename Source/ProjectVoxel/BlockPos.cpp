// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockPos.h"

BlockPos::BlockPos()
{
}

BlockPos::BlockPos(int32 x, int32 y, int32 z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

BlockPos::BlockPos(float x, float y, float z)
{
	this->x = floor(x);
	this->y = floor(y);
	this->z = floor(z);
}