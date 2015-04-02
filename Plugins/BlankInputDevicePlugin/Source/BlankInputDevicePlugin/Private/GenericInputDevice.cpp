// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BlankInputDevicePluginPrivatePCH.h"
#include "GenericInputDevice.h"
#include "IInputInterface.h"


FGenericInputDevice::FGenericInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
MessageHandler(InMessageHandler)
{
	// Initiate your device here
}


FGenericInputDevice::~FGenericInputDevice()
{
	// Close your device here
}


void FGenericInputDevice::Tick(float DeltaTime)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}


void FGenericInputDevice::SendControllerEvents()
{
	// Poll your device here and fire off events related to its current state

	// Example: Sending a dummy value
	UE_LOG(LogTemp, Warning, TEXT("Sending dummy analog controller event!"));
	MessageHandler->OnControllerAnalog(EControllerButtons::LeftTriggerAnalog, 0, 0.5f);
}


void FGenericInputDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}


bool FGenericInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
	return false;
}


void FGenericInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}


void FGenericInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}
