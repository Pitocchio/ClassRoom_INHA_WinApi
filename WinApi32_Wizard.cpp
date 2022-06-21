#include "framework.h"
#include "WinApi32_Wizard.h"
#include <cmath>
const double PI = 3.14159265358979323;


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

static TCHAR str[256]; // 1 메시지 처리후 데이터를 잃지 않기 위해 static
static int count, yPos; // 
static SIZE size; // 1030 캐럿

// 전방 선언: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void TextOut_Test(HDC hdc); // 텍스트 출력 함수
void DrawLine_Test(HDC hdc); // 직선 그리기 함수
void DrawGrid_Test(HDC hdc, POINT LeftTop, POINT RightBottom, LONG nWidth, LONG nHeight); // 격자무늬 그리기
void DrawCircle_Test(HDC hdc, POINT center, int radius);
void DrawRectangle_Test(HDC hdc);
void DrawPolygon_Test(HDC hdc);
void DrawSunFlower_Test(HDC hdc, POINT center, int radius, int num);
void DrawStar_Test(HDC hdc, POINT center, int distance, int num);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 메인 함수
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
    if (!InitInstance (hInstance, nCmdShow))
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

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance) // c_ 윈도우 기본 설정 
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI32WIZARD)); // 아이콘 설정
    wcex.hCursor        = LoadCursor(nullptr, IDC_IBEAM); // 커서 설정 
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);// (COLOR_WINDOW+1); // 배경색 설정 
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI32WIZARD); // NULL; 처리하면 위 상단바 없어짐
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); 
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
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

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//







LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // wParm : 눌린 키에 대한 데이터, lParm: 반복 횟수? 기타 정보
{
    

    switch (message)
    {
    case WM_CREATE: // 1028 엔터 키
        count = 0;
        yPos = 120;

        CreateCaret(hWnd, NULL, 10, 15); // 캐럿 생성
        ShowCaret(hWnd); // 캐럿 보이기

        break;
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

    // 키보드 인풋 처리
    case WM_KEYDOWN: // ch_눌렸을 때
        {
            int breakpoint = 999;
        }
        break;
    case WM_CHAR: // ch_문자를 눌렀을 때 + 문자열 출력
        {
           
            
            
   
            if (wParam == VK_BACK && count > 0) // 1026 백스페이스 처리
                count--; 
            else if (wParam == VK_RETURN) // 엔터 처리
                yPos += 20;  
            else  // 키보드 입력 문자를 출력(이어서)
                str[count++] = wParam; 

            str[count] = NULL;

            InvalidateRect(hWnd, NULL, TRUE);
           
        }
        break;
    case WM_KEYUP: // ch_눌렀다 땠을 때
        {
            int breakpoint = 999;
        }
        break;

    case WM_PAINT: // c_글자출력이나 글씨를 쓰거나 다 여기서!!!!
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); // 그리기 시작 포인트





            // 텍스트 출력
            //TextOut_Test(hdc); 

            // 직선 그리기 
            //DrawLine_Test(hdc);
            
            // 격자무늬 그리기
           /* POINT LeftTop = tagPOINT{ 100, 100 };
            POINT RightBottom = tagPOINT{ 500, 500 };
            DrawGrid_Test(hdc, LeftTop, RightBottom, 10, 10); */


            {
                // 펜 관련 함수
                HPEN hPen, oldPen; // 펜의 속성을 다루기 위해 펜을 생성
                hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 펜의 타입(p.86), 굵기, 컬러
                oldPen = (HPEN)SelectObject(hdc, hPen); // 펜에 대한 정보를 넘겨줌 

                // 타원 그리기
                POINT iCenter = tagPOINT{ 300, 300 };
                int iRadius = 100;
                int iNum = 8;
                // DrawSunFlower_Test(hdc, iCenter, iRadius, iNum);

                
                // 펜 관련 함수
                SelectObject(hdc, oldPen); //이전 펜으로 돌아감
                DeleteObject(hPen); // 삭제
            }


            {
                // 면 색 관련 함수 (컬러 색)
                HBRUSH hBrush, oldBrush;
                hBrush = CreateSolidBrush(RGB(0, 255, 0)); // 세세하게 컬러 지정 가능 
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

                //DrawRectangle_Test(hdc);
                
                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);
            }


            {
                // 면 색 관련 함수 (투명 색)
                HBRUSH hBrush, oldBrush;
                hBrush = (HBRUSH)GetStockObject(NULL_BRUSH); // NULL_BRUSH = 투명 + 기본 컬러
                oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

                //DrawPolygon_Test(hdc);
                POINT iCenter = tagPOINT{ 300, 300 };
                DrawStar_Test(hdc, iCenter, 100, 5);

                SelectObject(hdc, oldBrush);
                DeleteObject(hBrush);
            }






            EndPaint(hWnd, &ps); // 그리기 끝 포인트
        }
        break;
    case WM_DESTROY: // 소멸자 역할
        HideCaret(hWnd); // or Destroy : 감추기 - 파괴하기
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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





