// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldController.h"

// Sets default values
AWorldController::AWorldController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldController::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateWorld();
}

void AWorldController::GenerateWorld()
{
	for (int x = -worldRadiusInChunks; x <= worldRadiusInChunks; x++)
	{
		for (int y = -worldRadiusInChunks; y <= worldRadiusInChunks; y++)
		{
			AChunk* chunk = GetWorld()->SpawnActor<AChunk>();
			UChunkCoord* coord = NewObject<UChunkCoord>();
			coord->Init(x, y);
			chunk->Init(coord, chunkMaterial);
			int xbefore = coord->x;
			int ybefore = coord->y;
			UE_LOG(LogTemp, Warning, TEXT("X: %d"), xbefore);
			UE_LOG(LogTemp, Warning, TEXT("Y: %d"), ybefore);
			int64 num = coord->AsLong();
			UE_LOG(LogTemp, Warning, TEXT("Long64: Ox%llX"), num);
			int xafter = UChunkCoord::GetX(num);
			int yafter = UChunkCoord::GetY(num);
			UE_LOG(LogTemp, Warning, TEXT("X (after): %d"), xafter);
			UE_LOG(LogTemp, Warning, TEXT("Y (after): %d"), yafter);
			chunkMap.Add(num, chunk);
			//AddChunk(chunk);
		}
	}
}

void AWorldController::AddChunk(AChunk* chunk)
{
	UChunkCoord* coord = chunk->GetChunkCoord();
	int x = coord->x;
	int y = coord->y;
	if (x >= 0)
	{
		if (y >= 0)
		{
			chunkMapPosPos[x][y] = chunk;
		}
		else
		{
			y *= -1;
			chunkMapPosNeg[x][y] = chunk;
		}
	}
	else
	{
		if (y >= 0)
		{
			x *= -1;
			chunkMapNegPos[x][y] = chunk;
		}
		else
		{
			x *= -1;
			y *= -1;
			chunkMapNegNeg[x][y] = chunk;
		}
	}
}

AChunk* AWorldController::GetChunk(UChunkCoord* coord)
{
	int x = coord->x;
	int y = coord->y;
	if (x >= 0)
	{
		if (y >= 0)
		{
			return chunkMapPosPos[x][y];
		}
		else
		{
			y *= -1;
			return chunkMapPosNeg[x][y];
		}
	}
	else
	{
		if (y >= 0)
		{
			x *= -1;
			return chunkMapNegPos[x][y];
		}
		else
		{
			x *= -1;
			y *= -1;
			return chunkMapNegNeg[x][y];
		}
	}
}

// Called every frame
void AWorldController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

