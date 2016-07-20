// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "BlocksInteractionController.h"



// Sets default values
ABlocksInteractionController::ABlocksInteractionController()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABlocksInteractionController::BeginPlay()
{
  Super::BeginPlay();

  blocksInitiation();
}

// Called every frame
void ABlocksInteractionController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  refreshTimer += DeltaTime;
  
  if (refreshTimer >= refreshPeriod)
  {
    refreshTimer = 0.f;
    sychBlocksStateChange();
    refreshBlocks();
  }
}



void ABlocksInteractionController::init(TArray<TArray<ABlock*>>& blocksGrid, 
  TArray<TArray<int32>>& transformRules, float refreshPeriod)
{
  this->blocks = &blocksGrid;
  this->transformRules = &transformRules;
  this->refreshPeriod = refreshPeriod;
}



void ABlocksInteractionController::refreshBlocks()
{
  ABlock* block;
  ABlock* neighbor;

  int32 nRow = blocks->Num();
  int32 nColumn = (*blocks)[0].Num();

  for (int32 iBlocksRow = 0; iBlocksRow != blocks->Num(); iBlocksRow++)
  {
    for (int32 iBlock = 0; iBlock != (*blocks)[iBlocksRow].Num(); iBlock++)
    {
      block = (*blocks)[iBlocksRow][iBlock];

      if (iBlock < nColumn - 1)
      {
        neighbor = (*blocks)[iBlocksRow][iBlock + 1];
        provideBlocksInteraction(block, neighbor);
      }

      if (iBlocksRow < nRow - 1)
      {
        neighbor = (*blocks)[iBlocksRow + 1][iBlock];
        provideBlocksInteraction(block, neighbor);
      }
    }
  }
}



void ABlocksInteractionController::sychBlocksStateChange()
{
  ABlock* block;

  for (int32 iBlocksRow = 0; iBlocksRow != blocks->Num(); iBlocksRow++)
  {
    for (int32 iBlock = 0; iBlock != (*blocks)[iBlocksRow].Num(); iBlock++)
    {
      block = (*blocks)[iBlocksRow][iBlock];


      if (block->state == BlockState::changed) 
      {
        block->state = BlockState::spreading;
      }
      else if (block->state == BlockState::spreading) 
      {
        block->state = BlockState::interacting;
        block->prevColor = block->color;
      }
    }
  }
}



void ABlocksInteractionController::provideBlocksInteraction(ABlock* sourceBlock, ABlock* destBlock)
{
  if (sourceBlock->state == BlockState::idle) tryTakeTransformation(sourceBlock, destBlock);
  
  else if (sourceBlock->state == BlockState::spreading) trySpreadChanges(sourceBlock, destBlock);
  
  else if (sourceBlock->state == BlockState::interacting) tryProvideTransformation(sourceBlock, destBlock);
}



void ABlocksInteractionController::tryTakeTransformation(ABlock* sourceBlock, ABlock* destBlock)
{
  if (destBlock->state == BlockState::interacting) tryTransformBlocks(destBlock, sourceBlock);
  else if (destBlock->state == BlockState::spreading) trySpreadChanges(destBlock, sourceBlock);
}



void ABlocksInteractionController::trySpreadChanges(ABlock* sourceBlock, ABlock* destBlock)
{
  if (destBlock->state == BlockState::idle) 
  {
    // trySpreadChangesToBlock
    if (destBlock->color == sourceBlock->prevColor) destBlock->setColor(sourceBlock->color);

    // destBlock changes
    if (destBlock->color != destBlock->prevColor) destBlock->state = BlockState::changed;
  }

  // sourceBlock changes
  // sourceBlock->state = BlockState::interacting;
}



void ABlocksInteractionController::tryProvideTransformation(ABlock* sourceBlock, ABlock* destBlock)
{
  if (destBlock->state == BlockState::idle) tryTransformBlocks(sourceBlock, destBlock);
}



void ABlocksInteractionController::tryTransformBlocks(ABlock* sourceBlock, ABlock* destBlock)
{
  applyTransformRulesToBlocks(sourceBlock, destBlock);

  // sourceBlock changes
  if (sourceBlock->color == sourceBlock->prevColor) sourceBlock->state = BlockState::idle;
  else sourceBlock->state = BlockState::changed;

  // destBlock changes
  if (destBlock->color != destBlock->prevColor) destBlock->state = BlockState::changed;
}



void ABlocksInteractionController::applyTransformRulesToBlocks(ABlock* blockA, ABlock* blockB)
{
  TArray<int32> applicableRule = getApplicableRule(blockA, blockB);

  if (applicableRule.Num() != 0)
  {
    blockA->setColor(applicableRule[2]);
    blockB->setColor(applicableRule[3]);
  }
}



TArray<int32> ABlocksInteractionController::getApplicableRule(ABlock* blockA, ABlock* blockB)
{
  TArray<int32> rule;

  for (size_t iRule = 0; iRule < transformRules->Num(); iRule++)
  {
    rule = (*transformRules)[iRule];

    bool isRuleApplicableToBlockA = (blockA->color == rule[0]);
    bool isRuleApplicableToBlockB = (blockB->color == rule[1]);

    if (isRuleApplicableToBlockA && isRuleApplicableToBlockB) return rule;
  }

  return TArray<int32>();
}




void ABlocksInteractionController::blocksInitiation()
{
  ABlock* block;
  ABlock* neighbor;

  int32 nRow = blocks->Num();
  int32 nColumn = (*blocks)[0].Num();

  for (int32 iBlocksRow = 0; iBlocksRow != blocks->Num(); iBlocksRow++)
  {
    for (int32 iBlock = 0; iBlock != (*blocks)[iBlocksRow].Num(); iBlock++)
    {
      block = (*blocks)[iBlocksRow][iBlock];

      if (iBlock < nColumn - 1)
      {
        neighbor = (*blocks)[iBlocksRow][iBlock + 1];
        provideInitialBlocksInteraction(block, neighbor);
      }

      if (iBlocksRow < nRow - 1)
      {
        neighbor = (*blocks)[iBlocksRow + 1][iBlock];
        provideInitialBlocksInteraction(block, neighbor);
      }
    }
  }
}



void ABlocksInteractionController::provideInitialBlocksInteraction(ABlock* sourceBlock, ABlock* destBlock)
{
  if (sourceBlock->state == BlockState::idle && destBlock->state == BlockState::idle)
    tryTransformBlocks(sourceBlock, destBlock);

  if (sourceBlock->state == BlockState::idle && destBlock->state == BlockState::idle)
    tryTransformBlocks(destBlock, sourceBlock);
}

