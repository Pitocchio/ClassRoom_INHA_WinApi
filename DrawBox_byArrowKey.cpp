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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI32WIZARD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI32WIZARD));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0)) // c_���� �̺�Ʈ�� �߻��ߴٸ� �������ڴ�
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); // c_�޽��� ����
            DispatchMessage(&msg); // c_ �޽����� ����
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) // c_ ������ �⺻ ���� 
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI32WIZARD)); // ������ ����
    wcex.hCursor = LoadCursor(nullptr, IDC_IBEAM); // Ŀ�� ���� 
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);// (COLOR_WINDOW+1); // ���� ���� 
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI32WIZARD); // NULL; ó���ϸ� �� ��ܹ� ������
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // c_ �������� ������ ����, �ʱ�ȭ // WS_OVERLAPPED = Ŭ���� �޴� ���� ���� ����
        200, 300, 1000, 800, nullptr, nullptr, hInstance, nullptr); // c_ â ũ�� ���� ����

    if (!hWnd) // c_�� ������ ������ �ȉ�ٸ� NULL �� ��ȯ
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow); // c_ show ��� ���� ����
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
