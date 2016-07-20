// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "GameFramework/Actor.h"
#include "FRScene.h"

#include "GameEndPawn.h"

#include "LevelServicesHolder.h"
#include "GridRecoilController.h"

#include "LevelScene.generated.h"

UCLASS()
class FR_API ALevelScene : public AFRScene
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelScene();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

  void findResources();

  AScenePoint* mainMenuCameraPosition;

  ALevelServicesHolder* levelServicesHolder;
  AGridRecoilController* snapshotController;

  UFUNCTION()
    void pauseButtonHandler();
  UFUNCTION()
    void gameMenuButtonHandler();
  UFUNCTION()
    void gameOverHandler();
  UFUNCTION()
    void resetButtonHandler();
  UFUNCTION()
    void undoButtonHandler();

};
