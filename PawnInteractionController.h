// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LevelService.h"

#include "Block.h"
#include "PlayerPawn.h"


#include "PawnInteractionController.generated.h"

UCLASS()
class FR_API APawnInteractionController : public ALevelService
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APawnInteractionController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/*--------------------------------------------------*/

  void init(APlayerPawn* playerPawn, 
    TArray<TArray<ABlock*>>& blocksGrid, TArray<TArray<int32>>& transformRules,
    int32 gameStartX, int32 gameStartY, float refreshPeriod);
  
  APlayerPawn* playerPawn;
  TArray<TArray<ABlock*>>* blocksGrid;
  TArray<TArray<int32>>* transformRules;
  
  /*--------------------------------------------------*/
  
  void interact();

  void providePawnInteraction(ABlock* block);
  void tryTransform(ABlock* block);
  void applyTransformRules(ABlock* block);
  TArray<int32> getApplicableRule(ABlock* block);

  /*--------------------------------------------------*/

  float refreshPeriod;
  float refreshTimer;

};
