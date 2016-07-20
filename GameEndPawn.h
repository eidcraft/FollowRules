// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FRActor.h"
#include "Block.h"
#include "GameEndPawn.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOver);


/**
 * 
 */
UCLASS()
class FR_API AGameEndPawn : public AFRActor
{
	GENERATED_BODY()
	
  AGameEndPawn();

  USceneComponent* DummyRoot;
  UStaticMeshComponent* BlockMesh;

public:

  int32 gridX;
  int32 gridY;

  FGameOver gameOver;
  void makeGameOver();

  ABlock* pawnStatement;
  UFUNCTION()
  void OnFingerPressed(ETouchIndex::Type FingerIndex,
    UPrimitiveComponent* TouchedComponent);

  void init(int32 x, int32 y);
  void setPawnStatement(ABlock* pawnStatement);

};
