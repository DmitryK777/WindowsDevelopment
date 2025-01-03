<<<<<<< HEAD
﻿#include <Windows.h>
#include "Resource.h"

#define IDC_EDIT_DISPLAY     999

#define IDC_BUTTON_0        1000
#define IDC_BUTTON_1        1001
#define IDC_BUTTON_2        1002
#define IDC_BUTTON_3        1003
#define IDC_BUTTON_4        1004
#define IDC_BUTTON_5        1005
#define IDC_BUTTON_6        1006
#define IDC_BUTTON_7        1007
#define IDC_BUTTON_8        1008
#define IDC_BUTTON_9        1009
#define IDC_BUTTON_POINT    1010

#define IDC_BUTTON_PLUS     1011
#define IDC_BUTTON_MINUS    1012
#define IDC_BUTTON_ASTER    1013 // "*"
#define IDC_BUTTON_SLASH    1014 // '/'

#define IDC_BUTTON_BSP      1015 // BackSpace
#define IDC_BUTTON_CLR      1016 // Clear
#define IDC_BUTTON_EQUAL    1017 // '='

=======
﻿#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <Float.h>
#include <cstdio>
>>>>>>> origin/ButtonsInClass

#include "Resource.h"
#include "Dimensions.h"
#include "Skins.h"
#include "Fonts.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc_VPD_311";

CONST CHAR* g_OPERATIONS[] = { "+", "-", "*", "/" };

<<<<<<< HEAD
CONST INT g_i_WINDOW_WIDTH = 250;
CONST INT g_i_WINDOW_HEIGHT = 362;

CONST INT g_i_EDIT_HEIGHT = 22;

CONST INT g_i_BUTTON_SIZE = 50; // Размер кнопки в пикселах
CONST INT g_i_INTERVAL = 10;     // Расстояние между кнопками

CONST INT g_i_START_X = 10;     // 
CONST INT g_i_START_Y = 10;     // 
CONST INT g_i_BUTTON_START_X = g_i_START_X;     // 
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_INTERVAL;     // 
=======
>>>>>>> origin/ButtonsInClass

CONST INT g_i_EDIT_WIDTH = (g_i_BUTTON_SIZE * 4)+(g_i_INTERVAL * 3);


INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT GetTitleBarHeight(HWND hwnd);

VOID SetSkin(HWND hwnd, CONST CHAR skin[]);
VOID SetSkinFromDLL(HWND hwnd, CONST CHAR skin[]);
VOID LoadFontFromDLL(HMODULE hFontModule, INT resourceID);
VOID LoadFontsFromDLL(HMODULE hFontsModule);
VOID SetFont(HWND hwnd, CONST CHAR font_name[]);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// 1) Регистация класса окна

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = CS_HREDRAW | CS_VREDRAW;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

<<<<<<< HEAD
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CALCULATOR));
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CALCULATOR));
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "Cursors\\starcraft-original\\Normal Select.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
=======
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CALC));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CALC));
	wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
>>>>>>> origin/ButtonsInClass
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = (WNDPROC)WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}


	// 2) Создание окна
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_start_x = (screen_width / 2) - (g_i_WINDOW_WIDTH / 2);
	INT window_start_y = (screen_height / 2) - (g_i_WINDOW_HEIGHT / 2);

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_start_x = (screen_width / 2) - (g_i_WINDOW_WIDTH / 2);
	INT window_start_y = (screen_height / 2) - (g_i_WINDOW_HEIGHT);


	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
<<<<<<< HEAD
		WS_OVERLAPPEDWINDOW,
		window_start_x, window_start_y,
		(g_i_WINDOW_WIDTH + 15), (g_i_WINDOW_HEIGHT + 10),
