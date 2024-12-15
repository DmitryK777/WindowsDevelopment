#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <Float.h>
#include <cstdio>
#include <cstring>

#include "Resource.h"
#include "Dimensions.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc_VPD_311";

CONST CHAR* g_OPERATIONS[] = { "+", "-", "*", "/" };

static CONST CHAR* theme;


INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

VOID SetSkin(HWND hwnd, CONST CHAR skin[]);

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
				//SetSkin(hwnd, "square_blue");
				SetSkin(hwnd, "metal_mistral");

				CONST INT SIZE = 256;
				CHAR path[SIZE]{};

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
						HWND hButton_digit = CreateWindowEx
						(
							NULL, "Button", sz_digit,
							WS_CHILD | WS_VISIBLE | BS_BITMAP,
							g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
							g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (2 - i/3),
							g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
							hwnd,
							(HMENU)(IDC_BUTTON_1 + i + j),
							GetModuleHandle(NULL),
							NULL
						);
						sprintf(path, "ButtonsBMP\\%s\\button_%c.bmp", theme, sz_digit[0]);
						HBITMAP bmpButton_digit = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE, LR_LOADFROMFILE);
						SendMessage(hButton_digit, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_digit);
					}
				}

				// 1) Добавить стиль BS_BITMAP
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
				sprintf(path, "ButtonsBMP\\%s\\button_0.bmp", theme);
				// 2) Загрузить картинку из файла
				HBITMAP bmpButton_0 = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE, LR_LOADFROMFILE);
				// 3) Установить картинку на кнопку
				SendMessage(hButton_0, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_0);


				HWND hButton_point = CreateWindowEx
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
				sprintf(path, "ButtonsBMP\\%s\\button_point.bmp", theme);
				HBITMAP bmpButton_point = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE, LR_LOADFROMFILE);
				SendMessage(hButton_point, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_point);

				for (int i = 0; i < 4; i++)
				{
					HWND hButton_operation = CreateWindowEx
					(
						NULL, "Button", g_OPERATIONS[i],
						WS_CHILD | WS_VISIBLE | BS_BITMAP,
						BUTTON_SHIFT_X(3), BUTTON_SHIFT_Y(3-i),
						g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
						hwnd,
						(HMENU)(IDC_BUTTON_PLUS + i),
						GetModuleHandle(NULL),
						NULL
					);
					
					const CHAR* operation_add;
					switch ((int)g_OPERATIONS[i][0])
					{
						case (int)'+': operation_add = "plus"; break;
						case (int)'-': operation_add = "minus"; break;
						case (int)'*': operation_add = "aster"; break;
						case (int)'/': operation_add = "slash"; break;
						default: operation_add = "\0";  break;
					}
					sprintf(path, "ButtonsBMP\\%s\\button_%s.bmp", theme, operation_add);
					HBITMAP bmpButton_operation = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE, LR_LOADFROMFILE);
					SendMessage(hButton_operation, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_operation);
				}

				HWND hButton_bsp = CreateWindowEx
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
				sprintf(path, "ButtonsBMP\\%s\\button_bsp.bmp", theme);
				HBITMAP bmpButton_bsp = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE, LR_LOADFROMFILE);
				SendMessage(hButton_bsp, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_bsp);


				HWND hButton_clr = CreateWindowEx
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
				sprintf(path, "ButtonsBMP\\%s\\button_clr.bmp", theme);
				HBITMAP bmpButton_clr = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, g_i_BUTTON_SIZE, g_i_BUTTON_SIZE, LR_LOADFROMFILE);
				SendMessage(hButton_clr, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_clr);


				HWND hButton_equal = CreateWindowEx
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
				sprintf(path, "ButtonsBMP\\%s\\button_equal.bmp", theme);
				HBITMAP bmpButton_equal = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE, LR_LOADFROMFILE);
				SendMessage(hButton_equal, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpButton_equal);
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
					if(strchr(sz_display, '.')) break;
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
				if (wParam >= '0' && wParam <= '9')
				{
					SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - '0' + IDC_BUTTON_0), 0);
				}
					
				if (wParam >= 0x60 && wParam <= 0x69)
				{
					SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x60 + IDC_BUTTON_0), 0);
				}

				switch (wParam)
				{
					case VK_OEM_PERIOD: 
					case VK_DECIMAL: SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0); break;
					case VK_BACK: SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0); break;
					case VK_ESCAPE: SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0); break;
					
				}
			}
			break;
		case WM_DESTROY: PostQuitMessage(0); break;
		case WM_CLOSE: DestroyWindow(hwnd); break;
		default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	
	return FALSE;
}


VOID SetSkin(HWND hwnd, CONST CHAR skin[])
{
	theme = skin;
}