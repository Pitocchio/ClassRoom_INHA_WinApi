#include "framework.h"
#include "WinApi32_Wizard.h"
#include <cmath>
#include <string>
#include <iostream>


#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void DrawMove_Ellipse(HDC hdc, POINT curPos);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI32WIZARD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI32WIZARD));

    MSG msg;

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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI32WIZARD));
    wcex.hCursor = LoadCursor(nullptr, IDC_IBEAM);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI32WIZARD);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        200, 300, 1000, 800, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

int KeyDown(0), KeyUp(0);

bool bFlag(0);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT curPos;
    static RECT rcClient;
    RECT rc{ 0 };
    switch (message)
    {
    case WM_CREATE:

        curPos.x = 20;
        curPos.y = 20;

        GetClientRect(hWnd, &rcClient);

        // 타이머 이벤트 변수 설정 
        
        SetTimer(hWnd, 1, 100, NULL); // 기본, 타이머 ID, ms마다 이벤트 호출, 함수호출
        SetTimer(hWnd, 2, 100, NULL);
        

        break;

        //타이머 이벤트 호출
        case WM_TIMER:
            if (wParam == 1) // 1번 타이머라면
            {
                curPos.x += 40;

            }

            if (wParam == 2)
            {
                curPos.y += 40;

            }

            InvalidateRect(hWnd, NULL, TRUE);

            break;
        

        // 마우스 이벤트  호출
    case WM_LBUTTONDOWN:
    {
        if (sqrt(pow((LOWORD(lParam) - curPos.x), 2) + pow((HIWORD(lParam) - curPos.y), 2)) <= 20)
            bFlag = true;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }

    case WM_LBUTTONUP:
    {
        bFlag = false;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }

    case WM_MOUSEMOVE:
    {
        if (bFlag)
        {
            curPos.x = LOWORD(lParam);
            curPos.y = HIWORD(lParam); // 클릭시 오브젝트 위치를 클릭 위치로 설정
            InvalidateRect(hWnd, NULL, TRUE);
        }

        break;
    }


    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;


    case WM_KEYDOWN:
    {
        RECT rc;
        GetClientRect(hWnd, &rc);

        // 방향키로 원 움직이기 (윈도우 벗어남X)
        switch (wParam)
        {
        case VK_LEFT:
            if (curPos.x <= rcClient.left + 20)
                curPos.x = rcClient.left + 20;
            else
                curPos.x -= 40;
            break;

        case VK_RIGHT:
            if (curPos.x >= rcClient.right - 20)
                curPos.x = rcClient.right - 20;
            else
                curPos.x += 40;
            break;

        case VK_UP:
            if (curPos.y <= rcClient.top + 20)
                curPos.y = rcClient.top + 20;
            else
                curPos.y -= 40;
            break;

        case VK_DOWN:
            if (curPos.y >= rcClient.bottom - 20)
                curPos.y = rcClient.bottom - 20;
            else
                curPos.y += 40;
            break;
        }
        InvalidateRect(hWnd, NULL, TRUE);


    }
    break;
    case WM_KEYUP:
    {

    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        if (bFlag)
            SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
        else
            SelectObject(hdc, GetStockObject(WHITE_BRUSH));

        DrawMove_Ellipse(hdc, curPos);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        HideCaret(hWnd);
        PostQuitMessage(0);
        KillTimer(hWnd, 1);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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




void DrawMove_Ellipse(HDC hdc, POINT curPos)
{
    Ellipse(hdc, curPos.x - 20, curPos.y - 20, curPos.x + 20, curPos.y + 20);
}

