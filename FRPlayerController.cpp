// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "FR.h"
#include "FRPlayerController.h"

AFRPlayerController::AFRPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
