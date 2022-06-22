#include "framework.h"
#include "WinApi32_Wizard.h"
#include <cmath>
#include <string>
#include <iostream>
const double PI = 3.14159265358979323;

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                 
WCHAR szWindowClass[MAX_LOADSTRING];           

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void DrawGrid_Test(HDC hdc, POINT LeftTop, POINT RightBottom, LONG nWidth, LONG nHeight); // 격자무늬 그리기
void DrawCircle_Test(HDC hdc, POINT center, int radius);
void DrawPolygon_Test(HDC hdc);
void DrawSunFlower_Test(HDC hdc, POINT center, int radius, int num);
void DrawStar_Test(HDC hdc, POINT center, int distance, int num);

void DrawRectangle_Test(HDC hdc, RECT rc, const char* s);

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



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT curPos;
    static RECT rcClient;
    RECT rc{ 0 };
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

  

    case WM_PAINT: // c_글자출력이나 글씨를 쓰거나 다 여기서!!!!
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps); // 그리기 시작 포인트

        POINT iCenter = tagPOINT{ 300, 300 };

        DrawStar_Test(hdc, iCenter, 100, 5);
     

        EndPaint(hWnd, &ps); 
    }
    break;
    case WM_DESTROY: 
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

void DrawCircle_Test(HDC hdc, POINT center, int radius)
{
    Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}


void DrawPolygon_Test(HDC hdc)
{
    POINT point[5] = { {10, 150}, {250, 30}, {500, 150}, {350, 300}, {150, 300} };
    Polygon(hdc, point, 5);
}

void DrawStar_Test(HDC hdc, POINT center, int distance, int num)
{
    POINT* arr = new POINT[num];

    double angle;
    angle = 2 * PI / num;
    POINT MovePoint;

    DrawCircle_Test(hdc, center, 3);

    for (int i = 0; i < num; ++i)
    {
        MovePoint.x = center.x + distance * cosf(angle * i);
        MovePoint.y = center.y + distance * sinf(angle * i);

        arr[i] = MovePoint;

        DrawCircle_Test(hdc, MovePoint, 3);
    }

    double d = sqrt(pow((arr[0].x - arr[1].x), 2) + pow((arr[0].y - arr[1].y), 2));
    double t = sqrt(pow((center.x - arr[0].x), 2) + pow((center.y - arr[0].y), 2));
    double x = sqrt(pow(t, 2) - (pow(d, 2) / 4));
    double m = d / (2 * tanf(angle / 2));

    POINT MovePoint1;

    MovePoint1.x = center.x + (x - m) * sinf(angle / 2);
    MovePoint1.y = center.y + (x - m) * cosf(angle / 2);

    DrawCircle_Test(hdc, MovePoint1, 5);


    Polygon(hdc, arr, num);

    delete[] arr;

}


