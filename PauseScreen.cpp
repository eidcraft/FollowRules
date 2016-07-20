// Fill out your copyright notice in the Description page of Project Settings.

#include "FR.h"
#include "PauseScreen.h"
#include "ScenePoint.h"	
#include "Engine.h"

// Sets default values
APauseScreen::APauseScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


  meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("screenMesh0"));

  ConstructorHelpers::FObjectFinderOptional<UStaticMesh> staticMesh
    (TEXT("/Game/MobileStarterContent/Shapes/Shape_Cube.Shape_Cube"));
  meshComponent->SetStaticMesh(staticMesh.Get());

  ConstructorHelpers::FObjectFinder<UMaterialInstance>
    materialFinder(TEXT("/Game/Puzzle/Meshes/PauseScreenMaterial.PauseScreenMaterial"));
  material = materialFinder.Object;
  meshComponent->SetMaterial(0, material);

  meshComponent->SetRelativeScale3D(FVector(10.f, 10.f, 0.2f));
  meshComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

  meshComponent->OnInputTouchBegin.AddDynamic(this, &APauseScreen::OnFingerPressedHandler);


  dynamicMaterial = meshComponent->CreateAndSetMaterialInstanceDynamic(0);
  dynamicMaterial->SetScalarParameterValue(FName(TEXT("opacity")), 0.f);
  
  screenMinOpacity = 0.f;
  screenOpacityValueRange = 0.1f;
}

// Called when the game starts or when spawned
void APauseScreen::BeginPlay()
{
	Super::BeginPlay();
	
  calculateRoute();

  SetActorTickEnabled(false);
}

// Called every frame
void APauseScreen::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

  if (passedRoute < routeLength) moveScreen();
  else stopMoveScreen();
}


void APauseScreen::OnFingerPressedHandler(ETouchIndex::Type FingerIndex, 
  UPrimitiveComponent* TouchedComponent)
{
  onClicked.Broadcast();
}


void APauseScreen::calculateRoute()
{
  AScenePoint* forwardPosition = nullptr;
  AScenePoint* backwardPosition = nullptr;

  for (TActorIterator<AScenePoint> screenPointItr(GetWorld()); screenPointItr; ++screenPointItr)
  {
    if (screenPointItr->GetActorLabel() == FString("PauseScreenBackwardPosition"))
      backwardPosition = *screenPointItr;

    else if (screenPointItr->GetActorLabel() == FString("PauseScreenForwardPosition"))
      forwardPosition = *screenPointItr;
  }

  FVector forwardLocation = forwardPosition->GetActorLocation();
  FVector backwardLocation = backwardPosition->GetActorLocation();

  screenVelocity = (forwardLocation - backwardLocation) / screenLinearSpeed;

  routeLength = FPlatformMath::RoundToInt(screenLinearSpeed);

  isMovingForward = false;
  
  passedRoute = 0;
}


void APauseScreen::moveScreen()
{
  FVector location = GetActorLocation();
  FVector diffential;

  if (isMovingForward) 
    diffential = screenVelocity;
  else
    diffential = -screenVelocity;
  
  this->SetActorRelativeLocation(location + diffential);

  passedRoute++;
}


void APauseScreen::stopMoveScreen()
{
  passedRoute = 0;
  isMovingForward = false;
  SetActorTickEnabled(false);
}


void APauseScreen::moveScreenForward()
{
  isMovingForward = true;
  SetActorTickEnabled(true);
}


void APauseScreen::moveScreenBackward()
{
  isMovingForward = false;
  SetActorTickEnabled(true);
}


//void APauseScreen::activateScreen()
//{
//  SetActorTickEnabled(true);
//
//}