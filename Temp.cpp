#include "framework.h"
#include "WinApi32_Wizard.h"
#include <cmath>
#include <string>
#include <iostream>
#include <commdlg.h>
#pragma comment(lib, "msimg32.lib") // 비트맵 이미지를 사용하기 위한 라이브러리

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// >> : bipmap
HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hSigongImage;
BITMAP bitSigong;

HBITMAP hAniImage;
BITMAP bitAni;
const int Sprite_Size_X = 57; // 개별사이즈
const int Sprite_Size_Y = 52; // 개별사이즈
int Run_Frame_Max = 0;
int Run_Frame_Min = 0;
int curFrame = Run_Frame_Min;


// Double Buffering
HBITMAP hDoubleBufferImage;
void DrawBitMapDoubleBuffering(HWND hWnd, HDC hdc);


void UpdateFrame(HWND hWnd);


void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();
void DrawRectText(HDC hdc);

// << :

void DrawMove_Ellipse(HDC hdc, POINT curPos);
void DrawRectangle_Test(HDC hdc);
void OutFromFile(TCHAR filename[], HWND hwnd); // 파일을 읽어서 윈도우 창에 그려주는 함수
VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK keyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
TCHAR sKeyState[128];
void Update();
POINT ptAni = { 200, 400 };


// << : Dialog (대화 창)
BOOL CALLBACK Dlg_Proc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);


// >> : GDI+

#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;

ULONG_PTR g_GdiToken;
void Gdi_Init();
void Gdi_Draw(HDC hdc);
void Gdi_End();

// <<

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

  /*  while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
    Gdi_Init();
    while (true) // 메시지 발생 유무에 관계없이 돌리겠다
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // 메시지가 발생하지 않았다면
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            Update();
        }
    }
    Gdi_End();

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
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI32WIZARD); // 메뉴 리소스 중에 사용할 메뉴 리소스 네임 인자로 넣어주면 됨
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
static RECT rcClient;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int selectedMenu;
    RECT rc{ 0 };
    static HMENU hMenu, hSubmenu;


    switch (message)
    {
    case WM_CREATE:

        GetClientRect(hWnd, &rcClient);

        SetTimer(hWnd, 1, 50, TimerProc);
        //SetTimer(hWnd, 2, 200, keyStateProc);


        // 스크립트로 메뉴창 제어
        hMenu = GetMenu(hWnd);
        hSubmenu = GetSubMenu(hMenu, 2);
       /* EnableMenuItem(hSubmenu, ID_DrawCircle, MF_DISABLED);
        EnableMenuItem(hSubmenu, ID_DrawRect, MF_DISABLED);*/


        CreateBitmap();


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
            ofn.hwndOwner = hWnd;// 부모여부와 하위 설정
            ofn.lpstrFilter = filter;
            ofn.lpstrFile = lpstrFile;
            ofn.nMaxFile = 100;
            ofn.lpstrInitialDir = _T(".");
            if (GetOpenFileName(&ofn) != 0)
            {
                _stprintf_s(str, _T("%s 파일을 열겠습니까?"), ofn.lpstrFile);
                MessageBox(hWnd, str, _T("열기 선택"), MB_OK);
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
            ofn.hwndOwner = hWnd;// 부모여부와 하위 설정
            ofn.lpstrFilter = filter;
            ofn.lpstrFile = lpstrFile;
            ofn.nMaxFile = 256;
            ofn.lpstrInitialDir = _T(".");
            if (GetSaveFileName(&ofn) != 0)
            {
                 _stprintf_s(str, _T("%s 파일을 열겠습니까?"), ofn.lpstrFile);
                 MessageBox(hWnd, str, _T("열기 선택"), MB_OK);
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
            MessageBox(hWnd, _T("안녕 나는 동글이야"), _T("동글이"), MB_OKCANCEL); // 메시지 박스 띄우기
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        }
        case ID_DrawRect:
        {
            selectedMenu = wmId;
            //int answer = MessageBox(hWnd, _T("선택한 메뉴로 실행하시겠습니까?"), _T("메뉴확인"), MB_OKCANCEL); // 메시지 박스 띄우기
            MessageBox(hWnd, _T("안녕 나는 네모야"), _T("네모니"), MB_OKCANCEL); // 메시지 박스 띄우기

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

    case WM_LBUTTONDOWN:
    {
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg_Proc);
    }
    break;


    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

     
        //DrawBitmap(hWnd, hdc);
        DrawBitMapDoubleBuffering(hWnd, hdc);
        DrawRectText(hdc);

        EndPaint(hWnd, &ps); 
    }
    break;
    case WM_DESTROY:
        HideCaret(hWnd);
        KillTimer(hWnd, 1);
        //KillTimer(hWnd, 2);
        DeleteBitmap();
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




