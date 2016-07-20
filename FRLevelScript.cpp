// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "FRLevelScript.h"

#include "BlocksInteractionController.h"
#include "PawnInteractionController.h"
#include "TransformationRulesView.h"
#include "PawnMovementController.h"
#include "GridRecoilController.h"
#include "LevelServicesHolder.h"

#include "Engine.h"

// Sets default values
AFRLevelScript::AFRLevelScript()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// load materials
	{
		ConstructorHelpers::FObjectFinder<UMaterial>
			BlueMat(TEXT("/Game/Puzzle/Meshes/BlueMat.BlueMat"));
		ConstructorHelpers::FObjectFinder<UMaterial>
			OrangeMat(TEXT("/Game/Puzzle/Meshes/OrangeMat.OrangeMat"));
		ConstructorHelpers::FObjectFinder<UMaterial>
			GreenMat(TEXT("/Game/Puzzle/Meshes/GreenMat.GreenMat"));
		ConstructorHelpers::FObjectFinder<UMaterial>
			PurpleMat(TEXT("/Game/Puzzle/Meshes/PurpleMat.PurpleMat"));
		ConstructorHelpers::FObjectFinder<UMaterial>
			RedMat(TEXT("/Game/Puzzle/Meshes/RedMat.RedMat"));
		ConstructorHelpers::FObjectFinder<UMaterial>
			YellowMat(TEXT("/Game/Puzzle/Meshes/YellowMat.YellowMat"));
		ConstructorHelpers::FObjectFinder<UMaterial>
			WhiteMat(TEXT("/Game/Puzzle/Meshes/WhiteMat.WhiteMat"));

    materials.Add(WhiteMat.Object);
    materials.Add(BlueMat.Object);
		materials.Add(OrangeMat.Object);
		materials.Add(GreenMat.Object);
		materials.Add(PurpleMat.Object);
		materials.Add(RedMat.Object);
		materials.Add(YellowMat.Object);
	}

	// load map
	{
    int32 r1[] = { 1, 0, 0, 0, 0, 0, 0 };
    int32 r2[] = { 0, 0, 0, 0, 0, 0, 0 };
		int32 r3[] = { 0, 3, 3, 3, 3, 0, 0 };
		int32 r4[] = { 0, 0, 0, 0, 0, 0, 0 };
		int32 r5[] = { 0, 3, 3, 3, 3, 2, 2 };
		int32 r6[] = { 0, 3, 0, 0, 0, 0, 2 };
    int32 r7[] = { 0, 1, 1, 1, 1, 2, 2 };
		//int32 r8[] = { 0, 0, 0, 0, 0, 0, 0 };

		TArray<int32> t1;
		TArray<int32> t2;
		TArray<int32> t3;
		TArray<int32> t4;
		TArray<int32> t5;
		TArray<int32> t6;
		TArray<int32> t7;
		//TArray<int32> t8;

		t1.Append(r1, ARRAY_COUNT(r1));
		t2.Append(r2, ARRAY_COUNT(r2));
		t3.Append(r3, ARRAY_COUNT(r3));
		t4.Append(r4, ARRAY_COUNT(r4));
		t5.Append(r5, ARRAY_COUNT(r5));
		t6.Append(r6, ARRAY_COUNT(r6));
		t7.Append(r7, ARRAY_COUNT(r7));
		//t8.Append(r8, ARRAY_COUNT(r8));

		map.Add(t1);
		map.Add(t2);
		map.Add(t3);
		map.Add(t4);
		map.Add(t4);
		map.Add(t5);
		map.Add(t6);
		map.Add(t7);
		//map.Add(t8);
	}

	// load moveRules
	{
    bool mRule[] = { 1, 1, 1, 1, 1, 1};

    movementRules.Append(mRule, ARRAY_COUNT(mRule));
	}

	// load transformation rules
	{
		int32 tmpRuleA[] = { 1, 2, 2, 2 };
		int32 tmpRuleB[] = { 2, 3, 3, 3 };
		int32 tmpRuleC[] = { 3, 1, 1, 1 };
		int32 tmpRuleAd[] = { 2, 1, 2, 2 };
		int32 tmpRuleBd[] = { 3, 2, 3, 3 };
		int32 tmpRuleCd[] = { 1, 3, 1, 1 };

		TArray<int32> ruleA;
		TArray<int32> ruleB;
		TArray<int32> ruleC;
		TArray<int32> ruleAd;
		TArray<int32> ruleBd;
		TArray<int32> ruleCd;

		ruleA.Append(tmpRuleA, ARRAY_COUNT(tmpRuleA));
		ruleB.Append(tmpRuleB, ARRAY_COUNT(tmpRuleB));
		ruleC.Append(tmpRuleC, ARRAY_COUNT(tmpRuleC));
		ruleAd.Append(tmpRuleAd, ARRAY_COUNT(tmpRuleAd));
		ruleBd.Append(tmpRuleBd, ARRAY_COUNT(tmpRuleBd));
		ruleCd.Append(tmpRuleCd, ARRAY_COUNT(tmpRuleCd));

		transformRules.Add(ruleA);
		transformRules.Add(ruleB);
		transformRules.Add(ruleC);
		transformRules.Add(ruleAd);
		transformRules.Add(ruleBd);
		transformRules.Add(ruleCd);
	}

	// load begin play parameters
	{
		gameStartX = 1;
		gameStartY = 1;
		gameEndX = 5;
		gameEndY = 5;

		playerPawnStartColor = 1;
	}

	// load other things
	{
		// all sizes, speeds and other uncategorized numbers
    refreshPeriod = 0.5;
    pawnVelocity = 15;
		blocksSpacing = 280.0;
	}
}

