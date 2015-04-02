// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ConnexionPluginPrivatePCH.h"
#include "Generic3DMouseInputDevice.h"


class FConnexionPlugin : public IConnexionPlugin
{
	/** IConnexionPlugin implementation */
	
	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FConnexionPlugin, ConnexionPlugin )
//DEFINE_LOG_CATEGORY(LogConnexion)


TSharedPtr<class IInputDevice> FConnexionPlugin::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	return MakeShareable(new FGeneric3DMouseInputDevice(InMessageHandler));
}


void FConnexionPlugin::StartupModule()
{
	IModularFeatures::Get().RegisterModularFeature(FName(TEXT("InputDevice")), this);
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	// Custom module-specific init can go here
}


void FConnexionPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IModularFeatures::Get().UnregisterModularFeature(FName(TEXT("InputDevice")), this);
}



