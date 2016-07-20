// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "ScenePoint.h"


// Sets default values
AScenePoint::AScenePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
  RootComponent = DummyRoot;

  SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent0"));
  SphereComponent->AttachTo(DummyRoot);
  SphereComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AScenePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScenePoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

