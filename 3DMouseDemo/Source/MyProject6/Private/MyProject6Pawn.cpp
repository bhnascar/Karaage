// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject6.h"
#include "MyProject6Pawn.h"

// 3DConnexion-related includes
#include "AllowWindowsPlatformTypes.h"
#include "spwmacro.h"  /* Common macros used by SpaceWare functions. */
#include "si.h"        /* Required for any SpaceWare support within an app.*/
#include "siapp.h"     /* Required for siapp.lib symbols */
#include "virtualkeys.hpp" 
#include "HideWindowsPlatformTypes.h"

#pragma comment (lib, "siapp.lib")

///////// SpaceMouse globals ////////////
HDC          hdc;         /* Handle to Device Context used to draw on screen */
HWND         hWndMain;    /* Handle to Main Window */
SiHdl        devHdl;      /* Handle to 3D Mouse Device */
TCHAR devicename[100] = _T("");

/*--------------------------------------------------------------------------
* Function: HandleNTEvent
*
* Description:  This is a std. Win32 function to handle various window events
*
*
*
* Args: HWND hWnd                    // handle to window
*       unsigned msg                 // message to process
*       WPARAM wParam                // 32 bit msg parameter
*       LPARAM lParam                // 32 bit msg parameter
*
* Return Value:
*    int  msg.wparam                 // program done
*
*--------------------------------------------------------------------------*/
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

void SbMotionEvent(SiSpwEvent *pEvent)
{
	TCHAR buff0[30];                            /* text buffer for TX */
	TCHAR buff1[30];                            /* text buffer for TY */
	TCHAR buff2[30];                            /* text buffer for TZ */
	TCHAR buff3[30];                            /* text buffer for RX */
	TCHAR buff4[30];                            /* text buffer for RY */
	TCHAR buff5[30];                            /* text buffer for RZ */
	TCHAR buff6[30];                            /* text buffer for Period */

	int len0, len1, len2, len3, len4, len5, len6;	   /* length of each buffer */

	/* put the actual ball data into the buffers */
	len0 = _stprintf(buff0, _T("TX: %d         "), pEvent->u.spwData.mData[SI_TX]);
	len1 = _stprintf(buff1, _T("TY: %d         "), pEvent->u.spwData.mData[SI_TY]);
	len2 = _stprintf(buff2, _T("TZ: %d         "), pEvent->u.spwData.mData[SI_TZ]);
	len3 = _stprintf(buff3, _T("RX: %d         "), pEvent->u.spwData.mData[SI_RX]);
	len4 = _stprintf(buff4, _T("RY: %d         "), pEvent->u.spwData.mData[SI_RY]);
	len5 = _stprintf(buff5, _T("RZ: %d         "), pEvent->u.spwData.mData[SI_RZ]);
	len6 = _stprintf(buff6, _T(" P: %d         "), pEvent->u.spwData.period);

	/* get handle of our window to draw on */
	hdc = GetDC(hWndMain);

	/* print buffers */
	TCHAR *buf = _T("Motion Event              ");
	TextOut(hdc, 0, 0, buf, (int)_tcslen(buf));
	TextOut(hdc, 0, 20, devicename, (int)_tcslen(devicename));
	TextOut(hdc, 15, 100, buff0, len0);
	TextOut(hdc, 15, 120, buff1, len1);
	TextOut(hdc, 15, 140, buff2, len2);
	TextOut(hdc, 15, 160, buff3, len3);
	TextOut(hdc, 15, 180, buff4, len4);
	TextOut(hdc, 15, 200, buff5, len5);
	TextOut(hdc, 15, 220, buff6, len6);

	// Also dump to stdout for a searchable log
	printf("%d %d %d %d %d %d\n",
		pEvent->u.spwData.mData[SI_TX],
		pEvent->u.spwData.mData[SI_TY],
		pEvent->u.spwData.mData[SI_TZ],
		pEvent->u.spwData.mData[SI_RX],
		pEvent->u.spwData.mData[SI_RY],
		pEvent->u.spwData.mData[SI_RZ]);

	/*release our window handle */
	ReleaseDC(hWndMain, hdc);
}

void SbZeroEvent()
{
	/* get handle of our window to draw on */
	hdc = GetDC(hWndMain);

	/* print null data */
	TextOut(hdc, 0, 0, _T("Zero Event                  "), 28);
	TextOut(hdc, 0, 20, devicename, (int)_tcslen(devicename));
	TextOut(hdc, 15, 100, _T("TX: 0          "), 15);
	TextOut(hdc, 15, 120, _T("TY: 0          "), 15);
	TextOut(hdc, 15, 140, _T("TZ: 0          "), 15);
	TextOut(hdc, 15, 160, _T("RX: 0          "), 15);
	TextOut(hdc, 15, 180, _T("RY: 0          "), 15);
	TextOut(hdc, 15, 200, _T("RZ: 0          "), 15);
	TextOut(hdc, 15, 220, _T(" P: 0          "), 15);

	/*release our window handle */
	ReleaseDC(hWndMain, hdc);
}


/*--------------------------------------------------------------------------
* Function: CreateSPWindow
*
* Description:  This creates the window for our app
*
*
*
* Args:  int  atx        // horiz. start point to put window
*        int  aty        // vert.  start point to put window
*        int  hi         // hight of window
*        int  wid        // width of window
*        char *string    // window caption
*
* Return Value:
*    NONE
*
*--------------------------------------------------------------------------*/
void CreateSPWindow(int atx, int aty, int hi, int wid, TCHAR *string)
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
	wndclass.lpszClassName = _T("MyProject6Pawn");

	RegisterClass(&wndclass);

	/* create the window */
	hWndMain = CreateWindow(_T("MyProject6Pawn"),           /*Window class name*/
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

} /* end of CreateWindow */


