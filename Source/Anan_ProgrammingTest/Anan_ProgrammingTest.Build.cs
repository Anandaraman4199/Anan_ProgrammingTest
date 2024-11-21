// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Anan_ProgrammingTest : ModuleRules
{
	public Anan_ProgrammingTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "GameplayAbilities", "GameplayTags" , "GameplayTasks" });
	}
}