void TextOut_Test(HDC hdc) // 텍스트 출력
{
    // 기본 텍스트 출력 함수 (1) : TextOut() p.54 : 한 점의 좌표를 기준으로 출력
    TextOut(hdc, 100, 100, _T("<AMAZONE EXPRESS>"), _tcslen(_T("<AMAZONE EXPRESS>"))); 


    // 기본 텍스트 출력 함수 (2) : DrawText() p.56 : 박스 영역을 지정하고 출력 
    SetTextColor(hdc, RGB(0, 0, 255));
    RECT rc; // 박스 구조체
    rc.left = 300;
    rc.top = 100;
    rc.right = 500;
    rc.bottom = 300;
    DrawText(hdc, _T("윈도우 윈도우 윈도우"), _tcslen(_T("윈도우 윈도우 윈도우")), &rc, DT_LEFT); // 정렬 타입 선택 가능 p.57

    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

    // 키보드 인풋 출력
    SetTextColor(hdc, RGB(255, 0, 0));
    TextOut(hdc, 100, yPos, str, _tcslen(str)); // 1026, 1028

    GetTextExtentPoint(hdc, str, _tcslen(str), &size); // 문자열 크기 측정 함수 p.75

    SetCaretPos(size.cx + 100, yPos); // 캐럿 위치 설정 p.74
}

void DrawLine_Test(HDC hdc) // 직선 그리기
{
    MoveToEx(hdc, 100, 100, NULL);
    LineTo(hdc, 500, 100);

    MoveToEx(hdc, 500, 100, NULL);
    LineTo(hdc, 500, 500);

    MoveToEx(hdc, 500, 500, NULL);
    LineTo(hdc, 100, 500);

    MoveToEx(hdc, 100, 500, NULL);
    LineTo(hdc, 100, 100);
}

void DrawGrid_Test(HDC hdc, POINT LeftTop, POINT RightBottom, LONG nWidth, LONG nHeight) // 격자무늬 그리기
{
    
    for (LONG i = 0; i + LeftTop.y <= RightBottom.y; i += nHeight)
    {
        MoveToEx(hdc, LeftTop.x, LeftTop.y + i, NULL);
        LineTo(hdc, RightBottom.x, LeftTop.y + i);
    }

    for (LONG i = 0; i + LeftTop.x <= RightBottom.x; i += nWidth)
    {
        MoveToEx(hdc, LeftTop.x + i, LeftTop.y, NULL);
        LineTo(hdc, LeftTop.x + i, RightBottom.y);
    }
}

void DrawCircle_Test(HDC hdc, POINT center, int radius)
{
    Ellipse(hdc, center.x-radius, center.y-radius, center.x + radius, center.y + radius);
}

void DrawSunFlower_Test(HDC hdc, POINT center, int radius, int num)
{
    DrawCircle_Test(hdc, center, radius);
    double angle;
    angle = 2 * PI / num; // 갯수 구하기

    double r;
    r = (radius * sin(angle / 2)) / (1 - sin(angle / 2));

    double distance = r + radius;
    POINT MovePoint;


    for (int i = 0; i < num; i++)
    {
        MovePoint.x = center.x + distance * cosf(angle * i); 
        MovePoint.y = center.y + distance * sinf(angle * i); 
        DrawCircle_Test(hdc, MovePoint, r);
    }
}

void DrawRectangle_Test(HDC hdc)
{
    Rectangle(hdc, 500, 300, 700, 500);
}

void DrawPolygon_Test(HDC hdc)
{
    POINT point[5] = { {10, 150}, {250, 30}, {500, 150}, {350, 300}, {150, 300} };
    Polygon(hdc, point, 5);
}

void DrawStar_Test(HDC hdc, POINT center, int distance, int num)
{
    POINT *arr = new POINT[num];

    double angle;
    angle = 2 * PI / num;  
    POINT MovePoint;

    DrawCircle_Test(hdc, center, 3); // 원점

    for (int i = 0; i < num; ++i)
    {
        MovePoint.x = center.x + distance * cosf(angle * i); 
        MovePoint.y = center.y + distance * sinf(angle * i);

        arr[i] = MovePoint;
        
        
        DrawCircle_Test(hdc, MovePoint, 3); // 꼭짓점
    }

   

    Polygon(hdc, arr, num);

    delete [] arr;

}
