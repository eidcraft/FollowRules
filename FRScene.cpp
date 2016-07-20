// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "FRScene.h"


// Sets default values
AFRScene::AFRScene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  cameraSpeed = 200;

}

// Called when the game starts or when spawned
void AFRScene::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFRScene::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

  if (isCameraMoving) makeMovementStep();
}

void AFRScene::findResources()
{

}



void AFRScene::moveCamera(AScenePoint* destPosition)
{
  FVector departureLocation = curent->GetActorLocation();
  FVector destLocation = destPosition->GetActorLocation();

  FVector routeVector = destLocation - departureLocation;
  float routeLength = routeVector.Size2D();

  stepsToDest = FPlatformMath::RoundToInt(routeLength / cameraSpeed);

  isometricCoeff = routeLength / cameraSpeed;
  routeStep = routeVector / isometricCoeff;

  isCameraMoving = true;
}


void AFRScene::makeMovementStep()
{
  if (stepsToDest > 0)
  {
    FVector currentLoc = camera->GetActorLocation();
    camera->SetActorRelativeLocation(currentLoc + routeStep);
    stepsToDest--;
  }
  else
  {
    stopMoving();
  }
}


void AFRScene::stopMoving()
{
  isCameraMoving = false;

  isometricCoeff = 0;
  routeStep = FVector(0, 0, 0);
}


