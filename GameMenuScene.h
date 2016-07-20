// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FRScene.h"
#include "GameMenuScene.generated.h"

/**
 * 
 */
UCLASS()
class FR_API AGameMenuScene : public AFRScene
{
	GENERATED_BODY()
	
  void findResources();

  AScenePoint* levelCameraPosition;
  AScenePoint* levelChooseCameraPosition;
  AScenePoint* propertiesCameraPosition;
  AScenePoint* exitCameraPosition;

  UFUNCTION()
    void gameMenuToLevelButtonHandler();
  UFUNCTION()
    void gameMenuToLevelChooseButtonHandler();
  UFUNCTION()
    void gameMenuToPropertiesButtonHandler();
  UFUNCTION()
    void gameMenuToExitButtonHandler();

	
	
};
