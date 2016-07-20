// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FRButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonWasClicked);

/**
 * 
 */
UCLASS()
class FR_API AFRButton : public AActor
{
	GENERATED_BODY()

public:
  FButtonWasClicked onClicked;

private:
  AFRButton();

  USceneComponent* DummyRoot;
  UStaticMeshComponent* BlockMesh;

  UFUNCTION()
  void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	
};
