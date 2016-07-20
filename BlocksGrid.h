// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "Block.h"

#include "BlocksGrid.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBLocksGridWasClicked, ABlock*, clickedBlock);

/**
 * 
 */
UCLASS()
class FR_API ABlocksGrid : public AActor
{
	GENERATED_BODY()
	
	ABlocksGrid();

public:
  /*------------------------------------------------------*/
  // Unreal stuff

  virtual void Tick(float DeltaSeconds);
	virtual void BeginPlay() override;
	
  class USceneComponent* DummyRoot;
  UBoxComponent* BoxComponent;

	/*------------------------------------------------------*/
  // grid create

  void createGrid (TArray< TArray<int32> >& map, TArray<UMaterial*>& materials, float blocksSpacing);
  void spawnBlocks(TArray< TArray<int32> >* map, float blocksSpacing);
  void initBlocks (TArray< TArray<int32> >* map, TArray<UMaterial*>* materials);
  void agregateBlocksOnClickEvents();

  /*------------------------------------------------------*/

  // Event
  FBLocksGridWasClicked gridWasClicked;
  UFUNCTION()
  void gridBlockWasClicked(ABlock* clickedBlock);

  /*------------------------------------------------------*/

  TArray< TArray<ABlock*> > blocks;

};


