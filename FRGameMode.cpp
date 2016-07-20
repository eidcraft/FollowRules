// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "FR.h"
#include "FRGameMode.h"
#include "FRPlayerController.h"

AFRGameMode::AFRGameMode()
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = AFRPlayerController::StaticClass();
}
