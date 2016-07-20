// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"

#include "LevelLoader.h"
#include "BlocksGrid.h"
#include "PlayerPawn.h"
#include "GameEndPawn.h"

#include "FRLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class FR_API AFRLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
	// Sets default values for this actor's properties
		AFRLevelScript();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/*------------------------------------------------*/

  ALevelLoader* levelLoader;

	TArray<UMaterial*> materials;

	TArray< TArray<int32> > map;
	TArray< TArray<int32> > transformRules;
	TArray< bool > movementRules;
	
	int32 gameStartX;
	int32 gameStartY;
	int32 gameEndX;
	int32 gameEndY;

	int32 playerPawnStartColor;

	float blocksSpacing;
  float refreshPeriod;
  float pawnVelocity;

  /*------------------------------------------------*/

  ABlocksGrid* blocksGrid;
  APlayerPawn* playerPawn;
  AGameEndPawn* endPawn;

  void sceneObjectsInit();
  void sceneServicesInit();

};
