#pragma once

#include "IInputDevice.h"

#include "AllowWindowsPlatformTypes.h"
#include "chai3d.h"
#include "HideWindowsPlatformTypes.h"

#define MAX_CONTROLLER_BUTTONS 4

class FGenericHapticInputDevice : public IInputDevice
{
public:
	FGenericHapticInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
	~FGenericHapticInputDevice();

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
	/* Button states */
	bool CachedButtonStates[MAX_CONTROLLER_BUTTONS];

	/* A haptic device handler */
	chai3d::cHapticDeviceHandler *HapticDeviceHandler;

	/* A pointer to the current haptic device */
	chai3d::cGenericHapticDevicePtr HapticDevice;

	/* Message handler */
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};