=======
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		window_start_x, window_start_y,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,
>>>>>>> origin/ButtonsInClass
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	// 3) Запуск цикла сообщений

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		//TranslateMessage(&msg);
		//DispatchMessage(&msg);
		IsDialogMessage(hwnd, &msg);
	}

	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static INT index = 0;
	static HMODULE hFontsModule = NULL;
	static INT font_index = 0;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			g_i_START_X, g_i_START_Y,
			g_i_SCREEN_WIDTH, g_i_SCREEN_HEIGHT,
			hwnd,
			(HMENU)999,
			GetModuleHandle(NULL),
			NULL
		);

		
		
		hFontsModule = LoadLibrary("Fonts.dll");
		LoadFontsFromDLL(hFontsModule);
		SetFont(hwnd, g_FONT_NAMES[font_index]);

		CHAR sz_digit[2]{};
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
<<<<<<< HEAD
				INT edit_width = g_i_WINDOW_WIDTH - (2 * g_i_INTERVAL);
				INT edit_height = ((g_i_WINDOW_HEIGHT - (7 * g_i_INTERVAL))/6)/2 ;
				HWND hEdit = CreateWindowEx
				(
					NULL, "Edit", "0",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_RIGHT,
					g_i_INTERVAL, g_i_INTERVAL,
					edit_width, edit_height,
					hwnd,
					(HMENU)IDC_EDIT_DISPLAY,
					GetModuleHandle(NULL),
					NULL
				);

				INT button_width = (g_i_WINDOW_WIDTH - (5 * g_i_INTERVAL)) / 4;
				INT button_height = (g_i_WINDOW_HEIGHT - (7 * g_i_INTERVAL)) / 6;

				HWND hButton_7 = CreateWindowEx
				(
					NULL, "Button", "7",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					g_i_INTERVAL, (2 * g_i_INTERVAL + edit_height),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_7,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_8 = CreateWindowEx
				(
					NULL, "Button", "8",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					(2 * g_i_INTERVAL + button_width), (2 * g_i_INTERVAL + edit_height),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_8,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_9 = CreateWindowEx
				(
					NULL, "Button", "9",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					((3 * g_i_INTERVAL) + (2 * button_width)), (2 * g_i_INTERVAL + edit_height),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_9,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_slash = CreateWindowEx
				(
					NULL, "Button", "/",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					((4 * g_i_INTERVAL) + (3 * button_width)), (2 * g_i_INTERVAL + edit_height),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_SLASH,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_4 = CreateWindowEx
				(
					NULL, "Button", "4",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					g_i_INTERVAL, (3 * g_i_INTERVAL + edit_height + button_height),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_4,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_5 = CreateWindowEx
				(
					NULL, "Button", "5",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					(2 * g_i_INTERVAL + button_width), (3 * g_i_INTERVAL + edit_height + button_height),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_5,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_6 = CreateWindowEx
				(
					NULL, "Button", "6",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					((3 * g_i_INTERVAL) + (2 * button_width)), (3 * g_i_INTERVAL + edit_height + button_height),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_6,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_aster = CreateWindowEx
				(
					NULL, "Button", "*",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					((4 * g_i_INTERVAL) + (3 * button_width)), (3 * g_i_INTERVAL + edit_height + button_height),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_ASTER,
					GetModuleHandle(NULL),
					NULL
				);


				HWND hButton_1 = CreateWindowEx
				(
					NULL, "Button", "1",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					g_i_INTERVAL, ((4 * g_i_INTERVAL) + edit_height + (2 * button_height)),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_1,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_2 = CreateWindowEx
				(
					NULL, "Button", "2",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					(2 * g_i_INTERVAL + button_width), ((4 * g_i_INTERVAL) + edit_height + (2 * button_height)),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_2,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_3 = CreateWindowEx
				(
					NULL, "Button", "3",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					(3 * g_i_INTERVAL + (2 * button_width)), ((4 * g_i_INTERVAL) + edit_height + (2 * button_height)),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_3,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_minus = CreateWindowEx
				(
					NULL, "Button", "-",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					(4 * g_i_INTERVAL + (3 * button_width)), ((4 * g_i_INTERVAL) + edit_height + (2 * button_height)),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_MINUS,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_point = CreateWindowEx
				(
					NULL, "Button", ",",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					g_i_INTERVAL, ((5 * g_i_INTERVAL) + edit_height + (3 * button_height)),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_POINT,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_0 = CreateWindowEx
				(
					NULL, "Button", "0",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					(2 * g_i_INTERVAL + button_width), ((5 * g_i_INTERVAL) + edit_height + (3 * button_height)),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_0,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_bsp = CreateWindowEx
				(
					NULL, "Button", "<-",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					((3 * g_i_INTERVAL) + (2 * button_width)), ((5 * g_i_INTERVAL) + edit_height + (3 * button_height)),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_BSP,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_plus = CreateWindowEx
				(
					NULL, "Button", "+",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					((4 * g_i_INTERVAL) + (3 * button_width)), ((5 * g_i_INTERVAL) + edit_height + (3 * button_height)),
					button_width, button_height,
					hwnd,
					(HMENU)IDC_BUTTON_PLUS,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_clr = CreateWindowEx
				(
					NULL, "Button", "CLEAR",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					g_i_INTERVAL, ((6 * g_i_INTERVAL) + edit_height + (4 * button_height)),
					(2 * button_width + g_i_INTERVAL), button_height,
					hwnd,
					(HMENU)IDC_BUTTON_CLR,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton_equal = CreateWindowEx
				(
					NULL, "Button", "=",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | BS_PUSHBUTTON,
					((3 * g_i_INTERVAL) + (2 * button_width)), ((6 * g_i_INTERVAL) + edit_height + (4 * button_height)),
					(2 * button_width + g_i_INTERVAL), button_height,
					hwnd,
					(HMENU)IDC_BUTTON_EQUAL,
=======
				sz_digit[0] = i + j + '1';
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_BITMAP,
					g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (2 - i / 3),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1 + i + j),
>>>>>>> origin/ButtonsInClass
					GetModuleHandle(NULL),
					NULL
				);
			}
		}

		// 1) Добавить стиль BS_BITMAP
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
			BUTTON_SHIFT_X(0), BUTTON_SHIFT_Y(3),
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		/*
		HWND hButton_0 = CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
			BUTTON_SHIFT_X(0), BUTTON_SHIFT_Y(3),
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		// 2) Загрузить картинку из файла
		HBITMAP bmpButton_0 = (HBITMAP)LoadImage(NULL, "ButtonsBMP\\square_blue\\button_0.bmp", IMAGE_BITMAP, g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE, LR_LOADFROMFILE);
		// 3) Установить картинку на кнопку
		SendMessage(hButton_0, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_0);
		*/

		

		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
			BUTTON_SHIFT_X(2), BUTTON_SHIFT_Y(3),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);

		for (int i = 0; i < 4; i++)
		{
			CreateWindowEx
			(
				NULL, "Button", g_OPERATIONS[i],
				WS_CHILD | WS_VISIBLE | BS_BITMAP,
				BUTTON_SHIFT_X(3), BUTTON_SHIFT_Y(3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + i),
				GetModuleHandle(NULL),
				NULL
			);
		}

		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);

		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(1),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);

		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);

		SetSkinFromDLL(hwnd, "square_blue.dll");
	}
	break;

	case WM_CTLCOLOREDIT:
		{
			HDC hdcEdit = (HDC)wParam;
			SetBkMode(hdcEdit, OPAQUE);
			SetBkColor(hdcEdit, g_DISPLAY_BACKGROUND_COLOR[index]);
			SetTextColor(hdcEdit, g_DISPLAY_FOREGROUND_COLOR[index]);

			HBRUSH hbrBackground = CreateSolidBrush(g_WINDOW_BACKGROUND_COLOR[index]);

			SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)hbrBackground);
			SendMessage(hwnd, WM_ERASEBKGND, wParam, 0);
			RedrawWindow(hwnd, NULL, NULL, RDW_ERASE);

			return (LRESULT)hbrBackground;
		}
		break;

	case WM_COMMAND:
	{
		static DOUBLE a = DBL_MIN;
		static DOUBLE b = DBL_MIN;
		static WORD operation = 0;
		static BOOL input = FALSE;
		static BOOL operation_input = FALSE;
		static BOOL equal_pressed = FALSE;

		SetFocus(hwnd); // Что бы работала клавиатура

		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		CONST INT SIZE = 256;
		CHAR sz_display[MAX_PATH]{};
		CHAR sz_digit[2]{};

		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			if (operation_input || equal_pressed)
			{
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"");
				operation_input = equal_pressed = FALSE;
			}

			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (strlen(sz_display) == 1 && sz_display[0] == '0') sz_display[0] = sz_digit[0];
			else strcat(sz_display, sz_digit);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (strchr(sz_display, '.')) break;
			strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}

		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (strlen(sz_display) > 1) sz_display[strlen(sz_display) - 1] = 0;
			else sz_display[0] = '0';
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}

		if (LOWORD(wParam) == IDC_BUTTON_CLR)
		{
			a = b = DBL_MIN;
			operation = 0;
			input = operation_input = FALSE;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
		}

		//------------------------------------------------------------------
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (input && a == DBL_MIN) a = atof(sz_display);
			//input = FALSE;

			if (operation && input) SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			operation = LOWORD(wParam);
			operation_input = TRUE;
			equal_pressed = FALSE;
		}

		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (input) b = atof(sz_display);
			input = FALSE;

			switch (operation)
			{
			case IDC_BUTTON_PLUS: a += b; break;
			case IDC_BUTTON_MINUS: a -= b; break;
			case IDC_BUTTON_ASTER: a *= b; break;
			case IDC_BUTTON_SLASH: a /= b; break;
			}
			operation_input = FALSE;
			equal_pressed = TRUE;
			sprintf(sz_display, "%g", a);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}


	}
	break;

	case WM_KEYDOWN:
		{
		if (GetKeyState(VK_SHIFT) < 0 && wParam == 0x38)
		{
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
		}
		else if (wParam >= '0' && wParam <= '9')
		{
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		}

		else if (wParam >= 0x60 && wParam <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
			//SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x60 + IDC_BUTTON_0), 0);
		}

		switch (wParam)
			{
				case VK_OEM_PLUS:
				case VK_ADD:
					//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0); 
					SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0);
					break;

				case VK_OEM_MINUS:
				case VK_SUBTRACT: 
					//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0); 
					SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, TRUE, 0);
					break;

				case VK_MULTIPLY: 
					//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
					SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
					break;

				case VK_DIVIDE:
				case VK_OEM_2:
					//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
					SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0);
					break;

				case VK_OEM_PERIOD:
				case VK_DECIMAL: 
					//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0); 
					SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, TRUE, 0);
					break;

				case VK_BACK: 
					//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0); 
					SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, TRUE, 0);
					break;
				case VK_ESCAPE: 
					//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0); 
					SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, TRUE, 0);
					break;
				case VK_RETURN: 
					//SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0); 
					SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, TRUE, 0);
					break;
			}
		}
		break;

	case WM_KEYUP:
	{
		if (GetKeyState(VK_SHIFT) < 0 && wParam == 0x38)
		{
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
		}
		else if (wParam >= '0' && wParam <= '9')
		{
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - '0' + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
		}

		else if (wParam >= 0x60 && wParam <= 0x69)
		{
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x60 + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
		}

		switch (wParam)
		{
			case VK_OEM_PLUS: 
			case VK_ADD: 
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0); 
				break;

			case VK_OEM_MINUS:
			case VK_SUBTRACT: 
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0); 
				break;

			case VK_MULTIPLY: 
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0); 
				break;

			case VK_DIVIDE:
			case VK_OEM_2:
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
				break;
			
			case VK_OEM_PERIOD:
			case VK_DECIMAL: 
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0); 
				break;

			case VK_BACK: 
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0); 
				break;
			
			case VK_ESCAPE: 
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0); 
				break;
			case VK_RETURN:
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
				break;
		}
	}
	break;

	case WM_CONTEXTMENU:
		{
			// 1) создаём всплывающее меню
			HMENU hMenu = CreatePopupMenu(); 
			HMENU hMenuSkins = CreatePopupMenu();
			HMENU hMenuFonts = CreatePopupMenu();

			// 2) добавляем пункты в меню
			InsertMenu(hMenuFonts, 0, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, IDR_TERMINATOR, "Terminator Two"); 
			InsertMenu(hMenuFonts, 0, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, IDR_MOSCOW2024, "MOSCOW2024");
			InsertMenu(hMenuFonts, 0, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, IDR_DS_DIGITAL, "DS-Didital");
			InsertMenu(hMenuFonts, 0, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, IDR_DIGITAL_7, "Didital-7");

			InsertMenu(hMenuSkins, 0, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, IDR_METAL_MISTRAL, "Metal mistral");
			InsertMenu(hMenuSkins, 0, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, IDR_SQUARE_BLUE, "Square blue");
			
			InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, IDR_EXIT, "Exit");
			InsertMenu(hMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);

			InsertMenu(hMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hMenuFonts, "Fonts");
			InsertMenu(hMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hMenuSkins, "Skins");


			CheckMenuItem(hMenuSkins, index, MF_BYPOSITION | MF_CHECKED);
			CheckMenuItem(hMenuFonts, font_index, MF_BYPOSITION | MF_CHECKED);

			// 3) Использование контекстного меню
			DWORD item = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_RIGHTALIGN | TPM_BOTTOMALIGN, LOWORD(lParam), HIWORD(lParam), 0, hwnd, NULL);
			switch (item)
				{
					case IDR_SQUARE_BLUE:    
					case IDR_METAL_MISTRAL:  
						index = item - IDR_SQUARE_BLUE;
						break;

					case IDR_TERMINATOR:
					case IDR_MOSCOW2024:
					case IDR_DS_DIGITAL:
					case IDR_DIGITAL_7:
						font_index = item - IDR_FONTS - 1;
						break;

					case IDR_EXIT:           SendMessage(hwnd, WM_CLOSE, 0, 0); break;
				}
				
			HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
			HDC hdcDisplay = GetDC(hEditDisplay);
			SendMessage(hwnd, WM_CTLCOLOREDIT, (WPARAM)hdcDisplay, 0);
			ReleaseDC(hEditDisplay, hdcDisplay);
			SetSkinFromDLL(hwnd, g_SKIN[index]);
			SetFont(hwnd, g_FONT_NAMES[font_index]);
			SetFocus(hEditDisplay);


			// 4) Удаляем меню
			DestroyMenu(hMenuFonts);
			DestroyMenu(hMenuSkins);
			DestroyMenu(hMenu);
		}
		break;

	case WM_DESTROY:
		{
			FreeLibrary(hFontsModule);
			PostQuitMessage(0); 
		}
		break;
		
	case WM_CLOSE: DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return FALSE;
}

