// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FRActor.h"
#include "PlayerPawn.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerPawnBeginMoving);



/**
 * 
 */
UCLASS()
class FR_API APlayerPawn : public AFRActor
{
	GENERATED_BODY()
	
    /** Dummy root component */
    UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  class USceneComponent* DummyRoot;

public:
    APlayerPawn();

    UStaticMeshComponent* BlockMesh;
    TArray<UMaterial*>* materials;

    void init(TArray<UMaterial*>& materials, int32 initialColor);
    void setColor(int32 color);

    int32 color;

    int32 gridX;
    int32 gridY;

    /*------------------------------------------------*/

    FPlayerPawnBeginMoving onMovingBegin;

    void invokeBeginMovingEvent();
	
};
