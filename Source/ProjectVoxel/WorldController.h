// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	static const int worldRadiusInChunks = 10;

	UPROPERTY(VisibleAnywhere, Category = LoadedChunks)
		TMap<int64, AChunk*> chunkMap;

	UPROPERTY(EditAnywhere, Category = Material)
		UMaterial* chunkMaterial;

private:
	AChunk* chunkMapPosPos[worldRadiusInChunks][worldRadiusInChunks];
	AChunk* chunkMapPosNeg[worldRadiusInChunks][worldRadiusInChunks];
	AChunk* chunkMapNegPos[worldRadiusInChunks][worldRadiusInChunks];
	AChunk* chunkMapNegNeg[worldRadiusInChunks][worldRadiusInChunks];

public:	
	// Sets default values for this actor's properties
	AWorldController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void GenerateWorld();
	void AddChunk(AChunk* chunk);
	AChunk* GetChunk(UChunkCoord* coord);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

UCLASS()
class UBlockTypes : public UObject
{
	GENERATED_BODY()

public:
	std::string name;
	bool isSolid;
};
