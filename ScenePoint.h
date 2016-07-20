// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ScenePoint.generated.h"

UCLASS()
class FR_API AScenePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScenePoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  /*--------------------------------------------------*/

  USceneComponent* DummyRoot;
  USphereComponent* SphereComponent;


};
