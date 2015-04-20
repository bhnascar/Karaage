#include "ConnexionPluginPrivatePCH.h"
#include "Generic3DMouseInputDevice.h"
#include "IInputInterface.h"



static HDC          hdc;         /* Handle to Device Context used to draw on screen */
static HWND         hWndMain;    /* Handle to Main Window */
static SiHdl        devHdl;      /* Handle to 3D Mouse Device */
static TCHAR devicename[100] = _T("");
static int          movement = 0;

FGeneric3DMouseInputDevice::FGeneric3DMouseInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
MessageHandler(InMessageHandler)
{

	startupDevice();

}


FGeneric3DMouseInputDevice::~FGeneric3DMouseInputDevice()
{
	// Close 3DMouse device

}

bool FGeneric3DMouseInputDevice::startupDevice(){


	int  hsize, vsize;   /* size of window to be created,for each Dimension */

	/* Set Window Size */
	hsize = 280;
	vsize = 215;

	/* create our apps window */
	createSPWindow(0, 0, hsize, vsize, _T("3DxTest32"));

	InvalidateRect(hWndMain, NULL, false);

	int res;                             /* result of SiOpen, to be returned  */
	SiOpenData oData;                    /* OS Independent data to open ball  */
	HINSTANCE hInst = NULL;
	TCHAR *string = _T("ConnexionPlugin");

	/*init the SpaceWare input library */
	if (SiInitialize() == SPW_DLL_LOAD_ERROR)
	{
		MessageBox(hWndMain, _T("Error: Could not load SiAppDll dll files"),
			NULL, MB_ICONEXCLAMATION);
	}

	SiOpenWinInit(&oData, hWndMain);    /* init Win. platform specific data  */
	SiSetUiMode(devHdl, SI_UI_NO_CONTROLS); /* Config SoftButton Win Display */

	/* open data, which will check for device type and return the device handle
	to be used by this function */
	if ((devHdl = SiOpen("ConnexionPlugin", SI_ANY_DEVICE, SI_NO_MASK, SI_EVENT, &oData)) == NULL)
	{
#if 0
		SPWchar err[100];
		extern enum SpwRetVal SpwErrorVal;
		_stprintf(err, _T("SiOpen error: %d\n"), SpwErrorVal);
		MessageBox(NULL, err, _T("3DxTest: SiOpen Error"), MB_ICONERROR);
#endif

		SiTerminate();  /* called to shut down the SpaceWare input library */
		res = 0;        /* could not open device */
		UE_LOG(LogTemp, Error, TEXT("INIT FALALLALALALALALAALALAALALL"));
		return false;

	}
	else
	{
		//SiGrabDevice(devHdl, SPW_TRUE);
		SiDeviceName devName;
		SiGetDeviceName(devHdl, &devName);
		_stprintf(devicename, _T("%S"), devName.name);
		res = 1;        /* opened device succesfully */
		UE_LOG(LogTemp, Error, TEXT("INITSUCCESSSL"));
		return true;

	}


}










void FGeneric3DMouseInputDevice::Tick(float DeltaTime)
{
	
}


float filter(float value) {
	return (fabs(value) < 0.0001) ? 0 : value;
}

void FGeneric3DMouseInputDevice::SendControllerEvents()
{
	MSG            msg;      /* incoming message to be evaluated */
	BOOL           handled = SPW_FALSE;  /* is message handled yet */
	SiSpwEvent     Event;    /* SpaceWare Event */
	SiGetEventData EData;    /* SpaceWare Event Data */

	UINT_PTR timerID = SetTimer(NULL, NULL, 15, NULL);
	if (GetMessage(&msg, NULL, 0, 0)){
		KillTimer(NULL, timerID);
		/* init Window platform specific data for a call to SiGetEvent */
		SiGetEventWinInit(&EData, msg.message, msg.wParam, msg.lParam);

		/* check whether msg was a 3D mouse event and process it */
		if (SiGetEvent(devHdl, SI_AVERAGE_EVENTS, &EData, &Event) == SI_IS_EVENT)
		{
			if (Event.type == SI_MOTION_EVENT)
			{
				MessageHandler->OnControllerAnalog(EControllerButtons::LeftAnalogX, 0, filter(Event.u.spwData.mData[SI_TX]/ 1000.f));
				MessageHandler->OnControllerAnalog(EControllerButtons::LeftAnalogY, 0, filter(Event.u.spwData.mData[SI_TZ] / 1000.f));
				MessageHandler->OnControllerAnalog(EControllerButtons::RightAnalogX, 0, filter(-Event.u.spwData.mData[SI_RY] / 1000.f));
				MessageHandler->OnControllerAnalog(EControllerButtons::RightAnalogY, 0, filter(Event.u.spwData.mData[SI_RX] / 1000.f));
				MessageHandler->OnControllerAnalog(EControllerButtons::RightTriggerAnalog, 0, filter(Event.u.spwData.mData[SI_TY] / 1000.f));
				UE_LOG(LogTemp, Warning, TEXT("MOTION EVENT: ROTATION Y: %f   ROTATION X: %f \n"), -Event.u.spwData.mData[SI_RY], Event.u.spwData.mData[SI_RX]);

			
			}
			else if (Event.type == SI_ZERO_EVENT)
			{
				MessageHandler->OnControllerAnalog(EControllerButtons::LeftAnalogX, 0, 0);
				MessageHandler->OnControllerAnalog(EControllerButtons::LeftAnalogY, 0, 0);
				MessageHandler->OnControllerAnalog(EControllerButtons::RightAnalogX, 0, 0);
				MessageHandler->OnControllerAnalog(EControllerButtons::RightAnalogY, 0, 0);
				MessageHandler->OnControllerAnalog(EControllerButtons::RightTriggerAnalog, 0, 0.0);
				UE_LOG(LogTemp, Warning, TEXT("zero event\n"));
				//MessageHandler->OnKeyUp('E', 'E', false);
			}
			else if (Event.type == SI_BUTTON_PRESS_EVENT)
			{
				
				UE_LOG(LogTemp, Warning, TEXT("BUTTON PRESS EVENT \n"));
			}
			else if (Event.type == SI_BUTTON_RELEASE_EVENT)
			{

				UE_LOG(LogTemp, Warning, TEXT("SI BUTTON RELEASE \n"));
			}
			else if (Event.type == SI_DEVICE_CHANGE_EVENT)
			{
				//UE_LOG(LogTemp, Warning, TEXT("SI DEVICE CHANGE EVENT \n"));
			}

			handled = SPW_TRUE;
		}

		/* not a 3D mouse event, let windows handle it */
		if (handled == SPW_FALSE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


	}

	// Send dummy value
	
}


void FGeneric3DMouseInputDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}


