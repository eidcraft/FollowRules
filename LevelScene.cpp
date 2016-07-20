// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "LevelScene.h"
#include "LevelServicesHolder.h"


// Sets default values
ALevelScene::ALevelScene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelScene::BeginPlay()
{
	Super::BeginPlay();
	
  findResources();
}


void ALevelScene::findResources()
{
  // binding end pawn
  TActorIterator<AGameEndPawn> gameEndPawnItr(GetWorld());
  gameEndPawnItr->gameOver.AddDynamic(this, &ALevelScene::gameOverHandler);


  // binding buttons
  for (TActorIterator<AFRButton> buttonItr(GetWorld()); buttonItr; ++buttonItr)
  {
    if (buttonItr->GetActorLabel() == FString("PauseButton"))
      buttonItr->onClicked.AddDynamic(this, &ALevelScene::pauseButtonHandler);

    else if (buttonItr->GetActorLabel() == FString("GameMenuButton"))
      buttonItr->onClicked.AddDynamic(this, &ALevelScene::gameMenuButtonHandler);
    
    else if (buttonItr->GetActorLabel() == FString("UndoButton"))
      buttonItr->onClicked.AddDynamic(this, &ALevelScene::undoButtonHandler);

    else if (buttonItr->GetActorLabel() == FString("ResetButton"))
      buttonItr->onClicked.AddDynamic(this, &ALevelScene::resetButtonHandler);
    // etc.
  }


  for (TActorIterator<AScenePoint>  Itr(GetWorld());  Itr; ++ Itr)
  {
    if ( Itr->GetActorLabel() == FString("LevelCameraPosition"))
      curent  = * Itr;

    else if ( Itr->GetActorLabel() == FString("MainMenuCameraPosition"))
      mainMenuCameraPosition = * Itr;
          
    // etc.
  }

  TActorIterator<ALevelServicesHolder> levelServicesHolderItr(GetWorld());
  levelServicesHolder = *levelServicesHolderItr;

  TActorIterator<AGridRecoilController> snapshotControllerItr(GetWorld());
  snapshotController = *snapshotControllerItr;

  TActorIterator<ACameraActor> cameraItr(GetWorld());
  camera = *cameraItr;
}


// Called every frame
void ALevelScene::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

  //if (isCameraMoving) makeMovementStep();
}


void ALevelScene::pauseButtonHandler()
{
  GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, FString("pauseButtonHandler"));
  levelServicesHolder->startStopServices();
}


void ALevelScene::gameMenuButtonHandler()
{
  GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, FString("mainMenuCameraPosition"));
  moveCamera(mainMenuCameraPosition);
}


void ALevelScene::gameOverHandler()
{
  GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, FString("gameOverHandler"));

  //(*pauseControllerItr)->pauseGame();
}


void ALevelScene::undoButtonHandler()
{
  GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, FString("undoButtonHandler"));

  snapshotController->returnToLastSnapshot();
}


void ALevelScene::resetButtonHandler()
{
  GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, FString("resetButtonHandler"));
  
  snapshotController->returnToFirstSnapshot();
}
