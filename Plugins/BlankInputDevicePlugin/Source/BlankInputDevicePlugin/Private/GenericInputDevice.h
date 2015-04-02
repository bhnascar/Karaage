// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IInputDevice.h"

class FGenericInputDevice : public IInputDevice
{
public:
	FGenericInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
	~FGenericInputDevice();

	/** Tick the interface (e.g. check for new controllers) */
	virtual void Tick(float DeltaTime) override;

	/** Poll for controller state and send events if needed */
	virtual void SendControllerEvents() override;

	/** Set which MessageHandler will get the events from SendControllerEvents. */
	virtual void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;

	/** Exec handler to allow console commands to be passed through for debugging */
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	/** IForceFeedbackSystem pass through functions **/
	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override;

private:
	/* Message handler */
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};

