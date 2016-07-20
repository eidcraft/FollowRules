// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LevelService.h"


#include "BlocksGrid.h"
#include "PlayerPawn.h"
#include "GameEndPawn.h"
#include "PawnInteractionController.h"
#include "PawnMovementController.generated.h"

UCLASS()
class FR_API APawnMovementController : public ALevelService
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APawnMovementController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  /*--------------------------------------------------*/

  void init(APlayerPawn* playerPawn, AGameEndPawn* gameEndPawn, 
    ABlocksGrid* blocksGrid, TArray<bool>& movementRules, 
    float blockSpacing, float pawnVelocity,
    APawnInteractionController* pawnInteractionController);

  APlayerPawn* playerPawn;
  AGameEndPawn* gameEndPawn;

  TArray<TArray<ABlock*>>* blocks;
  TArray<bool>* movementRules;
  
  float blockSpacing;
  float pawnVelocity;

  UFUNCTION()
  void gridWasClickedHandler(ABlock* clickedBlock);

  /*--------------------------------------------------*/
  
  void performMovement(FVector dest);

  bool pawnIsMoving;

  FVector movementDir;
  int32 distanceToDest;
  float distanceToBlockBorder;
  float distanceToBlockCenter;

  void tryMovePawn();
  void movePawn();
  FVector getDirection(FVector vector);
  float getDistanceToDest(FVector vector);

  FVector getRelativeLocation(ABlock* block);

  void displacePawn();
  void checkBlockCenterExceeded();
  void checkForGameEnd();
  void checkTransitionBetwenBlocks();
  void refreshDistances();

  bool isNextBlockAccessable();
  bool isBlockAccessable(ABlock* block);
  void setNextBlocksCoordsToPawn();
  void stopMovement();
  void movePawnToLastBlockCenter();

  /*--------------------------------------------------*/

  APawnInteractionController* pawnInteractionController;

  void refreshPawn();
	
};
