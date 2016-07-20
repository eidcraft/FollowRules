// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "CoreMisc.h"
#include "Json.h"

#include "BlocksInteractionController.h"
#include "PawnInteractionController.h"
#include "TransformationRulesView.h"
#include "PawnMovementController.h"
#include "GridRecoilController.h"
#include "LevelServicesHolder.h"

#include "LevelLoader.generated.h"

UCLASS()
class FR_API ALevelLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelLoader();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  /*---------------------------------------------------------*/

  TArray<UMaterial*> materials;

  TArray< TArray<int32> > map;
  TArray< TArray<int32> > transformRules;
  TArray< bool > pawnPermitedColors;

  int32 gameStartX;
  int32 gameStartY;
  int32 gameEndX;
  int32 gameEndY;

  int32 playerPawnStartColor;

  float blocksSpacing;
  float refreshPeriod;
  float pawnVelocity;

  /*---------------------------------------------------------*/
  
  void loadLevel(int32 levelNumber);
  void loadMaterials();

  TSharedPtr<FJsonObject> parseLevelFromString(FString& fileInner);

  void createLevelObjectsFromJson(TSharedPtr<FJsonObject>& jsonParsedLevel);
  void createLevelMapFromJson(TArray <TSharedPtr<FJsonValue>>& jsonMapInStrings);
  void createRulesFromJson(TArray <TSharedPtr<FJsonValue>>& rulesInStrings);
  void createPawnPermittedColorsFromJson(TArray <TSharedPtr<FJsonValue>>& permitions);

  /*---------------------------------------------------------*/

  ABlocksGrid* blocksGrid;
  APlayerPawn* playerPawn;
  AGameEndPawn* endPawn;

  void levelServicesInit();
  void levelObjectsInit();

};

