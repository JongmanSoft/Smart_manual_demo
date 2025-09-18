// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class smart_manual : ModuleRules
{
	public smart_manual(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "LevelSequence"});
	}
}
