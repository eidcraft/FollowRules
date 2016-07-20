// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TransformationRulesView.generated.h"

UCLASS()
class FR_API ATransformationRulesView : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransformationRulesView();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  USceneComponent* DummyRoot;
  USphereComponent* SphereComponent;

  int32 maxRules = 6;

  void spawnRulesViews(TArray< TArray<int32> >& rules,
    TArray<UMaterial*>& materials, float BlockSpacing);
};


UCLASS()
class FR_API ARuleView : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ARuleView();

  //// Called when the game starts or when spawned
  //virtual void BeginPlay() override;

  //// Called every frame
  //virtual void Tick(float DeltaSeconds) override;

  USceneComponent* DummyRoot;

  UStaticMeshComponent* cubes[2][2];

  void init(TArray<int32>& rule, TArray<UMaterial*>& materials);
};


