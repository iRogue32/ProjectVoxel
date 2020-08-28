// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"
#include "WorldController.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	mesh->bUseAsyncCooking = true;

	isDirty = false;
	voxelMap = new bool** [chunkLength];
	for (int i = 0; i < chunkLength; i++)
	{
		voxelMap[i] = new bool* [chunkLength];
		for (int j = 0; j < chunkLength; j++)
		{
			voxelMap[i][j] = new bool[chunkHeight] { false };
		}
	}
}

void AChunk::Init(ChunkPos pos, UMaterial* _material)
{
	chunkPosition = pos;
	material = _material;
	CreateHeightMap();
	PopulateVoxelMap();
	// CreateMesh();
	SetActorLocation(FVector(chunkPosition.x * 100 * chunkLength, chunkPosition.y * 100 * chunkLength, 0));
	FString label = "Chunk ";
	label.AppendInt(chunkPosition.x);
	label += ", ";
	label.AppendInt(chunkPosition.y);
	//SetActorLabel(label);
}

void AChunk::GenerateMeshData()
{
	r = FMath::RandRange(0.0f, 1.0f);
	g = FMath::RandRange(0.0f, 1.0f);
	b = FMath::RandRange(0.0f, 1.0f);

	for (int z = 0; z < chunkHeight; z++)
	{
		for (int y = 0; y < chunkLength; y++)
		{
			for (int x = 0; x < chunkLength; x++)
			{
				if (voxelMap[x][y][z])
					AddVoxelRenderDataToChunk(FVector(x * 100, y * 100, z * 100));
			}
		}
	}
}

void AChunk::PostActorCreated()
{
	Super::PostActorCreated();
}

void AChunk::PostLoad()
{
	Super::PostLoad();
}

ChunkPos AChunk::GetChunkPosition()
{
	return chunkPosition;
}

ChunkPos AChunk::GetChunkPositionFromWorldCoord(FVector pos)
{
	int32 x, y;
	if (pos.X >= 0.0f)
		x = pos.X / (chunkLength * 100);
	else
		x = (pos.X / (chunkLength * 100)) - 1;
	if (pos.Y >= 0.0f)
		y = pos.Y / (chunkLength * 100);
	else
		y = (pos.Y / (chunkLength * 100)) - 1;

	ChunkPos chunkPos(x, y);
	return chunkPos;
}

void AChunk::CreateHeightMap()
{
	// sets blocks to fill chunk up to half of chunk height
	for (int x = 0; x < chunkLength; x++)
	{
		for (int y = 0; y < chunkLength; y++)
		{
			heightMap[x][y] = 0.5f * chunkHeight;
		}
	}

	/*
	FastNoise noise;
	noise.SetNoiseType(FastNoise::Perlin);

	for (int x = 0; x < chunkLength; x++)
	{
		for (int y = 0; y < chunkLength; y++)
		{
			heightMap[x][y] = noise.GetNoise((x + (chunkPosition.x * chunkLength)), (y + (chunkPosition.y * chunkLength))) * chunkHeight;
		}
	}
	*/
}

void AChunk::PopulateVoxelMap()
{
	for (int z = 0; z < chunkHeight; z++)
	{
		for (int y = 0; y < chunkLength; y++)
		{
			for (int x = 0; x < chunkLength; x++)
			{
					voxelMap[x][y][z] = GenerateVoxel(x , y, z);
			}
		}
	}
	isDirty = true;
}

void AChunk::AddVoxelRenderDataToChunk(FVector pos)
{
	//vertices.Empty();
	//triangles.Empty();
	//normals.Empty();
	//uvs.Empty();
	//vertexColors.Empty();
	for (int face = 0; face < 6; face++)
	{
		if (!CheckVoxel(pos + VOXEL_NORMALS[face] * 100))
		{
			vertices.Add(pos + VOXEL_VERTICES[VOXEL_TRIANGLES[face][0]]);
			vertices.Add(pos + VOXEL_VERTICES[VOXEL_TRIANGLES[face][1]]);
			vertices.Add(pos + VOXEL_VERTICES[VOXEL_TRIANGLES[face][2]]);
			vertices.Add(pos + VOXEL_VERTICES[VOXEL_TRIANGLES[face][3]]);

			normals.Add(VOXEL_NORMALS[face]);
			normals.Add(VOXEL_NORMALS[face]);
			normals.Add(VOXEL_NORMALS[face]);
			normals.Add(VOXEL_NORMALS[face]);

			uvs.Add(VOXEL_UVS[0]);
			uvs.Add(VOXEL_UVS[1]);
			uvs.Add(VOXEL_UVS[2]);
			uvs.Add(VOXEL_UVS[3]);

			vertexColors.Add(FLinearColor(r, g, b, 1.0f));
			vertexColors.Add(FLinearColor(r, g, b, 1.0f));
			vertexColors.Add(FLinearColor(r, g, b, 1.0f));
			vertexColors.Add(FLinearColor(r, g, b, 1.0f));

			triangles.Add(vertexIndex);
			triangles.Add(vertexIndex + 1);
			triangles.Add(vertexIndex + 2);
			triangles.Add(vertexIndex + 0);
			triangles.Add(vertexIndex + 2);
			triangles.Add(vertexIndex + 3);

			vertexIndex += 4;
		}
	}
}

void AChunk::CreateMesh()
{
	mesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, uvs, vertexColors, tangents, true);
	mesh->SetMaterial(0, material);
}

// Generates voxel at position x,y,z
bool AChunk::GenerateVoxel(int x, int y, int z)
{
	if (heightMap[x][y] <= 0)
		heightMap[x][y] = 0;
	if (z <= heightMap[x][y])
		return true;
	
	return false;
}

// returns true if voxel at relative pos (x, y, z) is within the current chunk
bool AChunk::VoxelIsInChunk(int x, int y, int z)
{
	if (x < 0 || x >= chunkLength || y < 0 || y >= chunkLength || z < 0 || z >= chunkHeight)
	{
		return false;
	}
	return true;
}

bool AChunk::CheckVoxel(FVector pos)
{
	int x = pos.X / 100;
	int y = pos.Y / 100;
	int z = pos.Z / 100;

	if (VoxelIsInChunk(x, y, z))
	{
		return voxelMap[x][y][z];
	}
	return true;
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDirty)
	{
		GenerateMeshData();
		CreateMesh();
		isDirty = false;
	}
}