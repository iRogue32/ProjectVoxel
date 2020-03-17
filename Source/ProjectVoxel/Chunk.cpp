// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	mesh->bUseAsyncCooking = true;

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

void AChunk::Init(UChunkCoord* _coord, UMaterial* _material)
{
	coord = _coord;
	material = _material;
	PopulateVoxelMap();

	r = FMath::RandRange(0.0f, 1.0f);
	g = FMath::RandRange(0.0f, 1.0f);
	b = FMath::RandRange(0.0f, 1.0f);

	for (int z = 0; z < chunkHeight; z++)
	{
		for (int y = 0; y < chunkLength; y++)
		{
			for (int x = 0; x < chunkLength; x++)
			{
				AddVoxelDataToChunk(FVector(x * 100, y * 100, z * 100));
			}
		}
	}

	CreateMesh();
	SetActorLocation(FVector(coord->x * 100 * chunkLength, coord->y * 100 * chunkLength, 0));
	FString label = "Chunk ";
	label.AppendInt(coord->x);
	label += ", ";
	label.AppendInt(coord->y);
	SetActorLabel(label);
}

void AChunk::PostActorCreated()
{
	Super::PostActorCreated();
}

void AChunk::PostLoad()
{
	Super::PostLoad();
}

UChunkCoord* AChunk::GetChunkCoord()
{
	return coord;
}

UChunkCoord* AChunk::GetChunkCoordFromWorldCoord(FVector pos)
{
	int x, y;
	if (pos.X >= 0.0f)
		x = pos.X / (chunkLength * 100);
	else
		x = (pos.X / (chunkLength * 100)) - 1;
	if (pos.Y >= 0.0f)
		y = pos.Y / (chunkLength * 100);
	else
		y = (pos.Y / (chunkLength * 100)) - 1;

	UChunkCoord* chunkCoord = NewObject<UChunkCoord>();
	chunkCoord->Init(x, y);

	return chunkCoord;
}

void AChunk::PopulateVoxelMap()
{
	for (int z = 0; z < chunkHeight; z++)
	{
		for (int y = 0; y < chunkLength; y++)
		{
			for (int x = 0; x < chunkLength; x++)
			{
				voxelMap[x][y][z] = true;
			}
		}
	}
}

void AChunk::AddVoxelDataToChunk(FVector pos)
{
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
	return false;
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

}

// ChunkCoord

UChunkCoord::UChunkCoord()
{
	x = 0;
	y = 0;
}

void UChunkCoord::Init(int _x, int _y)
{
	x = _x;
	y = _y;
}

int64 UChunkCoord::AsLong()
{
	return (int64)x & 4294967295LL | ((int64)y & 4294967295LL) << 32;
}

int UChunkCoord::GetX(int64 num)
{
	return (int)(num & 4294967295LL);
}

int UChunkCoord::GetY(int64 num)
{
	return (int)((num >> 32) & 4294967295LL);
}

