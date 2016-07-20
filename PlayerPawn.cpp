// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "Engine.h"
#include "PlayerPawn.h"




APlayerPawn::APlayerPawn() 
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

  BlockMesh->SetRelativeScale3D(FVector(2.f, 2.f, 0.2f));
  BlockMesh->AttachTo(DummyRoot);

}

void APlayerPawn::setColor(int32 color)
{
  this->color = color;

  BlockMesh->SetMaterial(0, (*materials)[color]);
}


void APlayerPawn::init(TArray<UMaterial*>& materials, int32 initialColor)
{
  this->materials = &materials;

  setColor(initialColor);
}


void APlayerPawn::invokeBeginMovingEvent()
{
  onMovingBegin.Broadcast();
}
