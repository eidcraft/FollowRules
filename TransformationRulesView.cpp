// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "Engine.h"
#include "TransformationRulesView.h"


// Sets default values
ATransformationRulesView::ATransformationRulesView()
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
void ATransformationRulesView::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATransformationRulesView::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ATransformationRulesView::spawnRulesViews(TArray< TArray<int32> >& rules, 
  TArray<UMaterial*>& materials, float BlockSpacing)
{
  FVector baseLocation = GetActorLocation();
  FVector ruleViewLocation;

  ARuleView* ruleView;

  int32 nUniqueRules = rules.Num() / 2;

  for (int32 iRule = 0; iRule < nUniqueRules; iRule++)
  {
    ruleViewLocation = baseLocation + FVector(iRule * BlockSpacing, 0, 0);
      
    ruleView = GetWorld()->SpawnActor<ARuleView>(ruleViewLocation, FRotator(0, 0, 0));

    ruleView->init(rules[iRule], materials);
  }
}


ARuleView::ARuleView()
{
  DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
  RootComponent = DummyRoot;

  ConstructorHelpers::FObjectFinder<UStaticMesh> planeMesh(
    TEXT("/Game/MobileStarterContent/Shapes/Shape_Plane.Shape_Plane"));

  UStaticMeshComponent* cube;

  for (size_t y = 0; y < 2; y++)
  {
    for (size_t x = 0; x < 2; x++)
    {
      cube = CreateDefaultSubobject<UStaticMeshComponent>(
        *FString::Printf(TEXT("cubeMesh%i%i"), y, x));

      cube->SetStaticMesh(planeMesh.Object);
      cube->SetRelativeScale3D(FVector(1.2f, 1.2f, 0.05f));
      cube->SetRelativeLocation(GetActorLocation() + FVector(120.f * x, 130.f * y, 0.f));
      cube->AttachTo(DummyRoot);
      cubes[y][x] = cube;
    }
  }
}


void ARuleView::init(TArray<int32>& rule, TArray<UMaterial*>& materials)
{
  cubes[0][0]->SetMaterial(0, materials[rule[0]]);
  cubes[0][1]->SetMaterial(0, materials[rule[1]]);
  cubes[1][0]->SetMaterial(0, materials[rule[2]]);
  cubes[1][1]->SetMaterial(0, materials[rule[3]]);
}