bool FGeneric3DMouseInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	// Nothing necessary to do
	return false;
}


void FGeneric3DMouseInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	// Nothing necessary to do
}


void FGeneric3DMouseInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values)
{
	// Nothing necessary to do
}


LRESULT WINAPI HandleNTEvent(HWND hWnd, unsigned msg, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;           /* used to paint the client area of a window */
	LONG addr;                /* address of our window */

	addr = GetClassLong(hWnd, 0);  /* get address */

	switch (msg)
	{
	case WM_ACTIVATEAPP:
		hdc = GetDC(hWnd);
		/* print buffers */
		TextOut(hdc, 0, 20, devicename, (int)_tcslen(devicename));
		TextOut(hdc, 15, 100, _T("TX: 0"), 5);
		TextOut(hdc, 15, 120, _T("TY: 0"), 5);
		TextOut(hdc, 15, 140, _T("TZ: 0"), 5);
		TextOut(hdc, 15, 160, _T("RX: 0"), 5);
		TextOut(hdc, 15, 180, _T("RY: 0"), 5);
		TextOut(hdc, 15, 200, _T("RZ: 0"), 5);
		TextOut(hdc, 15, 220, _T(" P: 0"), 5);

		/*release our window handle */
		ReleaseDC(hWnd, hdc);
	case WM_KEYDOWN:
	case WM_KEYUP:
		/* user hit a key to close program */
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWndMain, WM_CLOSE, 0, 0l);
		}
		break;

	case WM_PAINT:
		/* time to paint the window */
		if (addr)
		{
			hdc = BeginPaint(hWndMain, &ps);
			EndPaint(hWndMain, &ps);
		}

		break;

	case WM_CLOSE:
		/* cleanup the object info created */

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return (0);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);

}

void FGeneric3DMouseInputDevice::createSPWindow(int atx, int aty, int hi, int wid, TCHAR *string)
{
	WNDCLASS  wndclass;     /* our own instance of the window class */
	HINSTANCE hInst;        /* handle to our instance */

	hInst = NULL;             /* init handle */

	/* Register display window class */
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = (WNDPROC)HandleNTEvent;
	wndclass.cbClsExtra = 8;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInst;
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = _T("ConnexionPlugin");

	RegisterClass(&wndclass);

	/* create the window */
	hWndMain = CreateWindow(_T("ConnexionPlugin"),           /*Window class name*/
		string,              /*Window caption*/
		WS_OVERLAPPEDWINDOW, /*Window Style*/
		atx, aty, wid, hi,
		NULL,	               /*parent window handle*/
		NULL,                /*window menu handle*/
		hInst,		         /*program instance handle*/
		NULL);               /*creation parameters*/

	/* display the window */
	ShowWindow(hWndMain, SW_SHOW);

	/* get handle of our window to draw on */
	hdc = GetDC(hWndMain);

	/* print buffers */
	TextOut(hdc, 0, 20, devicename, (int)_tcslen(devicename));
	TextOut(hdc, 15, 100, _T("TX: 0"), 5);
	TextOut(hdc, 15, 120, _T("TY: 0"), 5);
	TextOut(hdc, 15, 140, _T("TZ: 0"), 5);
	TextOut(hdc, 15, 160, _T("RX: 0"), 5);
	TextOut(hdc, 15, 180, _T("RY: 0"), 5);
	TextOut(hdc, 15, 200, _T("RZ: 0"), 5);
	TextOut(hdc, 15, 220, _T(" P: 0"), 5);

	/*release our window handle */
	ReleaseDC(hWndMain, hdc);

	UpdateWindow(hWndMain);
}
