// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "Engine.h"
#include "FRCameraController.h"


// Sets default values
AFRCameraController::AFRCameraController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFRCameraController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFRCameraController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AFRCameraController::findResources()
{
  // binding buttons
  for (TActorIterator<AFRButton> buttonItr(GetWorld()); buttonItr; ++buttonItr)
  {
    // toLevel
    if (buttonItr->GetActorLabel() == FString("GameMenuToLevelButton"))
      buttonItr->onClicked.AddDynamic(this, &AFRCameraController::moveToLevel);
    
    // toMainMenu
    else if (buttonItr->GetActorLabel() == FString("LevelChooseToMainMenuButton") ||
             buttonItr->GetActorLabel() == FString("PropertiesToMainMenuButton") ||
             buttonItr->GetActorLabel() == FString("ExitToMainMenuButton"))
      buttonItr->onClicked.AddDynamic(this, &AFRCameraController::moveToMainMenu);

    // toGameMenu
    else if (buttonItr->GetActorLabel() == FString("LevelToGameMenuButton") ||
             buttonItr->GetActorLabel() == FString("PropertiesToGameMenuButton"))
      buttonItr->onClicked.AddDynamic(this, &AFRCameraController::moveToGameMenu);

    // toLevelChoose
    else if (buttonItr->GetActorLabel() == FString("MainMenuToLevelChooseButton") ||
             buttonItr->GetActorLabel() == FString("GameMenuToLevelChooseButton"))
      buttonItr->onClicked.AddDynamic(this, &AFRCameraController::moveToLevelChoose);

    // toProperties
    else if (buttonItr->GetActorLabel() == FString("MainMenuToPropertiesButton") ||
             buttonItr->GetActorLabel() == FString("GameMenuToPropertiesButton"))
      buttonItr->onClicked.AddDynamic(this, &AFRCameraController::moveToProperties);

    // toExit
    else if (buttonItr->GetActorLabel() == FString("MainMenuToExitButtonHandler") ||
             buttonItr->GetActorLabel() == FString("GameMenuToExitButtonHandler"))
      buttonItr->onClicked.AddDynamic(this, &AFRCameraController::moveToExit);

    // etc.
  }


  FString scenePointLabel;
  for (TActorIterator<AScenePoint> scenePointItr(GetWorld()); scenePointItr; ++scenePointItr)
  {
    scenePointLabel = scenePointItr->GetActorLabel();

    if (scenePointLabel == FString("MainMenuCameraPosition"))
      mainMenuCameraPosition = *scenePointItr;

    if (scenePointLabel == FString("GameMainCameraPosition"))
      mainMenuCameraPosition = *scenePointItr;

    else if (scenePointLabel == FString("LevelChooseCameraPosition"))
      levelChooseCameraPosition = *scenePointItr;

    else if (scenePointLabel == FString("PropertiesCameraPosition"))
      propertiesCameraPosition = *scenePointItr;

    else if (scenePointLabel == FString("ExitCameraPosition"))
      exitCameraPosition = *scenePointItr;

    else if (scenePointLabel == FString("LevelCameraPosition"))
      levelCameraPosition = *scenePointItr;
  }

  TActorIterator<ACameraActor> cameraItr(GetWorld());
  camera = *cameraItr;
  
  currentCameraPosition = mainMenuCameraPosition;
}


void AFRCameraController::moveCamera(AScenePoint* destPosition)
{
  FVector departureLocation = currentCameraPosition->GetActorLocation();
  FVector destLocation = destPosition->GetActorLocation();

  FVector routeVector = destLocation - departureLocation;
  float routeLength = routeVector.Size2D();

  stepsToDest = FPlatformMath::RoundToInt(routeLength / cameraSpeed);

  isometricCoeff = routeLength / cameraSpeed;
  routeStep = routeVector / isometricCoeff;

  isCameraMoving = true;
}


void AFRCameraController::makeMovementStep()
{
  if (stepsToDest > 0)
  {
    FVector currentLoc = camera->GetActorLocation();
    camera->SetActorRelativeLocation(currentLoc + routeStep);
    stepsToDest--;
  }
  else
  {
    stopMoving();
  }
}


void AFRCameraController::stopMoving()
{
  isCameraMoving = false;

  isometricCoeff = 0;
  routeStep = FVector(0, 0, 0);
}


void AFRCameraController::moveToLevel()
{
  moveCamera(levelCameraPosition);
}

void AFRCameraController::moveToMainMenu()
{
  moveCamera(mainMenuCameraPosition);
}

void AFRCameraController::moveToGameMenu()
{
  moveCamera(gameMenuCameraPosition);
}

void AFRCameraController::moveToLevelChoose()
{
  moveCamera(levelChooseCameraPosition);
}

void AFRCameraController::moveToProperties()
{
  moveCamera(propertiesCameraPosition);
}

void AFRCameraController::moveToExit()
{
  moveCamera(exitCameraPosition);
}


