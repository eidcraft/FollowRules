// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "GameEndPawn.h"
#include "FRPlayerController.h"
#include "GamePauseController.h"
#include "Engine.h"

// Sets default values
AGamePauseController::AGamePauseController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGamePauseController::BeginPlay()
{
	Super::BeginPlay();

  //TActorIterator<ALevelServicesHolder> actorItr(GetWorld());
  //levelServicesHolder = *ALevelServicesHolder;

  TActorIterator<AFRPlayerController> playerControllerItr(GetWorld());
  playerController = *playerControllerItr;

}

// Called every frame
void AGamePauseController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}



void AGamePauseController::pauseGame()
{
  //levelServicesHolder->SetActorTickEnabled(false);
}



void AGamePauseController::unpauseGame()
{
  //levelServicesHolder->SetActorTickEnabled(t);
}