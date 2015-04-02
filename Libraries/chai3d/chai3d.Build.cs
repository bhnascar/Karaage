// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class chai3d : ModuleRules
{
    public chai3d(TargetInfo Target)
	{
		Type = ModuleType.External;

		if ((Target.Platform == UnrealTargetPlatform.Win64) ||
			(Target.Platform == UnrealTargetPlatform.Win32))
		{

            string DirectShowLibPath = UEBuildConfiguration.UEThirdPartySourceDirectory
                + "chai3d/Libraries/" + ((Target.Platform == UnrealTargetPlatform.Win32) ? "Win32" : "Win64") + "/";

			PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/Includes/");
            PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/External/Eigen/");
            PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/External/giflib/include/");
            PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/External/glew/include/");
            PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/External/lib3ds/include/");
            PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/External/libjpeg/include/");
            PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/External/libpng/include/");
            PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/External/openal/include/");
            PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "chai3d/External/theoraplayer/include/");

            PublicLibraryPaths.Add( DirectShowLibPath );

			string LibraryName = "chai3d";
			if (Target.Platform == UnrealTargetPlatform.Win64)
			{
				LibraryName += ".x64";
			}
            else if (Target.Platform == UnrealTargetPlatform.Win32)
            {
                LibraryName += ".x86";
            }
			LibraryName += ".lib";
			PublicAdditionalLibraries.Add(LibraryName);
		}
	}
}

