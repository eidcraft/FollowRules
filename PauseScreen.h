// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PauseScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseScreenClicked);

UCLASS()
class FR_API APauseScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APauseScreen();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  /*-------------------------------------------------*/	

  UPROPERTY()
    UStaticMeshComponent* meshComponent;
  UPROPERTY()
    UMaterialInstance* material;
  UPROPERTY()
    UMaterialInstanceDynamic* dynamicMaterial;

  float screenMinOpacity;
  float screenOpacityValueRange;

  /*-------------------------------------------------*/

  FOnPauseScreenClicked onClicked;

  UFUNCTION()
  void OnFingerPressedHandler(ETouchIndex::Type FingerIndex, 
    UPrimitiveComponent* TouchedComponent);

  /*--------------------------------------------------*/

  FVector screenVelocity;
  float screenLinearSpeed;

  bool isMovingForward;
  bool isMovingBackward;
  
  int32 routeLength;
  int32 passedRoute;

  void calculateRoute();

  void moveScreen();
  void stopMoveScreen();

  void moveScreenForward();
  void moveScreenBackward();
};
