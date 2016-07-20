// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FRScene.h"
#include "ScenePoint.h"
#include "MainMenuScene.generated.h"

UCLASS()
class FR_API AMainMenuScene : public AFRScene
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainMenuScene();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  void findResources();

  AScenePoint* levelChooseCameraPosition;
  AScenePoint* propertiesCameraPosition;
  AScenePoint* exitCameraPosition;

  UFUNCTION()
    void levelChooseButtonHandler();
  UFUNCTION()
    void propertiesButtonHandler();
  UFUNCTION()
    void exitButtonHandler();
	
};
