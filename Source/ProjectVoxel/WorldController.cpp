// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldController.h"

// Sets default values
AWorldController::AWorldController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AWorldController::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(FVector(0.0f, 0.0f, 0.0f));

	player = GetWorld()->GetFirstPlayerController()->GetPawn();

	GenerateWorld();
	//AProjectVoxelCharacter* player = GetWorld()->SpawnActor<AProjectVoxelCharacter>(GetTransform().GetLocation(), GetTransform().GetRotation().Rotator());
}

void AWorldController::GenerateWorld()
{
	for (int x = -loadedChunkRadius; x <= loadedChunkRadius; x++)
	{
		for (int y = -loadedChunkRadius; y <= loadedChunkRadius; y++)
		{
			CreateNewChunk(x, y);
		}
	}
}

// Called every frame
void AWorldController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector playerLocation = player->GetActorLocation();
	ChunkPos playerChunkPos = AChunk::GetChunkPositionFromWorldCoord(playerLocation);

	const int32 AlwaysAddString = -1;
	static const FString scrollingMessage(TEXT("Chunk coord: "));

	GEngine->AddOnScreenDebugMessage(AlwaysAddString, 0.5f, FColor::Yellow, scrollingMessage + FString::FromInt(playerChunkPos.x) + FString(TEXT(", ") + FString::FromInt(playerChunkPos.y)));

	// Unload chunks farther than loadedChunkRadius from player
	for (auto& chunk : loadedChunkMap)
	{
		if (WithinLoadedRadius(chunk.Value, playerChunkPos))
		{
			// If chunk is within loadedChunkRadius
			continue;
		}
		AChunk* toDestroy = *loadedChunkMap.Find(chunk.Key);
		if (toDestroy)
		{
			toDestroy->Destroy();
		}
		loadedChunkMap.Remove(chunk.Key);
	}

	// Load chunks around player within loadedChunkRadius
	for (int x = (playerChunkPos.x - loadedChunkRadius); x <= playerChunkPos.x + loadedChunkRadius; x++)
	{
		for (int y = playerChunkPos.y - loadedChunkRadius; y <= playerChunkPos.y + loadedChunkRadius; y++)
		{
			ChunkPos chunkPos(x, y);
			// Check if chunk is already loaded
			if (loadedChunkMap.Contains(chunkPos.AsLong()))
			{
				// If chunk is loaded, continue to next chunk
				continue;
			}
			// If chunk is not loaded, then generate it
			CreateNewChunk(x, y);
		}
	}

}

AChunk* AWorldController::GetChunk(ChunkPos chunkPos)
{
	int32 x = chunkPos.x;
	int32 y = chunkPos.y;
	return nullptr;
}

void AWorldController::CreateNewChunk(int x, int y)
{
	AChunk* chunk = GetWorld()->SpawnActor<AChunk>();
	ChunkPos chunkPos(x, y);
	chunk->Init(chunkPos, chunkMaterial);
	loadedChunkMap.Add(chunkPos.AsLong(), chunk);
}

void AWorldController::AddChunk(AChunk* chunk)
{
	ChunkPos chunkPos = chunk->GetChunkPosition();
	int x = chunkPos.x;
	int y = chunkPos.y;
	// TODO: implement
}

// returns true if chunk with ChunkPos chunkPos is currently loaded
bool AWorldController::ChunkIsLoaded(ChunkPos chunkPos)
{
	return loadedChunkMap.Contains(chunkPos.AsLong());
}

bool AWorldController::WithinLoadedRadius(AChunk* chunk, ChunkPos playerChunkPos)
{
	ChunkPos chunkPos = chunk->chunkPosition;
	if ((chunkPos.x > playerChunkPos.x + loadedChunkRadius) || (chunkPos.x < playerChunkPos.x - loadedChunkRadius) || (chunkPos.y > playerChunkPos.y + loadedChunkRadius) || (chunkPos.y < playerChunkPos.y - loadedChunkRadius))
		return false;

	return true;
}