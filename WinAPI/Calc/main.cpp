#include <Windows.h>
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



CONST CHAR g_sz_WINDOW_CLASS[] = "Calc_VPD_311";

CONST INT g_i_SCREEN_WIDTH = 400;
CONST INT g_i_SCREEN_HEIGHT = 22;

CONST INT g_i_WINDOW_WIDTH = 250;
CONST INT g_i_WINDOW_HEIGHT = 362;

CONST INT g_i_EDIT_HEIGHT = 22;

CONST INT g_i_BUTTON_SIZE = 50; // Размер кнопки в пикселах
CONST INT g_i_INTERVAL = 10;     // Расстояние между кнопками

CONST INT g_i_START_X = 10;     // 
CONST INT g_i_START_Y = 10;     // 
CONST INT g_i_BUTTON_START_X = g_i_START_X;     // 
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_INTERVAL;     // 

CONST INT g_i_EDIT_WIDTH = (g_i_BUTTON_SIZE * 4)+(g_i_INTERVAL * 3);


INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// 1) Регистация класса окна
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = CS_HREDRAW | CS_VREDRAW;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CALCULATOR));
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CALCULATOR));
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "Cursors\\starcraft-original\\Normal Select.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = g_sz_WINDOW_CLASS;
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

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW,
		window_start_x, window_start_y,
		(g_i_WINDOW_WIDTH + 15), (g_i_WINDOW_HEIGHT + 10),
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
	switch (uMsg)
	{
		case WM_CREATE:
			{
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
					GetModuleHandle(NULL),
					NULL
				);
			}
			break;
		case WM_COMMAND:
			{

			}
			break;
	
		case WM_DESTROY: PostQuitMessage(0); break;
		case WM_CLOSE: DestroyWindow(hwnd); break;
		default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	
	return FALSE;
}