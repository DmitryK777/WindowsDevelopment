#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <string.h>
//#include <string.h>
#include <iostream>
#include <sstream>
#include "Resource.h"
#include "Dimensions.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc_VPD_311";

CONST CHAR* g_OPERATIONS[] = { "+", "-", "*", "/" };

DOUBLE first_number = 0;
DOUBLE second_number = 0;
INT operation = 0;


INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// 1) Регистация класса окна

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CALC));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CALC));
	wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
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
	INT window_start_y = (screen_height / 2) - (g_i_WINDOW_HEIGHT);


	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		window_start_x, window_start_y,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	// 3) Запуск цикла сообщений

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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

				CHAR sz_digit[2]{};
				for (int i = 6; i >= 0; i -= 3)
				{
					for (int j = 0; j < 3; j++)
					{
						sz_digit[0] = i + j + '1';
						CreateWindowEx
						(
							NULL, "Button", sz_digit,
							WS_CHILD | WS_VISIBLE,
							g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
							g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (2 - i/3),
							g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
							hwnd,
							(HMENU)(IDC_BUTTON_1 + i + j),
							GetModuleHandle(NULL),
							NULL
						);
					}
				}

				CreateWindowEx
				(
					NULL, "Button", "0",
					WS_CHILD | WS_VISIBLE,
					BUTTON_SHIFT_X(0), BUTTON_SHIFT_Y(3),
					g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_0,
					GetModuleHandle(NULL),
					NULL
				);

				CreateWindowEx
				(
					NULL, "Button", ".",
					WS_CHILD | WS_VISIBLE,
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
						WS_CHILD | WS_VISIBLE,
						BUTTON_SHIFT_X(3), BUTTON_SHIFT_Y(3-i),
						g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
						hwnd,
						HMENU(IDC_BUTTON_PLUS + i),
						GetModuleHandle(NULL),
						NULL
					);
				}

				CreateWindowEx
				(
					NULL, "Button", "<-",
					WS_CHILD | WS_VISIBLE,
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
					WS_CHILD | WS_VISIBLE,
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
					WS_CHILD | WS_VISIBLE,
					BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
					g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
					hwnd,
					(HMENU)IDC_BUTTON_EQUAL,
					GetModuleHandle(NULL),
					NULL
				);
			
			}
			break;

		case WM_COMMAND:
			{
				HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
				CONST INT SIZE = 256;
				CHAR sz_display[MAX_PATH]{};
				CHAR sz_digit[2]{};

				if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
				{
					sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
					SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
					if (strlen(sz_display) == 1 && sz_display[0] == '0') sz_display[0] = sz_digit[0];
					else strcat(sz_display, sz_digit);
					SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
				}

				if (LOWORD(wParam) == IDC_BUTTON_POINT)
				{
					CHAR* sz_buffer;
					SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
					sz_buffer = strchr(sz_display, ' ');
					if (sz_buffer)
					{
						if (strchr(sz_display, '.') && strchr(sz_buffer, '.')) break;
					}
					else
					{
						if (strchr(sz_display, '.')) break;
					}
					strcat(sz_display, ".");
					SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
				}

				if (LOWORD(wParam) == IDC_BUTTON_BSP)
				{
					SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
					INT display_length = strlen(sz_display);
					CHAR sz_buffer[MAX_PATH]{};
					if (display_length > 1)
					{
						display_length--;
						for (int i = 0; i < display_length; i++) sz_buffer[i] = sz_display[i];
					}
					else sz_buffer[0] = '0';
					SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_buffer);
				}

				if (LOWORD(wParam) == IDC_BUTTON_CLR)
				{
					sz_digit[0] = '0';
					SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_digit);
				}

				

				if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
				{
					operation = LOWORD(wParam);
					SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
					first_number = atof(sz_display);

					CHAR sz_buffer[MAX_PATH]{};
					for (int i = 0; i < sizeof(g_OPERATIONS) / sizeof(g_OPERATIONS[0]); i++)
					{
						if (i == operation - IDC_BUTTON_0 - 11)
						{
							strcat(sz_display, " ");
							strcat(sz_display, g_OPERATIONS[i]);
							//strcat(sz_buffer, g_OPERATIONS[i]);
							strcat(sz_display, " ");
							strcat(sz_display, sz_buffer);
							SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
						}
							
					}
				}

				if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
				{
					SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
					
					CHAR* sz_buffer;
					CHAR sz_result[MAX_PATH];

					DOUBLE result;

					switch (operation)
						{
							case IDC_BUTTON_PLUS:
								{
									sz_buffer = strchr(sz_display, '+');
									second_number = atof(++sz_buffer);
									result = first_number + second_number;
								}
								break;

							case IDC_BUTTON_MINUS:
								{
									sz_buffer = strchr(sz_display, '-');
									second_number = atof(++sz_buffer);
									result = first_number - second_number;
								}
								break;

							case IDC_BUTTON_ASTER:
								{
									sz_buffer = strchr(sz_display, '*');
									second_number = atof(++sz_buffer);
									result = first_number * second_number;
								}
								break;

							case IDC_BUTTON_SLASH:
								{
									sz_buffer = strchr(sz_display, '/');
									second_number = atof(++sz_buffer);
									if (second_number != 0) result = first_number / second_number;
									else result = 0;
								}
								break;
						}
					if (result == (int)result) sprintf(sz_result, "%i", (int)result);
					else sprintf(sz_result, "%.5f", result);
					strcat(sz_display, " = ");
					strcat(sz_display, sz_result);
					SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
				}
			}
			break;
	
		case WM_DESTROY: PostQuitMessage(0); break;
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