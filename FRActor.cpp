// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "FRActor.h"


// Sets default values
AFRActor::AFRActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFRActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFRActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


bool AFRActor::isActorBelongToGameState(FRGameState searchedState)
{
  for (FRGameState state : gameStateMembership)
  {
    if (state == searchedState) return true;
  }
  return false;
}

