#pragma once

#include "IInputDevice.h"

#include "AllowWindowsPlatformTypes.h"
#include "spwmacro.h"  /* Common macros used by SpaceWare functions. */
#include "si.h"        /* Required for any SpaceWare support within an app.*/
#include "siapp.h"     /* Required for siapp.lib symbols */
#include "virtualkeys.hpp" 
#include "HideWindowsPlatformTypes.h"

class FGeneric3DMouseInputDevice : public IInputDevice
{
public:
	FGeneric3DMouseInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
	~FGeneric3DMouseInputDevice();

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

	bool startupDevice();


	


private:

	void createSPWindow(int atx, int aty, int hi, int wid, TCHAR *string);
	//LRESULT WINAPI HandleNTEvent(HWND hWnd, unsigned msg, WPARAM wParam, LPARAM lParam);
	/* Message handler */
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};

