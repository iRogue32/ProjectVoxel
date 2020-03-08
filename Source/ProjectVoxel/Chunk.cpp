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
}

void AChunk::PostActorCreated()
{
	Super::PostActorCreated();
}

void AChunk::PostLoad()
{
	Super::PostLoad();
}

void AChunk::AddVoxelDataToChunk(FVector pos)
{
	for (int face = 0; face < 6; face++)
	{

		for (int i = 0; i < 6; i++)
		{
			int triangleIndex = VOXEL_TRIANGLES[face][i];
			vertices.Add(VOXEL_VERTICES[triangleIndex] + pos);
			triangles.Add(vertexIndex);
			uvs.Add(VOXEL_UVS[i]);
			normals.Add(VOXEL_NORMALS[face]);
			vertexIndex++;
		}
	}
}

void AChunk::CreateMesh()
{
	mesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, uvs, vertexColors, tangents, false);
	mesh->SetMaterial(0, material);
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();

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
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

