// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "LevelChooseScene.h"

//
//
//
//
//
//void AGameMenuScene::findResources()
//{
//  // binding buttons
//  for (TActorIterator<AFRButton> buttonItr(GetWorld()); buttonItr; ++buttonItr)
//  {
//    if (buttonItr->GetActorLabel() == FString("GameMenuToLevelButton"))
//      buttonItr->onClicked.AddDynamic(this, &AGameMenuScene::gameMenuToLevelButtonHandler);
//
//    else if (buttonItr->GetActorLabel() == FString("GameMenuToLevelChooseButton"))
//      buttonItr->onClicked.AddDynamic(this, &AGameMenuScene::gameMenuToLevelChooseButtonHandler);
//
//    else if (buttonItr->GetActorLabel() == FString("GameMenuToPropertiesButton"))
//      buttonItr->onClicked.AddDynamic(this, &AGameMenuScene::gameMenuToPropertiesButtonHandler);
//
//    else if (buttonItr->GetActorLabel() == FString("GameMenuToExitButtonHandler"))
//      buttonItr->onClicked.AddDynamic(this, &AGameMenuScene::gameMenuToExitButtonHandler);
//
//    // etc.
//  }
//
//
//  for (TActorIterator<AScenePoint> Itr(GetWorld()); Itr; ++Itr)
//  {
//    if (Itr->GetActorLabel() == FString("GameMenuCameraPosition"))
//      curent = *Itr;
//
//    else if (Itr->GetActorLabel() == FString("LevelCameraPosition"))
//      levelCameraPosition = *Itr;
//
//    else if (Itr->GetActorLabel() == FString("LevelChooseCameraPosition"))
//      levelChooseCameraPosition = *Itr;
//
//    else if (Itr->GetActorLabel() == FString("PropertiesCameraPosition"))
//      propertiesCameraPosition = *Itr;
//
//    else if (Itr->GetActorLabel() == FString("ExitCameraPosition"))
//      exitCameraPosition = *Itr;
//
//    // etc.
//  }
//
//  TActorIterator<ACameraActor> cameraItr(GetWorld());
//  camera = *cameraItr;
//}
//
//
//void AGameMenuScene::gameMenuToLevelButtonHandler()
//{
//  moveCamera(levelCameraPosition);
//}
//
//
//void AGameMenuScene::gameMenuToLevelChooseButtonHandler()
//{
//  moveCamera(levelChooseCameraPosition);
//}
//
//
//void AGameMenuScene::gameMenuToPropertiesButtonHandler()
//{
//  moveCamera(propertiesCameraPosition);
//}
//
//
//void AGameMenuScene::gameMenuToExitButtonHandler()
//{
//  moveCamera(exitCameraPosition);
//}
//
