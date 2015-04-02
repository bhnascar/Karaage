// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Chai3dPluginPrivatePCH.h"
#include "GenericHapticInputDevice.h"

#define LOCTEXT_NAMESPACE "InputKeys"

namespace EHapticDeviceKeys
{
	/* Custom key events */
	static const FKey HapticDeviceX;
	static const FKey HapticDeviceY;
	static const FKey HapticDeviceZ;
	static const FKey HapticDeviceOrientation;
}

class FChai3dPlugin : public IChai3dPlugin
{
	/** IChai3dPlugin implementation */
	
	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FChai3dPlugin, Chai3dPlugin )


TSharedPtr<class IInputDevice> FChai3dPlugin::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	UE_LOG(LogTemp, Warning, TEXT("Created new input device!"));
	return MakeShareable(new FGenericHapticInputDevice(InMessageHandler));
}


void FChai3dPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	// Custom module-specific init can go here
	UE_LOG(LogTemp, Warning, TEXT("Chai3DPlugin initiated!"));
	IModularFeatures::Get().RegisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}


void FChai3dPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogTemp, Warning, TEXT("Chai3DPlugin shut down!"));
	IModularFeatures::Get().UnregisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}