void DrawMove_Ellipse(HDC hdc, POINT curPos)
{
    Ellipse(hdc, curPos.x - 20, curPos.y - 20, curPos.x + 20, curPos.y + 20);
}



void DrawRectangle_Test(HDC hdc)
{
    Rectangle(hdc, 100, 100, 200, 200);
}

void OutFromFile(TCHAR filename[], HWND hwnd) // 읽어올 파일 이름과, 그 내용을 출력할 윈도우를 인자로 받는다
{
    FILE* fPtr; // 읽어올 파일을 열기 위한 파일 포인터 변수
    HDC hdc; // 윈도우에 출력하기 위한 디바이스 콘텍스트 변수
    int line; // 파일에서 읽어오는 텍스트의 라인 수를 저장하기 위한 변수
    TCHAR buffer[500];
    line = 0;
    hdc = GetDC(hwnd);

#ifdef _UNICODE // 유니코드일 경우
    _tfopen_s(&fPtr, filename, _T("r, ccs = UNICODE")); // 파일 열기

#else // 멀티바이트일 경우
    _tfopens(&fPtr, filename, _T("r"); // 파일 열기
#endif
    while (_fgetts(buffer, 100, fPtr) != NULL) 
    {
        // 파일의 끝을 만날 때까지 줄 단위로 버퍼에 읽어들임, 
        // 버퍼의 마지막 문자가 newline이면 이것을 null로 변경한 후 윈도우에 출력
        if (buffer[_tcsclen(buffer) - 1] == _T('\n'))
            buffer[_tcslen(buffer) - 1] = NULL;
        TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
        line++;
    }
    fclose(fPtr);
    ReleaseDC(hwnd, hdc);
}


// << : bitmap
void CreateBitmap() 
{
    // : for bitblt
    hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/수지.bmp"), 
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    GetObject(hBackImage, sizeof(BITMAP), &bitBack);

    // : for trans...bit
    hSigongImage = (HBITMAP)LoadImage(NULL, TEXT("images/sigong.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hSigongImage, sizeof(BITMAP), &bitSigong);

    // : for Animation
    hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/zero_run.bmp"),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(hAniImage, sizeof(BITMAP), &bitAni);

    Run_Frame_Max = bitAni.bmWidth / Sprite_Size_X - 1;
    Run_Frame_Min = 2;
    curFrame = Run_Frame_Min;
}

void DrawBitmap(HWND hWnd, HDC hdc)
{
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;


    // SUJI
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);
    bx = bitBack.bmWidth;
    by = bitBack.bmHeight;

    BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY); // 윈도우 창에서 이미지가 그려질 원점 세팅 / 가져올 이미지 소스의 원점 세팅 / 일반적 그림
    StretchBlt(hdc, 900, 0, 200, 200, hMemDC, 0, 0, bx, by, SRCCOPY); // 이미지 소스 비율 세팅 해서 그림
    
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);


    // Sigong
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hSigongImage);
    bx = bitSigong.bmWidth;
    by = bitSigong.bmHeight;

    TransparentBlt(hdc, 200, 200, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255)); // 분홍색 빼기

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);



    // for : Animation
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);
    bx = bitAni.bmWidth / 16; //개별 사이즈
    by = bitAni.bmHeight / 2; // 개별사이즈

    int xStart = curFrame * bx;// 위치값
    int yStart = 0;

    TransparentBlt(hdc, 200, 400, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255)); // 분홍색 빼기

    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}

void DeleteBitmap()
{
    DeleteObject(hBackImage);
    DeleteObject(hSigongImage);
    DeleteObject(hAniImage);
}

// >> : bitmap

void UpdateFrame(HWND hWnd)
{
    curFrame++;
    if (curFrame > Run_Frame_Max)
        curFrame = Run_Frame_Min;
}

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    UpdateFrame(hWnd);
    InvalidateRect(hWnd, NULL, false);
}


VOID CALLBACK keyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    if (GetKeyState('A') & 0x8000) // A키가 눌렸는지 검사
    {
        wsprintf(sKeyState, TEXT("%s"), _T("A-key pressed"));
    }
    else if (GetKeyState('D') & 0x8000)
    {
        wsprintf(sKeyState, TEXT("%s"), _T("D-key pressed"));
    }
    else
    {
        wsprintf(sKeyState, TEXT("%s"), _T(" "));
    }
}

