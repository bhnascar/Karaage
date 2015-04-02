#include "Chai3dPluginPrivatePCH.h"
#include "GenericHapticInputDevice.h"
#include "IInputInterface.h"

#define CHAIVEC_TO_FVEC(vector) FVector(-vector.x(), vector.y(), vector.z())


FGenericHapticInputDevice::FGenericHapticInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
MessageHandler(InMessageHandler)
{
	// Create a haptic device handler
	HapticDeviceHandler = new chai3d::cHapticDeviceHandler();

	// Get a handle to the first haptic device
	HapticDeviceHandler->getDevice(HapticDevice, 0);

	// Open a connection to haptic device
	HapticDevice->open();

	// Calibrate device (if necessary)
	HapticDevice->calibrate();

	// Retrieve information about the current haptic device
	chai3d::cHapticDeviceInfo info = HapticDevice->getSpecifications();

	// If the device has a gripper, enable the gripper to simulate a user switch
	HapticDevice->setEnableGripperUserSwitch(true);
}


FGenericHapticInputDevice::~FGenericHapticInputDevice()
{
	// Close haptic device
	HapticDevice->close();
}


void FGenericHapticInputDevice::Tick(float DeltaTime)
{
	// Nothing necessary to do
}


void FGenericHapticInputDevice::SendControllerEvents()
{
	// Read haptic device position 
	chai3d::cVector3d position;
	HapticDevice->getPosition(position);

	// Maintain position
	chai3d::cVector3d force(0, 0, 0);
	HapticDevice->setForce(force);

	// Send button states
	for (int i = 0; i < MAX_CONTROLLER_BUTTONS; i++) {
		bool selected = false;
		HapticDevice->getUserSwitch(i, selected);
		if (selected && !CachedButtonStates[i]) {
			MessageHandler->OnKeyDown('1' + i, '1' + i, false);
		}
		else if (!selected && CachedButtonStates[i]) {
			MessageHandler->OnKeyUp('1' + i, '1' + i, false);
		}
		CachedButtonStates[i] = selected;
	}

	// Send position as tilt
	FVector tilt = CHAIVEC_TO_FVEC(position);
	MessageHandler->OnMotionDetected(tilt, FVector(), FVector(), FVector(), 0);
}


void FGenericHapticInputDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}


bool FGenericHapticInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	// Nothing necessary to do
	return false;
}


void FGenericHapticInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	// Nothing necessary to do
}


void FGenericHapticInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values)
{
	// Nothing necessary to do
}
