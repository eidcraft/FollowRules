// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "CoreMisc.h"
#include "Json.h"
#include "LevelLoader.h"
#include "Engine.h"

// Sets default values
ALevelLoader::ALevelLoader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  loadMaterials();
}
 
// Called when the game starts or when spawned
void ALevelLoader::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelLoader::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ALevelLoader::loadLevel(int32 levelNumber)
{
  FString gameDir = FPaths::GameDir();
  FString fullFilePath = gameDir + "Content/Levels/Level-" + 
    FString::FromInt(levelNumber) + ".json";

  FString result;
  
  FFileHelper::LoadFileToString(result, *fullFilePath, 1);

  TSharedPtr<FJsonObject> jsonParsedLevel = parseLevelFromString(result);

  createLevelObjectsFromJson(jsonParsedLevel);

  levelObjectsInit();
  levelServicesInit();
}


TSharedPtr<FJsonObject> ALevelLoader::parseLevelFromString(FString& fileInner)
{
  TSharedPtr<FJsonObject> JsonParsed;
  TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(fileInner);

  if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
  {
    return JsonParsed;
  }
  return nullptr;
}


void ALevelLoader::createLevelObjectsFromJson(TSharedPtr<FJsonObject>& jsonParsedLevel)
{
  // FString ExampleString = JsonParsed->GetStringField("exampleString");
  // int size = jsonParsedLevel->GetNumberField("size");

  TArray <TSharedPtr<FJsonValue>> mapAsStringsArray = 
    jsonParsedLevel->GetArrayField("levelMap");
  createLevelMapFromJson(mapAsStringsArray);

  TArray <TSharedPtr<FJsonValue>> perimitionsAsStringsArray =
    jsonParsedLevel->GetArrayField("pawnPermittedColors");
  createPawnPermittedColorsFromJson(perimitionsAsStringsArray);

  TArray <TSharedPtr<FJsonValue>> rulesAsStringsArray =
    jsonParsedLevel->GetArrayField("colorsTransformationRules");
  createRulesFromJson(rulesAsStringsArray);

  gameStartX = jsonParsedLevel->GetNumberField("gameStartX");
  gameStartY = jsonParsedLevel->GetNumberField("gameStartY");
  gameEndX = jsonParsedLevel->GetNumberField("gameEndX");
  gameEndY = jsonParsedLevel->GetNumberField("gameEndY");

  playerPawnStartColor = jsonParsedLevel->GetNumberField("playerPawnStartColor");

  refreshPeriod = jsonParsedLevel->GetNumberField("refreshPeriod");
  pawnVelocity = jsonParsedLevel->GetNumberField("pawnVelocity");
  blocksSpacing = jsonParsedLevel->GetNumberField("blocksSpacing");
}


void ALevelLoader::createLevelMapFromJson(TArray <TSharedPtr<FJsonValue>>& mapAsStringsArray)
{
  TArray<TArray<TSharedPtr<FJsonValue>>> stringsArray;
  TArray <TSharedPtr<FJsonValue>> stringsRow;

  for (TSharedPtr<FJsonValue> mapString : mapAsStringsArray)
  {
    stringsRow = mapString->AsArray();
    stringsArray.Add(stringsRow);
  }

  TArray<int32> mapRow;
  for (int32 iRow = 0; iRow != stringsArray.Num(); iRow++)
  {
    for (int32 iColumn = 0; iColumn != stringsArray[0].Num(); iColumn++)
    {
      mapRow.Add(stringsArray[iRow][iColumn]->AsNumber());
    }
    map.Add(mapRow);
    mapRow.Empty();
  }
}


void ALevelLoader::createPawnPermittedColorsFromJson(
  TArray <TSharedPtr<FJsonValue>>& jsonPermitions)
{
  for (int32 iPermition = 0; iPermition != jsonPermitions.Num(); iPermition++)
  {
    pawnPermitedColors.Add(jsonPermitions[iPermition]->AsBool());
  }
}


void ALevelLoader::createRulesFromJson(TArray <TSharedPtr<FJsonValue>>& rulesInStrings)
{
  TArray<TArray<TSharedPtr<FJsonValue>>> stringsArray;
  TArray <TSharedPtr<FJsonValue>> stringsRow;

  for (TSharedPtr<FJsonValue> ruleAsString : rulesInStrings)
  {
    stringsRow = ruleAsString->AsArray();
    stringsArray.Add(stringsRow);
  }

  TArray<int32> rulesRow;
  for (int32 iRow = 0; iRow != stringsArray.Num(); iRow++)
  {
    for (int32 iColumn = 0; iColumn != stringsArray[0].Num(); iColumn++)
    {
      rulesRow.Add(stringsArray[iRow][iColumn]->AsNumber());
    }
    transformRules.Add(rulesRow);
    rulesRow.Empty();
  }

  for (int32 iRow = 0; iRow != stringsArray.Num(); iRow++)
  {
    for (int32 iColumn = 0; iColumn != stringsArray[0].Num(); iColumn++)
    {
      if (iColumn == 0) 
        rulesRow.Add(transformRules[iRow][1]);
      else if (iColumn == 1) 
        rulesRow.Add(transformRules[iRow][0]);
      else 
        rulesRow.Add(transformRules[iRow][iColumn]);
    }
    transformRules.Add(rulesRow);
    rulesRow.Empty();
  }
}


void ALevelLoader::loadMaterials()
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


void ALevelLoader::levelObjectsInit()
{
  // BlocksGrid
  TActorIterator<ABlocksGrid> BlocksGridItr(GetWorld());
  BlocksGridItr->createGrid(map, materials, blocksSpacing);
  blocksGrid = *BlocksGridItr;

  // Player pawn
  TActorIterator<APlayerPawn> playerPawnItr(GetWorld());
  playerPawnItr->init(materials, playerPawnStartColor);
  playerPawn = *playerPawnItr;

  // Game end pawn
  TActorIterator<AGameEndPawn> endPawnItr(GetWorld());
  endPawnItr->init(gameEndX, gameEndY);
  endPawn = *endPawnItr;

  // ATransformationRulesView
  TActorIterator<ATransformationRulesView> transformationRulesView(GetWorld());
  transformationRulesView->spawnRulesViews(transformRules, materials, blocksSpacing);
}


void ALevelLoader::levelServicesInit()
{
  TActorIterator<ABlocksInteractionController> BIC(GetWorld());
  BIC->init(blocksGrid->blocks, transformRules, refreshPeriod);

  // APawnInteractionController
  TActorIterator<APawnInteractionController> pawnInteractionControllerItr(GetWorld());
  pawnInteractionControllerItr->init(playerPawn, blocksGrid->blocks,
    transformRules, gameStartX, gameStartY, refreshPeriod);

  // APawnMovementController
  TActorIterator<APawnMovementController> pawnMovementController(GetWorld());
  pawnMovementController->init(playerPawn, endPawn, blocksGrid,
    pawnPermitedColors, blocksSpacing, pawnVelocity, *pawnInteractionControllerItr);

  // SnapshotController
  TActorIterator<AGridRecoilController> snapshothController(GetWorld());
  snapshothController->init(blocksGrid->blocks, playerPawn);
}
