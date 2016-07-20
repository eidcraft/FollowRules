// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelService.h"
#include "LevelServicesHolder.generated.h"

UCLASS()
class FR_API ALevelServicesHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelServicesHolder();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
  // a s s 
  void PreInitializeComponents() override;

  void spawnServices();

  void stopServices();
  void startServices();
  void startStopServices();

  void transitTick(float DeltaSeconds);

	TArray<ALevelService*> services;

  bool isServicesWork;
	
};