void Update()
{
    DWORD newTime = GetTickCount();
    static DWORD oldTime = newTime;
    if (newTime - oldTime < 100)
        return;
    oldTime = newTime;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        ptAni.x += 10;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        ptAni.x -= 10;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        ptAni.y -= 10;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        ptAni.y += 10;
    }
}

BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (iMsg)
    {
    case WM_INITDIALOG:
        {
            HWND hBtn = GetDlgItem(hDlg, IDC_PAUSE);
            EnableWindow(hBtn, FALSE); // 처음 생성시 중지 버튼은 비활성화 상태
        }
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_COPY:
            {
                TCHAR word[128];

                GetDlgItemText(hDlg, IDC_EDIT_SOURCE, word, 128); // 문자열을 가져옴 // 아이디 비번 가져오기 같은 기능
                SetDlgItemText(hDlg, IDC_EDIT_COPY, word);

            }
            break;

        case IDC_BUTTON_CLEAR:
            {
                SetDlgItemText(hDlg, IDC_EDIT_SOURCE,_T(""));
                SetDlgItemText(hDlg, IDC_EDIT_COPY, _T(""));
            }
            break;

        case IDC_START:
            {
                HWND hBtn = GetDlgItem(hDlg, IDC_START);
                EnableWindow(hBtn, FALSE); 

                hBtn = GetDlgItem(hDlg, IDC_PAUSE);
                EnableWindow(hBtn, TRUE); 

                SetDlgItemText(hDlg, IDC_TEXT, _T("시작됐어요"));
            }
            break;

        case IDC_PAUSE:
            {
                HWND hBtn = GetDlgItem(hDlg, IDC_START);
                EnableWindow(hBtn, TRUE);

                hBtn = GetDlgItem(hDlg, IDC_PAUSE);
                EnableWindow(hBtn, FALSE);

                SetDlgItemText(hDlg, IDC_TEXT, _T("중지됐어요"));
            }
            break;
        case IDC_CLOSE :
            {

                HWND hBtn = GetDlgItem(hDlg, IDC_START);
                EnableWindow(hBtn, TRUE);

                hBtn = GetDlgItem(hDlg, IDC_PAUSE);
                EnableWindow(hBtn, FALSE);

                SetDlgItemText(hDlg, IDC_TEXT, _T("종료됐어요"));

                return TRUE;
            }
            break;
        case IDC_BUTTON_PRINT:
            {
                HDC hdc = GetDC(hDlg);
                TextOut(hdc, 10, 10, _T("Hello Button!!"), 14);
                SetDlgItemText(hDlg, IDC_TEXT, _T("Hello Button!!"));
                ReleaseDC(hDlg, hdc);
                break;
            }
        case IDOK:
            {
                break;
            }
        case IDCANCEL:
            {
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
                break;
            }
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void DrawRectText(HDC hdc) // 텍스트 출력
{
    static int yPos = 0;
    TCHAR strTest[] = _T("내려갑니다~");
    TextOut(hdc, 10, yPos, strTest, _tcslen(strTest));
    yPos += 5;
    if (yPos > rcClient.bottom) // 텍스트가 윈도우 창 아래로 내려간다면 위치값 다시 위로 세팅 
        yPos = 0;

    TextOut(hdc, 50, 10, sKeyState, _tcsclen(sKeyState));
}

void DrawBitMapDoubleBuffering(HWND hWnd, HDC hdc)
{
 
    HDC hMemDC;
    HBITMAP hOldBitmap;
    int bx, by;

    HDC hMemDC2;
    HBITMAP hOldBitmap2;

    hMemDC = CreateCompatibleDC(hdc);

    if (hDoubleBufferImage == NULL)
        hDoubleBufferImage = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom); // 더블 버퍼링용 이미지 생성

    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

    // for : backImage
    {
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);

        bx = bitBack.bmWidth;
        by = bitBack.bmHeight;

        BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY); // 윈도우 창에서 이미지가 그려질 원점 세팅 / 가져올 이미지 소스의 원점 세팅 / 일반적 그림
        StretchBlt(hMemDC, 900, 0, 200, 200, hMemDC2, 0, 0, bx, by, SRCCOPY); // 이미지 소스 비율 세팅 해서 그림

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // for : sigong
    {
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hSigongImage);
        bx = bitSigong.bmWidth;
        by = bitSigong.bmHeight;

        TransparentBlt(hMemDC, 200, 200, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255)); // 분홍색 빼기

        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // for : Animation
    {
        hMemDC2 = CreateCompatibleDC(hMemDC);
        hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage);
        bx = bitAni.bmWidth / 16; //개별 사이즈
        by = bitAni.bmHeight / 2; // 개별사이즈

        int xStart = curFrame * bx;// 위치값
        int yStart = 0;

        TransparentBlt(hMemDC, ptAni.x, ptAni.y, bx, by, 
            hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255)); // 분홍색 빼기

        TransparentBlt(hMemDC, 900, 400, bx, by, 
            hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255)); 


        xStart = Run_Frame_Max * bx - xStart;
        yStart = by;
        TransparentBlt(hMemDC, ptAni.x, ptAni.y + 50, bx, by, 
            hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255)); 


        SelectObject(hMemDC2, hOldBitmap2);
        DeleteDC(hMemDC2);
    }

    // Gdi
    Gdi_Draw(hMemDC);
    // Gdi

    BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hMemDC, 0, 0, SRCCOPY);

    SelectObject(hMemDC, hOldBitmap);

    DeleteDC(hMemDC);
}


