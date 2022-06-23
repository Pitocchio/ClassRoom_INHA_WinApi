#include "framework.h"
#include "WinApi32_Wizard.h"
#include <string>
#include <iostream>
const double PI = 3.14159265358979323;

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

static TCHAR str[256]; 
static int count, yPos; 

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawRectangle_Test(HDC hdc, RECT rc);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI32WIZARD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI32WIZARD));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0)) // c_만약 이벤트가 발생했다면 가져오겠다
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); // c_메시지 번역
            DispatchMessage(&msg); // c_ 메시지를 보냄
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) // c_ 윈도우 기본 설정 
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI32WIZARD)); // 아이콘 설정
    wcex.hCursor = LoadCursor(nullptr, IDC_IBEAM); // 커서 설정 
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);// (COLOR_WINDOW+1); // 배경색 설정 
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI32WIZARD); // NULL; 처리하면 위 상단바 없어짐
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // c_ 실질적인 윈도우 세팅, 초기화 // WS_OVERLAPPED = 클로즈 메뉴 등이 없이 세팅
        200, 300, 1000, 800, nullptr, nullptr, hInstance, nullptr); // c_ 창 크기 조절 가능

    if (!hWnd) // c_위 윈도우 생성이 안됬다면 NULL 값 반환
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow); // c_ show 모드 변경 가능
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    bool bArr[4] = { 0 };

    switch (message)
    {
    case WM_CREATE: 
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
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
        switch (wParam)
        {
            case VK_LEFT: {
                bArr[0] = true;
                break;
            }

            case VK_UP: {
                bArr[1] = true;
                break;
            }

            case VK_RIGHT: {
                bArr[2] = true;
                break;
            }

            case VK_DOWN: {
                bArr[3] = true;
                break;
            }
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_KEYUP: 
    {
        switch (wParam)
        {
            case VK_LEFT: {
                bArr[0] = false;
                break;
            }
           
            case VK_UP: {
                bArr[1] = false;
                break;
            }

            case VK_RIGHT: {
                bArr[2] = false;
                break;
            }

            case VK_DOWN: {
                bArr[3] = false;
                break;
            }
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_PAINT: 
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps); 

        HBRUSH hBrush, oldBrush;

        RECT RC[4] =
        {
            { 300, 200, 400, 400 },
            { 400, 000, 500, 200 },
            { 500, 200, 600, 400 },
            { 400, 400, 500, 600 }
        };

        for (int i = 0; i < 4; ++i)
        {
            if (bArr[i] == true)
            {
                hBrush = CreateSolidBrush(RGB(255, 0, 0));
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

                DrawRectangle_Test(hdc, RC[i]);
                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);
            }
            else
            {
                hBrush = CreateSolidBrush(RGB(255,255,255));
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

                DrawRectangle_Test(hdc, RC[i]);
                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);
            }
        }
        EndPaint(hWnd, &ps);
        break;
    }
   
    case WM_DESTROY: 
        PostQuitMessage(0);
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





// =========================================================================================================================================================//



void DrawRectangle_Test(HDC hdc, RECT rc)
{
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
