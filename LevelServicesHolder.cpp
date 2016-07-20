// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"

#include "BlocksInteractionController.h"
#include "GamePauseController.h"
#include "GridRecoilController.h"
#include "PawnInteractionController.h"
#include "PawnMovementController.h"

#include "LevelServicesHolder.h"


// Sets default values
ALevelServicesHolder::ALevelServicesHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelServicesHolder::BeginPlay()
{
	Super::BeginPlay();

  this->SetActorTickEnabled(true);
  isServicesWork = true;
}

// Called every frame
void ALevelServicesHolder::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

  transitTick(DeltaTime);
}


void ALevelServicesHolder::spawnServices()
{
  UWorld* world = GetWorld();
  ALevelService* service;

  service = world->SpawnActor<AGridRecoilController>(FVector(0, 0, 0), FRotator(0, 0, 0));
  services.Add(service);

  service = world->SpawnActor<APawnMovementController>(FVector(0, 0, 0), FRotator(0, 0, 0));
  services.Add(service);

  service = world->SpawnActor<ABlocksInteractionController>(FVector(0, 0, 0), FRotator(0, 0, 0));
  services.Add(service);

  service = world->SpawnActor<APawnInteractionController>(FVector(0, 0, 0), FRotator(0, 0, 0));
  services.Add(service);
}


void ALevelServicesHolder::PreInitializeComponents()
{
  spawnServices();
}


void ALevelServicesHolder::transitTick(float DeltaSeconds)
{
  for (ALevelService* service : services)
  {
    service->Tick(DeltaSeconds);
  }
}


void ALevelServicesHolder::stopServices()
{
  SetActorTickEnabled(false);
  isServicesWork = false;
}


void ALevelServicesHolder::startServices()
{
  SetActorTickEnabled(true);
  isServicesWork = true;
}


void ALevelServicesHolder::startStopServices()
{
  if (isServicesWork) stopServices();
  else startServices();
}
