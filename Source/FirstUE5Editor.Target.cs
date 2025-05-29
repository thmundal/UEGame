// Copyright 2025 Chaos games

using UnrealBuildTool;
using System.Collections.Generic;

public class FirstUE5EditorTarget : TargetRules
{
	public FirstUE5EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "FirstUE5" } );
	}
}
