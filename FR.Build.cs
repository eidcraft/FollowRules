// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FR : ModuleRules
{
	public FR(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
    PublicDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities" });
  }
}
