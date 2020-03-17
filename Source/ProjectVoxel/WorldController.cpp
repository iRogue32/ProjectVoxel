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
	UChunkCoord* playerChunkCoord = AChunk::GetChunkCoordFromWorldCoord(playerLocation);

	const int32 AlwaysAddString = -1;
	static const FString scrollingMessage(TEXT("Chunk coord: "));

	GEngine->AddOnScreenDebugMessage(AlwaysAddString, 0.5f, FColor::Yellow, scrollingMessage + FString::FromInt(playerChunkCoord->x) + FString(TEXT(", ") + FString::FromInt(playerChunkCoord->y)));

	// Unload chunks farther than loadedChunkRadius from player
	for (auto& chunk : loadedChunkMap)
	{
		if (WithinLoadedRadius(chunk.Value, playerChunkCoord))
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
	for (int x = (playerChunkCoord->x - loadedChunkRadius); x <= playerChunkCoord->x + loadedChunkRadius; x++)
	{
		for (int y = playerChunkCoord->y - loadedChunkRadius; y <= playerChunkCoord->y + loadedChunkRadius; y++)
		{
			UChunkCoord* chunkCoord = NewObject<UChunkCoord>();
			chunkCoord->Init(x, y);
			// Check if chunk is already loaded
			if (loadedChunkMap.Contains(chunkCoord->AsLong()))
			{
				// If chunk is loaded, continue to next chunk
				continue;
			}
			// If chunk is not loaded, then generate it
			CreateNewChunk(x, y);
		}
	}

}

AChunk* AWorldController::GetChunk(UChunkCoord* coord)
{
	int x = coord->x;
	int y = coord->y;
	return nullptr;
}

void AWorldController::CreateNewChunk(int x, int y)
{
	AChunk* chunk = GetWorld()->SpawnActor<AChunk>();
	UChunkCoord* coord = NewObject<UChunkCoord>();
	coord->Init(x, y);
	chunk->Init(coord, chunkMaterial);
	loadedChunkMap.Add(coord->AsLong(), chunk);
}

void AWorldController::AddChunk(AChunk* chunk)
{
	UChunkCoord* coord = chunk->GetChunkCoord();
	int x = coord->x;
	int y = coord->y;
	
}

// returns true if chunk with UChunkCoord coord is currently loaded
bool AWorldController::ChunkIsLoaded(UChunkCoord* coord)
{
	return loadedChunkMap.Contains(coord->AsLong());
}

bool AWorldController::WithinLoadedRadius(AChunk* chunk, UChunkCoord* playerChunkCoord)
{
	UChunkCoord* coord = chunk->coord;
	if ((coord->x > playerChunkCoord->x + loadedChunkRadius) || (coord->x < playerChunkCoord->x - loadedChunkRadius) || (coord->y > playerChunkCoord->y + loadedChunkRadius) || (coord->y < playerChunkCoord->y - loadedChunkRadius))
		return false;

	return true;
}