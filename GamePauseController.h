// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FRPlayerController.h"
#include "LevelService.h"

#include "GamePauseController.generated.h"

UCLASS()
class FR_API AGamePauseController : public ALevelService
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePauseController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  AFRPlayerController* playerController;

  //ALevelServicesHolder* levelServicesHolder;

  bool isGamePaused;

  void pauseGame();
  void unpauseGame();
	
};
