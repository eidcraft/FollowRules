// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "FRButton.h"


AFRButton::AFRButton()
{
  DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
  RootComponent = DummyRoot;

  ConstructorHelpers::FObjectFinderOptional<UStaticMesh> planeMesh
  (TEXT("/Game/MobileStarterContent/Shapes/Shape_Plane.Shape_Plane"));
  ConstructorHelpers::FObjectFinder<UMaterial> blackMat
  (TEXT("/Game/Puzzle/Meshes/BlackMat.BlackMat"));

  BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
  BlockMesh->SetStaticMesh(planeMesh.Get());
  BlockMesh->SetMaterial(0, blackMat.Object);

  BlockMesh->SetRelativeScale3D(FVector(2.f, 2.f, 0.01f));
  BlockMesh->AttachTo(DummyRoot);

  BlockMesh->OnInputTouchBegin.AddDynamic(this, &AFRButton::OnFingerPressedBlock);

}


void AFRButton::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
  onClicked.Broadcast();
}
