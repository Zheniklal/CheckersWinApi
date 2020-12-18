#include "Config.h"

#include "StdAfx.h"
#include "resource.h"
#include "Game.h"

TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Прототип функции обработки сообщений с пользовательским названием:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE hInst);
BOOL InitInstance(HINSTANCE hInst, int nCmdShow);

// Управляющая функция:
int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпляра приложения
	HINSTANCE hPrevInst, // не используем
	LPSTR lpCmdLine, // не используем
	int nCmdShow) // режим отображения окошка
{
	LoadString(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInst, IDC_MY50, szWindowClass, MAX_LOADSTRING);
	//	HWND hMainWnd; // создаём дескриптор будущего окошка
	MSG msg; // создём экземпляр структуры MSG для обработки сообщений
	MyRegisterClass(hInst);
	if (!InitInstance(hInst, nCmdShow)) {
		return FALSE;
	}

	while (GetMessage(&msg, NULL, NULL, NULL)) { // извлекаем сообщения из очереди, посылаемые фу-циями, ОС
		TranslateMessage(&msg); // интерпретируем сообщения
		DispatchMessage(&msg); // передаём сообщения обратно ОС
	}
	return msg.wParam; // возвращаем код выхода из приложения
}


ATOM MyRegisterClass(HINSTANCE hInst) {
	WNDCLASSEX wc; // создаём экземпляр, для обращения к членам класса WNDCLASSEX
	wc.cbSize = sizeof(wc); // размер структуры (в байтах)
	wc.style = CS_HREDRAW | CS_VREDRAW; // стиль класса окошка
	wc.lpfnWndProc = WndProc; // указатель на пользовательскую функцию
	wc.lpszMenuName = NULL; // указатель на имя меню (у нас его нет)
	wc.lpszClassName = szWindowClass; // указатель на имя класса
	wc.cbWndExtra = NULL; // число освобождаемых байтов в конце структуры
	wc.cbClsExtra = NULL; // число освобождаемых байтов при создании экземпляра приложения
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // декриптор пиктограммы
	wc.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2)); // дескриптор маленькой пиктограммы (в трэе)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // дескриптор курсора
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(253, 253, 200)); // дескриптор кисти для закраски фона окна
	wc.hInstance = hInst; // указатель на строку, содержащую имя меню, применяемого для класса
	if (!RegisterClassEx(&wc)) {
		// в случае отсутствия регистрации класса:
		MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
		return NULL; // возвращаем, следовательно, выходим из WinMain
	}
	return RegisterClassEx(&wc);
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow) {
	HWND hMainWnd;
	// Функция, создающая окошко:
	hMainWnd = CreateWindow(szWindowClass, // имя класса
		szTitle,  // имя окошка (то что сверху)
		WS_CAPTION | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // режимы отображения окошка
		CW_USEDEFAULT, // позиция окошка по оси х
		NULL, // позиция окошка по оси у (раз дефолт в х, то писать не нужно)
		visOkna - 42,//    (CW_USEDEFAULT для автоматич) ширина окошка
		visOkna,// высота окошка (раз дефолт в ширине, то писать не нужно) - NULL
		(HWND)NULL, // дескриптор родительского окна
		NULL, // дескриптор меню
		HINSTANCE(hInst), // дескриптор экземпляра приложения
		NULL); // ничего не передаём из WndProc
	if (!hMainWnd) {
		// в случае некорректного создания окошка (неверные параметры и тп):
		MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
		return FALSE;
	}
	ShowWindow(hMainWnd, nCmdShow); // отображаем окошко
	UpdateWindow(hMainWnd); // обновляем окошко
	return TRUE;
}

Game *game;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC; // создаём дескриптор ориентации текста на экране
	static HANDLE hFile = NULL;
	static HINSTANCE hInst;
	PAINTSTRUCT ps; // структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
	RECT rect; // стр-ра, определяющая размер клиентской области
	static POINT point;

	switch (uMsg) {
	case WM_CREATE: {
		HMENU hMenubar = CreateMenu();
		HMENU hFile = CreateMenu();
		HMENU hGame = CreateMenu();

		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hGame, L"Игра");

		AppendMenu(hGame, MF_POPUP, (UINT_PTR)hFile, L"Новая");
		AppendMenu(hGame, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hGame, MF_STRING, ID_exit, L"Выход");

		AppendMenu(hFile, MF_STRING, ID_new2, L"Два игрока");
		SetMenu(hWnd, hMenubar);
		game = new Game;

	}
					break;
	case WM_LBUTTONDOWN: {
		point.x = HIWORD(lParam) / 65;
		point.y = LOWORD(lParam) / 65;

		game->gameChess(point);
		InvalidateRect(hWnd, NULL, FALSE);
	}
						 break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_exit:
			DestroyWindow(hWnd);
			break;
		
		case ID_new2:
			game->twoPlayerGame();
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		break;
	case WM_PAINT: // если нужно нарисовать, то:
		hDC = BeginPaint(hWnd, &ps); // инициализируем контекст устройства
		GetWindowRect(hWnd, &rect);
		game->drawBoard(hDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}