void Gdi_Init()
{
    GdiplusStartupInput gpsi;
    GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}

void Gdi_Draw(HDC hdc)
{
    Graphics graphics(hdc);
    // >> : txt
    SolidBrush brush(Color(255, 255, 0, 0));
    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, 100, FontStyleRegular, UnitPixel);
    PointF pointF(10.0f, 20.0f);
    graphics.DrawString(L"배고프다 배고파!", -1, &font, pointF, &brush);
    // << : txt

    Pen pen(Color(255, 0, 255, 255));
    graphics.DrawLine(&pen, 0, 0, 300, 300);

    // >> : image
    Image img((WCHAR*)L"images/sigong.png");
    int w = img.GetWidth();
    int h = img.GetHeight();

    graphics.DrawImage(&img, 275, 30, w, h);
    // << : image

    // >> : ani
    Image img2((WCHAR*)L"images/zero_run.png");
    w = img2.GetWidth() / 16;
    h = img2.GetHeight() / 2;

    int xStart = curFrame * w;
    int yStart = 0;

    ImageAttributes imgAttr;
    imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
    graphics.DrawImage(&img2, Rect(400, 100, w, h), xStart, yStart, w, h, UnitPixel, &imgAttr);
    // << : ani


    // >> : alpha rect..
    brush.SetColor(Color(128, 255, 0, 0));
    graphics.FillRectangle(&brush, 400, 100, w, h);
    // << 


    // >> : rotation image


    
    Image* pImg = nullptr;
    pImg = Image::FromFile((WCHAR*)L"Images/sigong.png");
    int xPos = 300;
    int yPos = 200; // 회전의 중심 좌표
    if (pImg) // nullcheck 필수!
    {
        w = pImg->GetWidth();
        h = pImg->GetHeight();

        Gdiplus::Matrix mat; // 행렬
        static int rot = 0;

        mat.RotateAt((rot % 360), Gdiplus::PointF(xPos + (float)(w / 2), yPos + (float)(w / 2))); // 앵글, 중점 

        graphics.SetTransform(&mat);
        graphics.DrawImage(pImg, xPos, yPos, w, h);

        rot += 10;

        // 회전후 초기화 필수!
        mat.Reset();
        graphics.SetTransform(&mat);

        // >> : alpha image
        REAL transparency = 0.5;
        ColorMatrix colorMatrix =
        {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, transparency, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        };

        imgAttr.SetColorMatrix(&colorMatrix);
        xPos = 400;
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h),  // dest doord
            0, 0, w, h, // source doord
            UnitPixel, &imgAttr);

        // gray
        ColorMatrix grayMatrix =
        {
            0.3f, 0.3f, 0.3f, 0.0f, 0.0f,
            0.6f, 0.6f, 0.6f, 0.0f, 0.0f,
            0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        };
        imgAttr.SetColorMatrix(&grayMatrix);
        xPos = 500;
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);



        xPos = 600;
        pImg->RotateFlip(RotateNoneFlipX); // 플립
        graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

        delete pImg;
    }
    // <<


 
}

void Gdi_End()
{
    GdiplusShutdown(g_GdiToken);
}