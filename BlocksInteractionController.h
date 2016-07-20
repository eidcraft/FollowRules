// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LevelService.h"

#include "Block.h"

#include "BlocksInteractionController.generated.h"

/**
 * 
 */
UCLASS()
class FR_API ABlocksInteractionController : public ALevelService
{
	GENERATED_BODY()
  public:
  ABlocksInteractionController();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;


  /*----------------------------------------------------*/

  void init(TArray<TArray<ABlock*>>& blocksGrid, TArray<TArray<int32>>& transformRules, float refreshPeriod);

  TArray<TArray<ABlock*>>* blocks;

  TArray<TArray<int32>>* transformRules;

  /*----------------------------------------------------*/

  void refreshBlocks();
  void sychBlocksStateChange();
  void provideBlocksInteraction(ABlock* sourceBlock, ABlock* destBlock);
  
  void blocksInitiation();
  void provideInitialBlocksInteraction(ABlock* sourceBlock, ABlock* destBlock);

  void tryTakeTransformation(ABlock* sourceBlock, ABlock* destBlock);
  void tryProvideTransformation(ABlock* sourceBlock, ABlock* destBlock);

  void trySpreadChanges(ABlock* sourceBlock, ABlock* destBlock);
  void tryTransformBlocks(ABlock* sourceBlock, ABlock* destBlock);
  void applyTransformRulesToBlocks(ABlock* blockA, ABlock* blockB);
  TArray<int32> getApplicableRule(ABlock* blockA, ABlock* blockB);

  /*----------------------------------------------------*/

  float refreshPeriod;
  float refreshTimer;

};
