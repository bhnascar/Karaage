// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class connexion : ModuleRules
{
    public connexion(TargetInfo Target)
	{
		Type = ModuleType.External;

		if ((Target.Platform == UnrealTargetPlatform.Win64) ||
			(Target.Platform == UnrealTargetPlatform.Win32))
		{

            string DirectShowLibPath = UEBuildConfiguration.UEThirdPartySourceDirectory
                + "connexion/Lib/" + ((Target.Platform == UnrealTargetPlatform.Win32) ? "x86" : "x64") + "/";

			PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "connexion/Inc/");

            PublicLibraryPaths.Add( DirectShowLibPath );

            PublicAdditionalLibraries.Add("siapp.lib");
            PublicAdditionalLibraries.Add("spwmath.lib");
            PublicAdditionalLibraries.Add("spwmathD.lib");
            PublicAdditionalLibraries.Add("spwmathMT.lib");
            PublicAdditionalLibraries.Add("spwmathMTD.lib");
		}
	}
}

