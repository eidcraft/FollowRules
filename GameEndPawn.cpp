// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "GamePauseController.h"
#include "GameEndPawn.h"
#include "Engine.h"


AGameEndPawn::AGameEndPawn()
{
  DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
  RootComponent = DummyRoot;

  ConstructorHelpers::FObjectFinderOptional<UStaticMesh> planeMesh
    (TEXT("/Game/MobileStarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
  ConstructorHelpers::FObjectFinder<UMaterial> blackMat
    (TEXT("/Game/Puzzle/Meshes/BlackMat.BlackMat"));

  BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
  BlockMesh->SetStaticMesh(planeMesh.Get());
  BlockMesh->SetMaterial(0, blackMat.Object);

  BlockMesh->SetRelativeScale3D(FVector(2.f, 2.f, 0.4f));
  BlockMesh->AttachTo(DummyRoot);

  BlockMesh->OnInputTouchBegin.AddDynamic(this, &AGameEndPawn::OnFingerPressed);
}



void AGameEndPawn::init(int32 x, int32 y)
{
  gridX = x;
  gridY = y;
}

void AGameEndPawn::setPawnStatement(ABlock* pawnStatement)
{
  this->pawnStatement = pawnStatement;

  FVector gameEndPawnInitialCoords = pawnStatement->GetActorLocation();
  this->SetActorRelativeLocation(gameEndPawnInitialCoords + FVector(0.f, 0.f, 50.f));
}


void AGameEndPawn::OnFingerPressed(ETouchIndex::Type FingerIndex,
  UPrimitiveComponent* TouchedComponent)
{
  pawnStatement->onClicked.Broadcast(pawnStatement);
}


void AGameEndPawn::makeGameOver()
{
  gameOver.Broadcast();
}