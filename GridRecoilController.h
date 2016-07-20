// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LevelService.h"
#include "BlocksGrid.h"
#include "PlayerPawn.h"
#include "GridRecoilController.generated.h"


//USTRUCT() FR_API
struct BlockSnapshot
{
  int32 color;
  int32 prevColor;
  BlockState state;
};


struct PawnSnapshot
{
  int32 color;
  int32 gridX;
  int32 gridY;
};


struct GameFieldSnapshot
{
  TArray< TArray<BlockSnapshot*>*>* gridSnapshot;
  PawnSnapshot* pawnSnapshot;
};


UCLASS()
class FR_API AGridRecoilController : public ALevelService
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridRecoilController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:
  void init(TArray< TArray<ABlock*> >& blocks, APlayerPawn* playerPawn);

  UFUNCTION()
  void makeSnapshot();

  void returnToLastSnapshot();
  void returnToFirstSnapshot();

private:
  TArray< TArray<ABlock*> >* blocks;
  APlayerPawn* playerPawn;

  /*----------------------------------------------------*/

  TArray< GameFieldSnapshot* > gameFieldSnapshots;

  PawnSnapshot* getPawnSnapshot();
  BlockSnapshot* getBlockSnapshot(ABlock* block);

  void setSnapshot(GameFieldSnapshot* gameFieldSnapshot);
  void changeBlockBySnapshot(ABlock* block, BlockSnapshot* snapshot);
  void changePawnBySnapshot(PawnSnapshot* snapshot);

};


