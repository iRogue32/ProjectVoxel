// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include <string>
#include "Chunk.h"
#include "WorldController.generated.h"

UCLASS()
class PROJECTVOXEL_API AWorldController : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Blocks)
		UBlockTypes* blocks;

	UPROPERTY(VisibleAnywhere, Category = Players)
		APawn* player;

	static const int loadedChunkRadius = 12;

	UPROPERTY(VisibleAnywhere, Category = LoadedChunks)
		TMap<int64, AChunk*> loadedChunkMap;

	UPROPERTY(EditAnywhere, Category = Material)
		UMaterial* chunkMaterial;

private:
	FVector playerSpawnEdition;

public:	
	// Sets default values for this actor's properties
	AWorldController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& transform) override;
	virtual void EndPlay(const EEndPlayReason::Type reason) override;

public:	
	void GenerateWorld();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AChunk* GetChunk(ChunkPos chunkPos);

private:
	void CreateNewChunk(int x, int y);
	void AddChunk(AChunk* chunk);
	bool ChunkIsLoaded(ChunkPos chunkPos);
	bool WithinLoadedRadius(AChunk* chunk, ChunkPos playerChunk);

};

UCLASS()
class UBlockTypes : public UObject
{
	GENERATED_BODY()

public:
	std::string name;
	bool isSolid;
};
