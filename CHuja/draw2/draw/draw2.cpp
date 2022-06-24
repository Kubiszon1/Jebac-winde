// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;

// buttons
HWND hwndButton;

// sent data
int col = 0;
int pietro = 1;
int ludzik = 0;
std::vector<Point> data;
RECT drawArea1 = { 0, 0, 150, 200 };
RECT drawArea2 = { 50, 400, 650, 422 };
RectF ellipseRect(70.0f, 330.0f, 20.0f, 20.0f);
RectF ellipseRect2(70.0f, 535.0f, 20.0f, 20.0f);
RectF ellipseRect3(70.0f, 535.0f, 20.0f, 20.0f);

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc, int pietro, int ludzik)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25 * col, 0, 255));

	//	for (int i = 1; i < 100; i++)
	//		graphics.DrawLine(&pen2, data[i - 1].X, data[i - 1].Y, data[i].X, data[i].Y);

	graphics.DrawRectangle(&pen2, 497, 37, 146, 600);//kanal

	switch (pietro)
	{
	case 1:graphics.DrawRectangle(&pen2, 500, 450, 140, 180);//1 pietro winda
		break;
	case 2:graphics.DrawRectangle(&pen2, 500, 335, 140, 180);//2 pietro winda
		break;
	case 3:graphics.DrawRectangle(&pen2, 500, 245, 140, 180);//3 pietro winda
		break;
	case 4:graphics.DrawRectangle(&pen2, 500, 130, 140, 180);//4 pietro winda
		break;
	case 5:graphics.DrawRectangle(&pen2, 500, 40, 140, 180); //5 pietro winda
		break;
	default:
		break;
	}
	/*
	graphics.DrawRectangle(&pen2, 500, 40, 140, 180); //5 pietro winda
	graphics.DrawRectangle(&pen2, 500, 245, 140, 180);//3 pietro winda
	graphics.DrawRectangle(&pen2, 500, 450, 140, 180);//1 pietro winda

	graphics.DrawRectangle(&pen2, 500, 130, 140, 180);//4 pietro winda
	graphics.DrawRectangle(&pen2, 500, 335, 140, 180);//2 pietro winda
	*/
	graphics.DrawLine(&pen2, 10, 220, 497, 220); //5 pietro podloga
	graphics.DrawLine(&pen2, 10, 425, 497, 425); //3 pietro podloga
	graphics.DrawLine(&pen2, 10, 630, 497, 630); //1 pietro podloga

	graphics.DrawLine(&pen2, 643, 310, 1130, 310); //4 pietro podloga
	graphics.DrawLine(&pen2, 643, 515, 1130, 515); //2 pietro podloga

	switch (ludzik)
	{
	case 1:graphics.DrawLine(&pen2, 80, 555, 80, 601); // cz³on
		   graphics.DrawLine(&pen2, 80, 599, 90, 629); //prawa noga
		   graphics.DrawLine(&pen2, 80, 599, 70, 629); //lewa noga
		   graphics.DrawLine(&pen2, 80, 555, 90, 601); // prawa reka
		   graphics.DrawLine(&pen2, 80, 555, 70, 601); //lewa reka
		   graphics.DrawEllipse(&pen2, ellipseRect2);  //³epek 
		   break;

	case 2:graphics.DrawLine(&pen2, 80, 355, 1130, 385); // cz³on
		   graphics.DrawLine(&pen2, 80, 599, 1140, 414); //prawa noga
		   graphics.DrawLine(&pen2, 80, 599, 1120, 414); //lewa noga
		   graphics.DrawLine(&pen2, 80, 555, 1140, 385); // prawa reka
		   graphics.DrawLine(&pen2, 80, 555, 1120, 385); //lewa reka
		   graphics.DrawEllipse(&pen2, ellipseRect3);  //³epek 
		   break;

	case 3:graphics.DrawLine(&pen2, 80, 350, 80, 396); // cz³on
		   graphics.DrawLine(&pen2, 80, 394, 90, 424); //prawa noga
		   graphics.DrawLine(&pen2, 80, 394, 70, 424); //lewa noga
		   graphics.DrawLine(&pen2, 80, 350, 90, 396); // prawa reka
		   graphics.DrawLine(&pen2, 80, 350, 70, 396); //lewa reka
		   graphics.DrawEllipse(&pen2, ellipseRect);  //³epek 
		   break;
	}
}

