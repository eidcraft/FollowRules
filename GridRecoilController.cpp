// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "PlayerPawn.h"
#include "Engine.h"
#include "GridRecoilController.h"


// Sets default values
AGridRecoilController::AGridRecoilController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
  SetActorTickEnabled(false);

}

// Called when the game starts or when spawned
void AGridRecoilController::BeginPlay()
{
	Super::BeginPlay();
	
  makeSnapshot();
}

// Called every frame
void AGridRecoilController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AGridRecoilController::init(TArray< TArray<ABlock*> >& blocks, APlayerPawn* playerPawn)
{
  this->blocks = &blocks;
  this->playerPawn = playerPawn;

  playerPawn->onMovingBegin.AddDynamic(this, &AGridRecoilController::makeSnapshot);
}


void AGridRecoilController::makeSnapshot()
{
  BlockSnapshot* blockSnapshot;
  ABlock* tmp;

  TArray<BlockSnapshot*>* blockSnapshotsRow;
  TArray<TArray<BlockSnapshot*>*>* blockSnapshotsGrid = 
    new TArray<TArray<BlockSnapshot*>*>();

  for (int32 y = 0; y < blocks->Num(); y++)
  {
    blockSnapshotsRow = new TArray<BlockSnapshot*>();
    for (int32 x = 0; x < (*blocks)[0].Num(); x++)
    {
      tmp = (*blocks)[y][x];

      blockSnapshot = getBlockSnapshot((*blocks)[y][x]);
      blockSnapshotsRow->Add(blockSnapshot);
    }
    blockSnapshotsGrid->Add(blockSnapshotsRow);
  }

  PawnSnapshot* pawnSnapshot = getPawnSnapshot();

  /*------------------------------------------------------*/

  GameFieldSnapshot* gameFieldSnapshot = new GameFieldSnapshot();
  
  gameFieldSnapshot->gridSnapshot = blockSnapshotsGrid;
  gameFieldSnapshot->pawnSnapshot = pawnSnapshot;

  gameFieldSnapshots.Add(gameFieldSnapshot);
}


BlockSnapshot* AGridRecoilController::getBlockSnapshot(ABlock* block)
{
  BlockSnapshot* snapshot = new BlockSnapshot();

  snapshot->color = block->color;
  snapshot->prevColor = block->prevColor;
  snapshot->state = block->state;

  return snapshot;
}


PawnSnapshot* AGridRecoilController::getPawnSnapshot()
{
  PawnSnapshot* snapshot = new PawnSnapshot();

  snapshot->gridX = playerPawn->gridX;
  snapshot->gridY = playerPawn->gridY;
  snapshot->color = playerPawn->color;

  return snapshot;
}


void AGridRecoilController::changeBlockBySnapshot(ABlock* block, BlockSnapshot* snapshot)
{
  block->prevColor = snapshot->prevColor;
  block->state = snapshot->state;

  block->setColor(snapshot->color);
}


void AGridRecoilController::changePawnBySnapshot(PawnSnapshot* snapshot)
{
  playerPawn->gridX = snapshot->gridX;
  playerPawn->gridY = snapshot->gridY;

  playerPawn->setColor(snapshot->color);

  ABlock* pawnStatement = (*blocks)[snapshot->gridY][snapshot->gridX];
  playerPawn->SetActorRelativeLocation(pawnStatement->GetActorLocation());
}


void AGridRecoilController::setSnapshot(GameFieldSnapshot* gameFieldSnapshot)
{
  for (int32 y = 0; y < blocks->Num(); y++)
  {
    for (int32 x = 0; x < (*blocks)[0].Num(); x++)
    {
      BlockSnapshot* blockSnapshot = (*(*gameFieldSnapshot->gridSnapshot)[y])[x];
      changeBlockBySnapshot((*blocks)[y][x], (*(*gameFieldSnapshot->gridSnapshot)[y])[x]);
    }
  }

  changePawnBySnapshot(gameFieldSnapshot->pawnSnapshot);
}


void AGridRecoilController::returnToLastSnapshot()
{
  GameFieldSnapshot* lastSnapshot;

  if (gameFieldSnapshots.Num() == 1) 
    lastSnapshot = gameFieldSnapshots.Last();
  else
    lastSnapshot = gameFieldSnapshots.Pop();

  setSnapshot(lastSnapshot);
}


void AGridRecoilController::returnToFirstSnapshot()
{
  GameFieldSnapshot* firtsSnapshot = gameFieldSnapshots[0];
  
  setSnapshot(firtsSnapshot);
  
  gameFieldSnapshots.Empty();

  gameFieldSnapshots.Add(firtsSnapshot);
}




