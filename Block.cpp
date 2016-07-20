// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "Block.h"

#include "Engine.h"

ABlock::ABlock()
{
    DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
    RootComponent = DummyRoot;

	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> planeMesh
		(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"));
	ConstructorHelpers::FObjectFinder<UMaterial> blackMat
		(TEXT("/Game/Puzzle/Meshes/BlackMat.BlackMat"));

  BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
  BlockMesh->SetStaticMesh(planeMesh.Get());
  BlockMesh->SetMaterial(0, blackMat.Object);

  //BlockMesh->SetRelativeScale3D(FVector(2.5f, 2.5f, 1.f));
  BlockMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.4f));

  BlockMesh->AttachTo(RootComponent);

  BlockMesh->OnInputTouchBegin.AddDynamic(this, &ABlock::OnFingerPressedBlock);

}


void ABlock::init(int32 initialColor, TArray<UMaterial*>* materials, int32 x, int32 y)
{
  this->materials = materials;
  setColor(initialColor);
  prevColor = initialColor;

  gridX = x;
  gridY = y;
}


void ABlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
  broadcastClickEvent();

  //FVector loc = GetActorLocation();
  //GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red,
  //  FString::Printf(TEXT("Block x:%f  y:%f"), loc.X, loc.Y));
}


void ABlock::broadcastClickEvent()
{
  onClicked.Broadcast(this);
}


void ABlock::setColor(int32 color)
{
  this->color = color;

  BlockMesh->SetMaterial(0, (*materials)[color]);
}




