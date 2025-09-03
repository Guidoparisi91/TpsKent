// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TpsKent2025 : ModuleRules
{
	public TpsKent2025(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TpsKent2025",
			"TpsKent2025/Variant_Platforming",
			"TpsKent2025/Variant_Platforming/Animation",
			"TpsKent2025/Variant_Combat",
			"TpsKent2025/Variant_Combat/AI",
			"TpsKent2025/Variant_Combat/Animation",
			"TpsKent2025/Variant_Combat/Gameplay",
			"TpsKent2025/Variant_Combat/Interfaces",
			"TpsKent2025/Variant_Combat/UI",
			"TpsKent2025/Variant_SideScrolling",
			"TpsKent2025/Variant_SideScrolling/AI",
			"TpsKent2025/Variant_SideScrolling/Gameplay",
			"TpsKent2025/Variant_SideScrolling/Interfaces",
			"TpsKent2025/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