void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc, pietro, ludzik);
	EndPaint(hWnd, &ps);
}

void inputData()
{
	data.push_back(Point(0, 0));
	for (int i = 1; i < 100; i++) {
		data.push_back(Point(2 * i + 1, 200 * rand() / RAND_MAX));
	}
}

int OnCreate(HWND window)
{
	inputData();
	return 0;
}


// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle                                                       

/*	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Draw"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		300, 60,                                  // the left and top co-ordinates
		80, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need
*/
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("DrawAll"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 0,                                  // the left and top co-ordinates
		80, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON99,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	//############# 1 pietro  #############
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		10, 600,                                  // the left and top co-ordinates
		29, 29,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 570,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON2,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 540,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON3,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 510,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON4,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("W"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 480,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON5,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("+1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		10, 450,                                  // the left and top co-ordinates
		29, 29,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON27,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	//################# 3 pietro  ############################

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		10, 395,                                  // the left and top co-ordinates
		29, 29,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON6,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 365,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON7,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 335,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON8,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 305,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON9,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("W"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 275,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON10,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("+1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 245,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON26,
		hInstance,
		NULL);
	//################# 5 pietro  ############################

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		10, 190,                                  // the left and top co-ordinates
		29, 29,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON11,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 160,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON12,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 130,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON13,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 100,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON14,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("W"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 70,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON15,
		hInstance,
		NULL);

	//################# 2 pietro  ############################

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1100, 485,                                  // the left and top co-ordinates
		29, 29,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON16,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1100, 455,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON17,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1100, 425,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON18,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1100, 395,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON19,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("W"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1100, 365,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON20,
		hInstance,
		NULL);

	//################# 4 pietro  ############################

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1100, 280,                                  // the left and top co-ordinates
		29, 29,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON21,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1100, 250,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON22,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1100, 220,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON23,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1100, 190,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON24,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("W"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1100, 160,
		29, 29,
		hWnd,
		(HMENU)ID_BUTTON25,
		hInstance,
		NULL);
	// create button and store the handle                                                       

	/*hwndButton = CreateWindow(TEXT("button"), TEXT("Timer ON"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		300, 155, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer OFF"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		300, 200, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL);*/

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			//########################
		case ID_BUTTON1:
			if (pietro == 1)
				pietro = 2;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON2:
			if (pietro == 1)
				pietro = 3;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON3:
			if (pietro == 1)
				pietro = 4;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON4:
			if (pietro == 1)
				pietro = 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON5:
			pietro = 1;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;


		case ID_BUTTON6:
			if (pietro == 3)
				pietro = 1;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON7:
			if (pietro == 3)
				pietro = 2;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON8:
			if (pietro == 3)
				pietro = 4;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON9:
			if (pietro == 3)
				pietro = 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON10:
			pietro = 3;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;


		case ID_BUTTON11:
			if (pietro == 5)
				pietro = 1;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON12:
			if (pietro == 5)
				pietro = 2;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON13:
			if (pietro == 5)
				pietro = 3;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON14:
			if (pietro == 5)
				pietro = 4;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON15:
			pietro = 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;



		case ID_BUTTON16:
			if (pietro == 2)
				pietro = 1;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON17:
			if (pietro == 2)
				pietro = 3;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON18:
			if (pietro == 2)
				pietro = 4;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON19:
			if (pietro == 2)
				pietro = 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON20:
			pietro = 2;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;

		case ID_BUTTON21:
			if (pietro == 4)
				pietro = 1;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON22:
			if (pietro == 4)
				pietro = 2;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON23:
			if (pietro == 4)
				pietro = 3;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON24:
			if (pietro == 4)
				pietro = 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON25:
			pietro = 4;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
			//##########################
		case ID_BUTTON26:
			ludzik = 3;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON27:
			ludzik = 1;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_RBUTTON1:
			SetTimer(hWnd, TMR_1, 25, 0);
			break;
		case ID_RBUTTON2:
			KillTimer(hWnd, TMR_1);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea2);
			value++;
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}