// Called when the game starts or when spawned
void AFRLevelScript::BeginPlay()
{
	Super::BeginPlay();

  TActorIterator<ALevelLoader> levelLoaderItr(GetWorld());
  levelLoader = *levelLoaderItr;
  levelLoader->loadLevel(1);

  /*sceneObjectsInit();
  sceneServicesInit();*/
}

// Called every frame
void AFRLevelScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}


void AFRLevelScript::sceneObjectsInit()
{
  // BlocksGrid
  TActorIterator<ABlocksGrid> BlocksGridItr(GetWorld());
  BlocksGridItr->createGrid(levelLoader->map, levelLoader->materials, levelLoader->blocksSpacing);
  blocksGrid = *BlocksGridItr;

  // Player pawn
  TActorIterator<APlayerPawn> playerPawnItr(GetWorld());
  playerPawnItr->init(levelLoader->materials, levelLoader->playerPawnStartColor);
  playerPawn = *playerPawnItr;

  // Game end pawn
  TActorIterator<AGameEndPawn> endPawnItr(GetWorld());
  endPawnItr->init(levelLoader->gameEndX, levelLoader->gameEndY);
  endPawn = *endPawnItr;

  // ATransformationRulesView
  TActorIterator<ATransformationRulesView> transformationRulesView(GetWorld());
  transformationRulesView->spawnRulesViews(levelLoader->transformRules, levelLoader->materials, levelLoader->blocksSpacing);
}


void AFRLevelScript::sceneServicesInit()
{
  //TActorIterator<ALevelServicesHolder> levelServicesHolder(GetWorld());
  //levelServicesHolder->BeginPlay();
  
  TActorIterator<ABlocksInteractionController> BIC(GetWorld());
  BIC->init(blocksGrid->blocks, levelLoader->transformRules, levelLoader->refreshPeriod);

  // APawnInteractionController
  TActorIterator<APawnInteractionController> pawnInteractionControllerItr(GetWorld());
  pawnInteractionControllerItr->init(playerPawn, blocksGrid->blocks,
    levelLoader->transformRules, levelLoader->gameStartX, levelLoader->gameStartY, levelLoader->refreshPeriod);

  // APawnMovementController
  TActorIterator<APawnMovementController> pawnMovementController(GetWorld());
  pawnMovementController->init(playerPawn, endPawn, blocksGrid,
    levelLoader->pawnPermitedColors, levelLoader->blocksSpacing, levelLoader->pawnVelocity, *pawnInteractionControllerItr);

  // SnapshotController
  TActorIterator<AGridRecoilController> snapshothController(GetWorld());
  snapshothController->init(blocksGrid->blocks, playerPawn);
}
