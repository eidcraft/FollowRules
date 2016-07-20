// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BlockState.h"

#include "Block.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlockWasClicked, ABlock*, clickedBlock);


/**
 * 
 */
UCLASS()
class FR_API ABlock : public AActor
{
	GENERATED_BODY()

public:
  ABlock();

  USceneComponent* DummyRoot;
  UStaticMeshComponent* BlockMesh;

  /*------------------------------------------------------*/

  void init(int32 initialColor, TArray<UMaterial*>* materials, int32 gridX, int32 gridY);
  
  int32 gridX;
  int32 gridY;

  int32 color;
  int32 prevColor;

  void setColor(int32 color);

  TArray<UMaterial*>* materials; // make static

  BlockState state;

  /*------------------------------------------------------*/

  FBlockWasClicked onClicked;

  UFUNCTION()
  void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
  void broadcastClickEvent();

};
