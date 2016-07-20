// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "ClickObject.h"


// Sets default values
AClickObject::AClickObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
  RootComponent = DummyRoot;
}

// Called when the game starts or when spawned
void AClickObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClickObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

