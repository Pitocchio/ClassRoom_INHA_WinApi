#include "framework.h"
#include "WinApi32_Wizard.h"
#include <cmath>
#include <string>
#include <iostream>
#include <commdlg.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


void DrawMove_Ellipse(HDC hdc, POINT curPos);
void DrawRectangle_Test(HDC hdc);
void OutFromFile(TCHAR filename[], HWND hwnd); // ������ �о ������ â�� �׷��ִ� �Լ�


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
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI32WIZARD); // �޴� ���ҽ� �߿� ����� �޴� ���ҽ� ���� ���ڷ� �־��ָ� ��
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
    static RECT rcClient;
    static int selectedMenu;
    RECT rc{ 0 };
    static HMENU hMenu, hSubmenu;

    switch (message)
    {
    case WM_CREATE:

        GetClientRect(hWnd, &rcClient);
        
        // ��ũ��Ʈ�� �޴�â ����
        hMenu = GetMenu(hWnd);
        hSubmenu = GetSubMenu(hMenu, 2);
       /* EnableMenuItem(hSubmenu, ID_DrawCircle, MF_DISABLED);
        EnableMenuItem(hSubmenu, ID_DrawRect, MF_DISABLED);*/

        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_OpenFile:
        {
            TCHAR str[100], lpstrFile[100] = _T("");
            TCHAR filter[] = _T("Every File(*.*) \0*.*\0Text File\0*.t\0;*.doc\0");

            OPENFILENAME ofn;
            memset(&ofn, 0, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;// �θ𿩺ο� ���� ����
            ofn.lpstrFilter = filter;
            ofn.lpstrFile = lpstrFile;
            ofn.nMaxFile = 100;
            ofn.lpstrInitialDir = _T(".");
            if (GetOpenFileName(&ofn) != 0)
            {
                _stprintf_s(str, _T("%s ������ ���ڽ��ϱ�?"), ofn.lpstrFile);
                MessageBox(hWnd, str, _T("���� ����"), MB_OK);
                //OutFromFile(ofn.lpstrFile, hWnd);
            }
            
        }
            break;
        case ID_SaveFile:
        {
            TCHAR str[100], lpstrFile[100] = _T("");
            TCHAR filter[] = _T("Every File(*.*) \0*.*\0Text File\0*.t\0;*.doc\0");

            OPENFILENAME ofn;
            memset(&ofn, 0, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;// �θ𿩺ο� ���� ����
            ofn.lpstrFilter = filter;
            ofn.lpstrFile = lpstrFile;
            ofn.nMaxFile = 256;
            ofn.lpstrInitialDir = _T(".");
            if (GetSaveFileName(&ofn) != 0)
            {
                 _stprintf_s(str, _T("%s ������ ���ڽ��ϱ�?"), ofn.lpstrFile);
                 MessageBox(hWnd, str, _T("���� ����"), MB_OK);
            }

        }
        break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_DrawCircle:
        {
            MessageBox(hWnd, _T("�ȳ� ���� �����̾�"), _T("������"), MB_OKCANCEL); // �޽��� �ڽ� ����
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        }
        case ID_DrawRect:
        {
            selectedMenu = wmId;
            //int answer = MessageBox(hWnd, _T("������ �޴��� �����Ͻðڽ��ϱ�?"), _T("�޴�Ȯ��"), MB_OKCANCEL); // �޽��� �ڽ� ����
            MessageBox(hWnd, _T("�ȳ� ���� �׸��"), _T("�׸��"), MB_OKCANCEL); // �޽��� �ڽ� ����

            InvalidateRect(hWnd, NULL, TRUE);
            
            /*if (answer == IDOK)
            {
                
            }
            else if (answer == IDCANCEL)
            {

            }*/
            break;

        }

        
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
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

       /* switch (selectedMenu)
        {
            case
        }*/


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



void DrawRectangle_Test(HDC hdc)
{
    Rectangle(hdc, 100, 100, 200, 200);
}

void OutFromFile(TCHAR filename[], HWND hwnd) // �о�� ���� �̸���, �� ������ ����� �����츦 ���ڷ� �޴´�
{
    FILE* fPtr; // �о�� ������ ���� ���� ���� ������ ����
    HDC hdc; // �����쿡 ����ϱ� ���� ����̽� ���ؽ�Ʈ ����
    int line; // ���Ͽ��� �о���� �ؽ�Ʈ�� ���� ���� �����ϱ� ���� ����
    TCHAR buffer[500];
    line = 0;
    hdc = GetDC(hwnd);

#ifdef _UNICODE // �����ڵ��� ���
    _tfopen_s(&fPtr, filename, _T("r, ccs = UNICODE")); // ���� ����

#else // ��Ƽ����Ʈ�� ���
    _tfopens(&fPtr, filename, _T("r"); // ���� ����
#endif
    while (_fgetts(buffer, 100, fPtr) != NULL) 
    {
        // ������ ���� ���� ������ �� ������ ���ۿ� �о����, 
        // ������ ������ ���ڰ� newline�̸� �̰��� null�� ������ �� �����쿡 ���
        if (buffer[_tcsclen(buffer) - 1] == _T('\n'))
            buffer[_tcslen(buffer) - 1] = NULL;
        TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
        line++;
    }
    fclose(fPtr);
    ReleaseDC(hwnd, hdc);
}