// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "LevelService.h"

// Sets default values
ALevelService::ALevelService()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;
  SetActorTickEnabled(false);

}

// Called when the game starts or when spawned
void ALevelService::BeginPlay()
{
  Super::BeginPlay();

}

// Called every frame
void ALevelService::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

