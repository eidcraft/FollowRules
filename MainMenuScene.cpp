// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "MainMenuScene.h"


// Sets default values
AMainMenuScene::AMainMenuScene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMenuScene::BeginPlay()
{
	Super::BeginPlay();
	
  findResources();
}

// Called every frame
void AMainMenuScene::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AMainMenuScene::findResources()
{
  // binding buttons
  for (TActorIterator<AFRButton> buttonItr(GetWorld()); buttonItr; ++buttonItr)
  {
    if (buttonItr->GetActorLabel() == FString("LevelChooseButton"))
      buttonItr->onClicked.AddDynamic(this, &AMainMenuScene::levelChooseButtonHandler);

    else if (buttonItr->GetActorLabel() == FString("PropertiesButton"))
      buttonItr->onClicked.AddDynamic(this, &AMainMenuScene::propertiesButtonHandler);

    else if (buttonItr->GetActorLabel() == FString("ExitButton"))
      buttonItr->onClicked.AddDynamic(this, &AMainMenuScene::exitButtonHandler);

    // etc.
  }

  for (TActorIterator<AScenePoint> Itr(GetWorld()); Itr; ++Itr)
  {
    if (Itr->GetActorLabel() == FString("MainMenuCameraPosition"))
      curent = *Itr;

    else if (Itr->GetActorLabel() == FString("LevelChooseCameraPosition"))
      levelChooseCameraPosition = *Itr;

    else if (Itr->GetActorLabel() == FString("PropertiesCameraPosition"))
      propertiesCameraPosition = *Itr;

    else if (Itr->GetActorLabel() == FString("ExitCameraPosition"))
      exitCameraPosition = *Itr;
    
    // etc.
  }

  TActorIterator<ACameraActor> cameraItr(GetWorld());
  camera = *cameraItr;
}


void AMainMenuScene::levelChooseButtonHandler()
{
  moveCamera(levelChooseCameraPosition);
}


void AMainMenuScene::propertiesButtonHandler()
{
  moveCamera(propertiesCameraPosition);
}


void AMainMenuScene::exitButtonHandler()
{
  moveCamera(exitCameraPosition);
}


