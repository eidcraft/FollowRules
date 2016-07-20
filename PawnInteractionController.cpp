// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "PawnInteractionController.h"


// Sets default values
APawnInteractionController::APawnInteractionController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
  SetActorTickEnabled(false);

}

// Called when the game starts or when spawned
void APawnInteractionController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnInteractionController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

  //refreshTimer += DeltaTime;

  //if (refreshTimer >= refreshPeriod)
  //{
  //  refreshTimer = 0.f;
  //  refreshPawn();
  //}
}



void APawnInteractionController::init(APlayerPawn* playerPawn,
  TArray<TArray<ABlock*>>& blocksGrid, TArray<TArray<int32>>& transformRules,
  int32 gameStartX, int32 gameStartY, float refreshPeriod)
{
  this->playerPawn = playerPawn;
  this->blocksGrid =  &blocksGrid;
  this->transformRules = &transformRules;
  this->refreshPeriod = refreshPeriod;

  // install initial grid coords
  playerPawn->gridX = gameStartX;
  playerPawn->gridY = gameStartY;
}



void APawnInteractionController::interact()
{
  // get block what pawn stand on
  ABlock* currentStatement = (*blocksGrid)[playerPawn->gridY][playerPawn->gridX];

  // check thier interaction
  providePawnInteraction(currentStatement);
}



void APawnInteractionController::providePawnInteraction(ABlock* block)
{
  if (block->state == BlockState::idle || block->state == BlockState::interacting)
    tryTransform(block);
}



void APawnInteractionController::tryTransform(ABlock* block)
{
  applyTransformRules(block);

  // block changes
  if (block->color != block->prevColor) block->state = BlockState::changed;
}



void APawnInteractionController::applyTransformRules(ABlock* block)
{
  TArray<int32> applicableRule = getApplicableRule(block);

  if (applicableRule.Num() != 0)
  {
    playerPawn->setColor(applicableRule[2]);
    block->setColor(applicableRule[3]);
  }
}


TArray<int32> APawnInteractionController::getApplicableRule(ABlock* block)
{
  TArray<int32> rule;

  for (size_t iRule = 0; iRule < transformRules->Num(); iRule++)
  {
    rule = (*transformRules)[iRule];

    bool isRuleApplicableToBlockA = (playerPawn->color == rule[0]);
    bool isRuleApplicableToBlockB = (block->color == rule[1]);

    if (isRuleApplicableToBlockA && isRuleApplicableToBlockB) return rule;
  }

  return TArray<int32>();
}


