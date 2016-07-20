// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ScenePoint.h"
#include "FRButton.h"
#include "Engine.h"
#include "FRScene.generated.h"

UCLASS()
class FR_API AFRScene : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFRScene();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  /*---------------------------------------------*/

  void findResources();

  ACameraActor* camera;
  AScenePoint* curent;

  /*---------------------------------------------*/

  bool isCameraMoving;
  float cameraSpeed;
  int32 stepsToDest;

  float isometricCoeff;
  FVector routeStep;

  void moveCamera(AScenePoint* destPosition);
  void makeMovementStep();
  void stopMoving();
};
