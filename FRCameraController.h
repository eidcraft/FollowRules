// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ScenePoint.h"
#include "FRButton.h"
#include "FRCameraController.generated.h"

UCLASS()
class FR_API AFRCameraController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFRCameraController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  /*-----------------------------------------------*/

  void findResources();

  ACameraActor* camera;

  /*-----------------------------------------------*/
  
  AScenePoint* currentCameraPosition;

  AScenePoint* mainMenuCameraPosition;
  AScenePoint* gameMenuCameraPosition;
  AScenePoint* levelCameraPosition;
  AScenePoint* levelChooseCameraPosition;
  AScenePoint* propertiesCameraPosition;
  AScenePoint* exitCameraPosition;
  
  /*-----------------------------------------------*/

  bool isCameraMoving;
  float cameraSpeed;
  int32 stepsToDest;

  float isometricCoeff;
  FVector routeStep;

  void moveCamera(AScenePoint* destPosition);
  void makeMovementStep();
  void stopMoving();

  /*-----------------------------------------------*/

  UFUNCTION()
    void moveToMainMenu();
  UFUNCTION()
    void moveToGameMenu();
  UFUNCTION()
    void moveToLevel();
  UFUNCTION()
    void moveToLevelChoose();
  UFUNCTION()
    void moveToProperties();
  UFUNCTION()
    void moveToExit();
	
};