/*--------------------------------------------------------------------------
* Function: SbInit()
*
* Description:
*    This function initializes the 3D mouse and opens ball for use.
*
*
* Args: None
*
*
* Return Value:
*    int  res         result of SiOpen, =0 if Fail =1 if it Works
*
*--------------------------------------------------------------------------*/
int SbInit()
{
	int res;                             /* result of SiOpen, to be returned  */
	SiOpenData oData;                    /* OS Independent data to open ball  */
	HINSTANCE hInst = NULL;
	TCHAR *string = _T("MyProject6Pawn");

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
	if ((devHdl = SiOpen("MyProject6Pawn", SI_ANY_DEVICE, SI_NO_MASK, SI_EVENT, &oData)) == NULL)
	{
#if 0
		SPWchar err[100];
		extern enum SpwRetVal SpwErrorVal;
		_stprintf(err, _T("SiOpen error: %d\n"), SpwErrorVal);
		MessageBox(NULL, err, _T("3DxTest: SiOpen Error"), MB_ICONERROR);
#endif

		SiTerminate();  /* called to shut down the SpaceWare input library */
		res = 0;        /* could not open device */
		return res;
	}
	else
	{
		//SiGrabDevice(devHdl, SPW_TRUE);
		SiDeviceName devName;
		SiGetDeviceName(devHdl, &devName);
		_stprintf(devicename, _T("%S"), devName.name);
		res = 1;        /* opened device succesfully */
		return res;
	}
}


AMyProject6Pawn::AMyProject6Pawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Meshes/UFO.UFO"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	PlaneMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	RootComponent = PlaneMesh;

	// Create a spring arm component
	SpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm0"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f,0.f,60.f);
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 15.f;

	// Create camera component 
	Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera0"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	// Set handling parameters
	Acceleration = 50.f;
	TurnSpeed = 25.f;
	MaxSpeed = 2000.f;
	MinSpeed = 0.f;
	CurrentForwardSpeed = 0.f;

	/////////////////// Adding Our stuff ///////////////////////

	int  hsize, vsize;   /* size of window to be created,for each Dimension */

	/* Set Window Size */
	hsize = 280;
	vsize = 215;

	/* create our apps window */
	CreateSPWindow(0, 0, hsize, vsize, _T("3DxTest32"));

	/* update screen */
	BOOL blah = false;
	InvalidateRect(hWndMain, NULL, blah);

	/* Initialize 3D mouse */
	if (SbInit() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("3D MOUSE INIT SUCCEEDED \n\n\n\n\n\n"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("3D MOUSE INIT FAILED \n\n\n\n\n\n"));
	}
}

void AMyProject6Pawn::Tick(float DeltaSeconds)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f);

	// Move plan forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0,0,0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	// Rotate plane
	AddActorLocalRotation(DeltaRotation);
	/*
	MSG msg;

	tick_frequency++;
	if (tick_frequency == 20){
		tick_frequency = 0;
		GetMessage(&msg, NULL, 0, 0);

	}
	*/
	MSG            msg;      /* incoming message to be evaluated */
	BOOL           handled = SPW_FALSE;  /* is message handled yet */
	SiSpwEvent     Event;    /* SpaceWare Event */
	SiGetEventData EData;    /* SpaceWare Event Data */

	UINT_PTR timerID = SetTimer(NULL, NULL, 15, NULL);
	if (GetMessage(&msg, NULL,0,0)){
		KillTimer(NULL, timerID);
	//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		/* init Window platform specific data for a call to SiGetEvent */
		SiGetEventWinInit(&EData, msg.message, msg.wParam, msg.lParam);

		/* check whether msg was a 3D mouse event and process it */
	   if (SiGetEvent(devHdl, SI_AVERAGE_EVENTS, &EData, &Event) == SI_IS_EVENT)
		{
			if (Event.type == SI_MOTION_EVENT)
			{
				SbMotionEvent(&Event);
				ThrustInput(Event.u.spwData.mData[SI_TZ]);
				MoveUpInput(-Event.u.spwData.mData[SI_RX]/100);
				MoveRightInput(-Event.u.spwData.mData[SI_RY]/100);
				//UE_LOG(LogTemp, Warning, TEXT("3SIMOTIONDED \n"));
			}
			else if (Event.type == SI_ZERO_EVENT)
			{
				SbZeroEvent();
				CurrentForwardSpeed = 0.f;
				//UE_LOG(LogTemp, Warning, TEXT("SIZEZERO\n"));
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
				UE_LOG(LogTemp, Warning, TEXT("SI DEVICE CHANGE EVENT \n"));
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

	//handled = SPW_FALSE;     /* init handled */

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void AMyProject6Pawn::ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Set velocity to zero upon collision
	CurrentForwardSpeed = 0.f;
}


void AMyProject6Pawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	// Bind our control axis' to callback functions
	InputComponent->BindAxis("Thrust", this, &AMyProject6Pawn::ThrustInput);
	InputComponent->BindAxis("MoveUp", this, &AMyProject6Pawn::MoveUpInput);
	InputComponent->BindAxis("MoveRight", this, &AMyProject6Pawn::MoveRightInput);
}

void AMyProject6Pawn::ThrustInput(float Val)
{
	
	// Is there no input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc = bHasInput ? (Val * Acceleration) : (-0.5f * Acceleration);
	// Calculate new speed
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void AMyProject6Pawn::MoveUpInput(float Val)
{
	UE_LOG(LogTemp, Warning, TEXT("%d\n"), Val);
	// Target pitch speed is based in input
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f);

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);

	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void AMyProject6Pawn::MoveRightInput(float Val)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Is there any left/right input?
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value
	float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);

	// Smoothly interpolate roll speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}