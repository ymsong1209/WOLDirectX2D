// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "Client.h"

//#include <StaticLib\math.h>
//#pragma comment(lib, "StaticLib//StaticLib_d.lib")
//
////dll 암시적 링크
//#include <DynamicLib\math_dll.h>
////암시적 링크하려면 pragma 풀기
//#pragma comment(lib, "DynamicLib//DynamicLib_d.lib")

//Engine이 build되고 Client가 빌드되어야함, 프로젝트사이의 종속성이 중요
//client->빌드 종속성->빌드 순서
//Engine Library

#include <Engine\CDevice.h>
#include <Engine/CKeyMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CTimeMgr.h>

#include "CEditorObjMgr.h"

// ImGui
#include "ImGuiMgr.h"

#include "TestLevel.h"
#include "TestBoss.h"


//명시적 링크함수포인터
typedef int (*FUNC_TYPE)(int, int);
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //int a = Add(10, 100);
    //int b = Mul(100, 200);


    //Dll 명시적 링크
   /* wchar_t path[256] = L"";
    GetCurrentDirectory(256,path);
    HMODULE hModule = LoadLibrary(L"..//bin_d//DynamicLib_d.dll");*/

   /*
   * 명시적으로 함수를 일일이 가져오려면 GetProcAddress를 써야하고 함수이름을 찾아야한다. 리턴값은 함수포인터.
   * 헤더를 알고 있기 때문에 .dll에 f12를 하면 함수포인터 형식을 알 수가 있다.
    하지만, Engine 헤더를 수정할때마다 매번 include폴더에 복사하는 과정이 너무 귀찮다.
   * EngineCopy.bat 프로그램으로 Engine에서 만든 헤더 파일을 자동으로 Client의 Include로 복사하자.
   * Engine->빌드이벤트->빌드 전 이벤트->명령줄
   */
   /* FUNC_TYPE MulFunc = (FUNC_TYPE)GetProcAddress(hModule, "Mul");
    int c = MulFunc(100, 2);

    if (nullptr != hModule) {
        FreeLibrary(hModule);
    }*/


    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(5774);
    

    
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //CEngine 초기화
    if (FAILED(CEngine::GetInst()->init(g_hWnd, 1600, 900)))
    {
        return 0;
    }

    //ShowCursor(false);

 
    // ImGui 초기화
    ImGuiMgr::GetInst()->init(g_hWnd);

    // Editor 초기화
    CEditorObjMgr::GetInst()->init();

    CreateTestLevel();
    CreateTestBossLevel();

    //LoadLevel();

   
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        else
        {
            CEngine::GetInst()->progress();
            /*if (KEY_TAP(KEY::F8)) {
                CTimeMgr::GetInst()->SetTimeScale(1.f);
                CLevelMgr::GetInst()->GetCurLevel()->ChangeState(LEVEL_STATE::PLAY);
            }*/
           
            CEditorObjMgr::GetInst()->progress();

            ImGuiMgr::GetInst()->progress();
       
            //렌더 종료
            //물체를 다 그리고 나서 backbuffer, frontbuffer교체
            CDevice::GetInst()->Present();
        }
    }


    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;//MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = L"MyWindow";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(L"MyWindow", L"MyGame", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   // ShowWindow(hWnd, nCmdShow)를 하면 조그만한 창이 만들어지고 engine에서 거대한 창을 덮어씌운다.
   // main에서는 아예 창을 만들지 말고 engine에서 창을 만들게 하자.
   ShowWindow(g_hWnd, false);
   UpdateWindow(g_hWnd);

   return TRUE;
}



// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
