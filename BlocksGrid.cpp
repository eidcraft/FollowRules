// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "BlocksGrid.h"

#include "Engine.h"

ABlocksGrid::ABlocksGrid()
{
  PrimaryActorTick.bCanEverTick = true;

  DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
  RootComponent = DummyRoot;

  BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent0"));
  BoxComponent->AttachTo(DummyRoot);
  BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
  BoxComponent->SetRelativeScale3D(FVector(40.f, 60.f, 1.f));

}

// Called when the game starts or when spawned
void ABlocksGrid::BeginPlay()
{
  Super::BeginPlay();

}

// Called every frame
void ABlocksGrid::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}



void ABlocksGrid::createGrid(TArray< TArray<int32> >& map, TArray<UMaterial*>& materials, float blocksSpacing)
{
  spawnBlocks(&map, blocksSpacing);

  initBlocks(&map, &materials);

  agregateBlocksOnClickEvents();
}



void ABlocksGrid::spawnBlocks(TArray<TArray<int32>>* map, float blocksSpacing)
{
  FVector gridLocation;
  FVector gridExtent;
  GetActorBounds(false, gridLocation, gridExtent);

  FVector blockSpawnPoint = gridLocation - gridExtent / 2;

  UWorld* world = GetWorld();
  TArray<ABlock*> blocksRow;

  for (int32 y = 0; y < map->Num(); y++)
  {
    for (int32 x = 0; x < (*map)[0].Num(); x++)
    {
      const float xOffset = x * blocksSpacing;
      const float yOffset = y * blocksSpacing;
      const FVector blockLocation = blockSpawnPoint + FVector(xOffset, yOffset, 0.f);

      ABlock* newBlock = world->SpawnActor<ABlock>(blockLocation, FRotator(0, 0, 0));

      this->Children.Add(newBlock);
      blocksRow.Add(newBlock);
    }
    blocks.Add(blocksRow);
    blocksRow.Empty();
  }
}



void ABlocksGrid::initBlocks(TArray< TArray<int32> >* map, TArray<UMaterial*>* materials)
{
  for (int32 y = 0; y < map->Num(); y++)
  {
    for (int32 x = 0; x < (*map)[0].Num(); x++)
    {
      blocks[y][x]->init((*map)[y][x], materials, x, y);
    }
  }
}




void ABlocksGrid::agregateBlocksOnClickEvents()
{
  for (int32 y = 0; y < blocks.Num(); y++)
  {
    for (int32 x = 0; x < blocks[0].Num(); x++)
    {
      blocks[y][x]->onClicked.AddDynamic(this, &ABlocksGrid::gridBlockWasClicked);
    }
 }   
}


void ABlocksGrid::gridBlockWasClicked(ABlock* clickedBlock)
{
  gridWasClicked.Broadcast(clickedBlock);
}