INT GetTitleBarHeight(HWND hwnd)
{
	RECT window_rect;
	RECT client_rect;

	GetWindowRect(hwnd, &window_rect);
	GetWindowRect(hwnd, &client_rect);

	INT title_bar_height = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

	return title_bar_height;
}

CONST CHAR* g_BUTTONS[] =
{
	"button_0.bmp",
	"button_1.bmp",
	"button_2.bmp",
	"button_3.bmp",
	"button_4.bmp",
	"button_5.bmp",
	"button_6.bmp",
	"button_7.bmp",
	"button_8.bmp",
	"button_9.bmp",
	"button_point.bmp",
	"button_plus.bmp",
	"button_minus.bmp",
	"button_aster.bmp",
	"button_slash.bmp",
	"button_bsp.bmp",
	"button_clr.bmp",
	"button_equal.bmp"
};

VOID SetSkin(HWND hwnd, CONST CHAR skin[])
{
	CHAR sz_filename[MAX_PATH]{};
	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_EQUAL; i++)
	{
		HWND hButton = GetDlgItem(hwnd, i);
		sprintf(sz_filename, "ButtonsBMP\\%s\\%s", skin, g_BUTTONS[i - IDC_BUTTON_0]);
		HBITMAP bmpButton = (HBITMAP)LoadImage
		(
			NULL,
			sz_filename,
			IMAGE_BITMAP,
			i == IDC_BUTTON_0		 ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			i == IDC_BUTTON_EQUAL	 ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton);
	}
}

