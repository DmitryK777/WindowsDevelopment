﻿#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <cstdio>
#include "Resource.h"

#define IDC_STATIC 1000
#define IDC_EDIT 1001
#define IDC_BUTTON 1002


CONST CHAR g_sz_WINDOW_CLASS[] = "My Main Window";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// 1) Регистрация класса окна

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_BITCOIN));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_PALM));
	//wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\bitcoin.ico",IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\palm.ico",IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "Cursors\\starcraft-original\\Link Select.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpfnWndProc = (WNDPROC)WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration faild", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	// 2) Создание окна

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_width = screen_width * 3 / 4;
	INT window_height = screen_height * .75;

	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,                 // Ex-Styles
		g_sz_WINDOW_CLASS,    // Class Name
		g_sz_WINDOW_CLASS,    // Window Title
		WS_OVERLAPPEDWINDOW,  // Window Style - такой стиль всегда задаётся для главного окна
		window_start_x, window_start_y,   // Position - положение окна при запуске
		window_width, window_height,   // Size - размер окна
		NULL,
		NULL, // hMenu - для главного окна это ResourseID главного меню, 
		      //         для дочернего окна (или элемента) - это ResourceID соответствующего элемента
		      // по этому ResourceID нужный элемент всегда можно получить при помощи функции GetDlgItem()
		      // кроме того этот ResourceID будет прилетать в параметре LOWORD(wParam) при воздействии пользователя
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);   // Задаёт режим отображения окна (развёрнуто на весь экран, свёрнуто в окно, свёрнуто на панель задач)
	UpdateWindow(hwnd);           // Прорисовывает окно


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
				HWND hStatic = CreateWindowEx
				(
					NULL,
					"Static",
					"Этот статический текст создан функцией CreateWindowEx();",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP,
					10, 10,
					800, 22,
					hwnd,
					(HMENU)IDC_STATIC,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hEdit = CreateWindowEx
				(
					NULL,
					"Edit",
					"",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER,
					10, 32,
					500, 22,
					hwnd,
					(HMENU)IDC_EDIT,
					GetModuleHandle(NULL),
					NULL
				);

				HWND hButton = CreateWindowEx
				(
					NULL,
					"Button",
					"Применить",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
					410, 58,
					100, 32,
					hwnd,
					(HMENU)IDC_BUTTON,
					GetModuleHandle(NULL),
					NULL
				);
			}
			break;
		case WM_MOVE:
		case WM_SIZE:
			{
				RECT window_rect;
				GetWindowRect(hwnd, &window_rect);
				INT window_width = window_rect.right - window_rect.left;
				INT window_height = window_rect.bottom - window_rect.top;

				CONST INT SIZE = 256;
				CHAR  sz_title[SIZE]{};
				sprintf
				(sz_title, "%s   Position: %ix%i;   Size: %ix%i", 
					g_sz_WINDOW_CLASS,
					window_rect.left,
					window_rect.top,
					window_width, 
					window_height
				);

				SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
			}
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
				{
					case IDC_BUTTON:
						HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
						HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
						CONST INT SIZE = 256;
						CHAR sz_buffer[SIZE]{};
						SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
						SendMessage(hStatic, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
						SendMessage(hwnd, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
				}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		default:       return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}