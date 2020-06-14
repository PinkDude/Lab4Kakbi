// Lab_OC_5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab4Kakbi.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Triangles(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Ellipses(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4KAKBI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4KAKBI));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABOC5));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB4KAKBI);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_CREATE   - создание виртуального окна
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
HDC memdc; // контекст устройства памяти
HBITMAP hbit; // растр изображения в окне 
HBRUSH hbrush; // дескриптор текущей кисти
HBRUSH hOldbrush; // дескриптор предыдущей кисти
HPEN hRedPen, hBluePen; // дескрипторы синего и красного перьев
HPEN hOldpen; // дескриптор предыдущего состояния пера
int maxX, maxY; // размеры экрана

/* координаты вершин треугольников */
POINT mp1[3] = { {150, 50}, {50, 150}, {150, 150} }; // 1 трегоульник
POINT mp2[3] = { {250, 150}, {350, 50}, {450, 150} }; // 2 трегоульник
COLORREF color = RGB(255, 255, 0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;

    switch (message)
    {
    case WM_CREATE:
    {
        maxX = GetSystemMetrics(SM_CXSCREEN);
        maxY = GetSystemMetrics(SM_CYSCREEN);
        hdc = GetDC(hWnd);
        memdc = CreateCompatibleDC(hdc);
        hbit = CreateCompatibleBitmap(hdc, maxX, maxY);

        /* выбор растрового изображения в контекст устройства памяти */
        SelectObject(memdc, hbit);
        PatBlt(memdc, 0, 0, maxX, maxY, PATCOPY);

        /* создание красного и синего перьев */
        hRedPen = CreatePen(PS_SOLID, 2, RGB(200, 0, 0));
        hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

        ReleaseDC(hWnd, hdc);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_TRIANGES:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_TRIANGLESBOX), hWnd, Triangles);
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case ID_ELLIPSES:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ELLIPSESBOX), hWnd, Ellipses);
            break;
        case ID_RECT:
            PatBlt(memdc, 0, 0, maxX, maxY, PATCOPY);
            hbrush = CreateSolidBrush(color);
            hOldbrush = (HBRUSH)SelectObject(memdc, hbrush);
            hOldpen = (HPEN)SelectObject(memdc, hRedPen);
            Rectangle(memdc, 50, 50, 200, 200);
            SelectObject(memdc, hBluePen);
            RoundRect(memdc, 250, 50, 400, 150, 30, 30);
            SelectObject(memdc, hOldpen);
            SelectObject(memdc, hOldbrush);
            DeleteObject(hbrush);
            Polygon(memdc, (const POINT*)3, (int)mp1);
            InvalidateRect(hWnd, NULL, 0);
            break;
        case ID_RED:
            color = RGB(250, 0, 0);
            break;
        case ID_BLACK:
            color = RGB(0, 0, 0);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        BitBlt(hdc, 0, 0, maxX, maxY, memdc, 0, 0, SRCCOPY);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        DeleteObject(hRedPen);
        DeleteObject(hBluePen);
        DeleteDC(memdc);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
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

// Обработчик сообщений для окна "Треугольники"
INT_PTR CALLBACK Triangles(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

// Обработчик сообщений для окна "Эллипсы"
INT_PTR CALLBACK Ellipses(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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