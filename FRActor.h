// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "FRGameState.h"

#include "FRActor.generated.h"

UCLASS()
class FR_API AFRActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFRActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  TArray<FRGameState> gameStateMembership;

	bool isActorBelongToGameState(FRGameState);
};