VOID SetSkinFromDLL(HWND hwnd, CONST CHAR skin[])
{
	HMODULE hModule = LoadLibrary(skin);
	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_EQUAL; i++)
	{
		HWND hButton = GetDlgItem(hwnd, i);
		HBITMAP bmpButton = (HBITMAP)LoadImage
		(
			hModule,
			MAKEINTRESOURCE(i),
			IMAGE_BITMAP,
			i == IDC_BUTTON_0		?  g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			i == IDC_BUTTON_EQUAL	?  g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			LR_SHARED // NULL тоже работает
		);
		SendMessage(hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton); // IMAGE_BITMAP можно не указывать и оставит 0
	}

	FreeLibrary(hModule);
}

VOID LoadFontFromDLL(HMODULE hFontModule, INT resourceID)
{
	HRSRC hFntRes = FindResource(hFontModule, MAKEINTRESOURCE(resourceID), MAKEINTRESOURCE(RT_FONT));
	HGLOBAL hFntMem = LoadResource(hFontModule, hFntRes);
	VOID* fntData = LockResource(hFntMem);
	DWORD nFonts = 0;
	DWORD len = SizeofResource(hFontModule, hFntRes);
	AddFontMemResourceEx(fntData, len, NULL, &nFonts);
}

VOID LoadFontsFromDLL(HMODULE hFontsModule)
{
	for (int i = 2001; i <= 2004; i++)
	{
		LoadFontFromDLL(hFontsModule, i);
	}
}

VOID SetFont(HWND hwnd, CONST CHAR font_name[])
{
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
	HFONT hFont = CreateFont
	(
		g_i_FONT_HEIGHT, g_i_FONT_WIDTH,
		0, 0,
		FW_MEDIUM, 0, 0, 0,
		ANSI_CHARSET,
		OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		font_name
	);
	SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
}