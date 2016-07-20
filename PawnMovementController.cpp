// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "PawnMovementController.h"

#include "Engine.h"


// Sets default values
APawnMovementController::APawnMovementController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;
  SetActorTickEnabled(false);

  pawnIsMoving = false;
}

// Called when the game starts or when spawned
void APawnMovementController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnMovementController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

  if (pawnIsMoving) tryMovePawn();
}


void APawnMovementController::refreshPawn()
{

}


void APawnMovementController::init(APlayerPawn* playerPawn, AGameEndPawn* gameEndPawn,
  ABlocksGrid* blocksGrid, TArray<bool>& movementRules,
  float blockSpacing, float pawnVelocity,
  APawnInteractionController* pawnInteractionController
  )
{
  this->playerPawn = playerPawn;
  this->gameEndPawn = gameEndPawn;
  this->blocks = &blocksGrid->blocks;
  this->movementRules = &movementRules;
  this->blockSpacing = blockSpacing;
  this->pawnVelocity = pawnVelocity;
  this->pawnInteractionController = pawnInteractionController;

  // subscribe 
  blocksGrid->gridWasClicked.AddDynamic(this, &APawnMovementController::gridWasClickedHandler);

  // move playerPawn to initial place
  ABlock* playerPawnInitialBlock = (*blocks)[playerPawn->gridY][playerPawn->gridX];
  FVector playerPawnInitialCoords = playerPawnInitialBlock->GetActorLocation();
  playerPawn->SetActorRelativeLocation(playerPawnInitialCoords + FVector(0.f, 0.f, 50.f));

  // set gameEndPawn statement block
  ABlock* gameEndPawnStatement = (*blocks)[gameEndPawn->gridY][gameEndPawn->gridX];
  gameEndPawn->setPawnStatement(gameEndPawnStatement);
}



void APawnMovementController::gridWasClickedHandler(ABlock* clickedBlock)
{
  if (pawnIsMoving) return;

  FVector clickedBlockRelativeLoc = getRelativeLocation(clickedBlock);

  bool isRouteTwoDimensional = clickedBlockRelativeLoc.X != 0 && clickedBlockRelativeLoc.Y != 0;

  if (isRouteTwoDimensional) return;

  performMovement(clickedBlockRelativeLoc);
}



FVector APawnMovementController::getRelativeLocation(ABlock* block)
{
  FVector relativeLocation(0.f, 0.f, 0.f);

  relativeLocation.X = block->gridX - playerPawn->gridX;
  relativeLocation.Y = block->gridY - playerPawn->gridY;

  return relativeLocation;
}


void APawnMovementController::performMovement(FVector destVector)
{
  movementDir = getDirection(destVector);
  distanceToDest = getDistanceToDest(destVector);
  
  distanceToBlockBorder = blockSpacing / 2;
  distanceToBlockCenter = 0;

  pawnIsMoving = true;
  playerPawn->invokeBeginMovingEvent();
}



FVector APawnMovementController::getDirection(FVector vector)
{
  FVector direction(0.f, 0.f, 0.f);

  if (vector.X) direction.X = vector.X / FMath::Abs(vector.X);
  if (vector.Y) direction.Y = vector.Y / FMath::Abs(vector.Y);

  return direction;
}


float APawnMovementController::getDistanceToDest(FVector vector)
{
  return FMath::Max(FMath::Abs(vector.X), FMath::Abs(vector.Y));
}


void APawnMovementController::tryMovePawn()
{
  bool isThisBlockAccessable = isBlockAccessable(
    (*blocks)[playerPawn->gridY][playerPawn->gridX]);

  if (!isThisBlockAccessable) stopMovement();
  else movePawn();
}



void APawnMovementController::movePawn()
{
  displacePawn();
  checkTransitionBetwenBlocks();
  checkBlockCenterExceeded();
  checkForGameEnd();
  refreshDistances();
}



void APawnMovementController::refreshDistances()
{
  if (distanceToBlockCenter <= 0) distanceToBlockCenter += blockSpacing;
  if (distanceToBlockBorder <= 0) distanceToBlockBorder += blockSpacing;
}



void APawnMovementController::checkBlockCenterExceeded()
{
  if (distanceToBlockCenter > 0) return;

  bool isRouteEnd = distanceToDest == 0;
  if (isRouteEnd)
  {
    stopMovement();
  }
  else
  {
    distanceToDest -= 1;
    pawnInteractionController->interact();
  }
}


void APawnMovementController::checkTransitionBetwenBlocks()
{
  if (distanceToBlockBorder > 0) return;

  if (isNextBlockAccessable()) 
    setNextBlocksCoordsToPawn();
  else 
    movePawnToLastBlockCenter();//invokeCrashEvent();
}



bool APawnMovementController::isNextBlockAccessable()
{
  int32 nextBlockX = playerPawn->gridX + movementDir.X;
  int32 nextBlockY = playerPawn->gridY + movementDir.Y;

  return isBlockAccessable((*blocks)[nextBlockY][nextBlockX]);
}




void APawnMovementController::displacePawn()
{
  FVector currentLocation = playerPawn->GetActorLocation();
  float curPawnVelocity;

  if (distanceToBlockCenter >= pawnVelocity)
    curPawnVelocity = pawnVelocity;
  else
    curPawnVelocity = distanceToBlockCenter;

  playerPawn->SetActorRelativeLocation(currentLocation + curPawnVelocity * movementDir);

  distanceToBlockCenter -= curPawnVelocity;
  distanceToBlockBorder -= curPawnVelocity;
}



bool APawnMovementController::isBlockAccessable(ABlock* block)
{
  return (*movementRules)[block->color];
}



void APawnMovementController::setNextBlocksCoordsToPawn()
{
  int32 nextBlockX = playerPawn->gridX + movementDir.X;
  int32 nextBlockY = playerPawn->gridY + movementDir.Y;

  playerPawn->gridX = nextBlockX;
  playerPawn->gridY = nextBlockY;
}


void APawnMovementController::stopMovement()
{
  FVector pawnLoc = playerPawn->GetActorLocation();

  GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red,
  	FString::Printf(TEXT("pawn x:%f  y:%f"), pawnLoc.X, pawnLoc.Y));

  pawnIsMoving = false;

  movementDir = FVector(0, 0, 0);
  distanceToDest = 0;
  distanceToBlockBorder = 0;
  distanceToBlockCenter = 0;
}



void APawnMovementController::movePawnToLastBlockCenter()
{
  movementDir = -movementDir;
  distanceToDest = 0;
  distanceToBlockBorder = blockSpacing - distanceToBlockBorder;
  distanceToBlockCenter = blockSpacing - distanceToBlockCenter;
}



void APawnMovementController::checkForGameEnd()
{
  if (distanceToBlockCenter > 0) return;

  FVector playerPawnLoc = playerPawn->GetActorLocation();
  FVector gameEndPawnLoc = gameEndPawn->GetActorLocation();

  bool gameIsOver = playerPawnLoc == gameEndPawnLoc;

  if (gameIsOver) gameEndPawn->makeGameOver();
}
