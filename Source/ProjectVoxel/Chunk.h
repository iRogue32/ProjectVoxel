// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Chunk.generated.h"

UCLASS()
class PROJECTVOXEL_API AChunk : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = Attributes)
		UMaterial* material;

public:
	FVector VOXEL_VERTICES[8] =
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

	UPROPERTY(EditAnywhere, Category = vertices)
		TArray<FVector> vertices;
	UPROPERTY(EditAnywhere, Category = triangles)
		TArray<int32> triangles;
	TArray<FVector2D> uvs;
	TArray<FVector> normals;
	TArray<FLinearColor> vertexColors;
	TArray<FProcMeshTangent> tangents;

	UChunkCoord* coord;

	int32 chunkHeight = 4;
	int32 chunkLength = 16;

	int32 vertexIndex = 0;

	bool*** voxelMap;

	float r;
	float g;
	float b;

public:
	// Sets default values for this actor's properties
	AChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	void Init(UChunkCoord* _coord, UMaterial* _material);
	virtual void Tick(float DeltaTime) override;
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	UChunkCoord* GetChunkCoord();

private:
	void PopulateVoxelMap();
	void AddVoxelDataToChunk(FVector pos);
	void CreateMesh();
	bool CheckVoxel(FVector pos);
};

UCLASS()
class UChunkCoord : public UObject
{
	GENERATED_BODY()

public:
	int x;
	int y;

	UChunkCoord();
	void Init(int x, int y);
	int64 AsLong();
	static int GetX(int64 num);
	static int GetY(int64 num);
};
