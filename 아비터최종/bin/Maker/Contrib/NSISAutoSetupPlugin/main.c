////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// NSIS를 자동으로 설치하기 위한 플러그인
///
/// 사용법 : 
/*
	초기화 함수에서 

	SetOutPath $TEMP														; 임시 폴더에 플러그인 복사후 
	File NSISAutoSetupPlugin.dll
	CallInstDLL $TEMP\NSISAutoSetupPlugin.dll /NOUNLOAD StartAutoSetup		; 플러그인 처리



//
// example 
// 다음 예제는 설치 프로그램 실행시 /A 옵션을 주면
// 자동으로 주르륵... 설치되는 예제 이다..
//

;;;;;;;;;;;;;;;; 예제 시작 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; 초기화 함수 
Function .onInit
	call GetParameters					; 실행 파라메터 체크
	call CheckAndRunAutoInstall			; /A 옵션 처리
FunctionEnd

; 실행 파라메터 체크 함수 
Function GetParameters
	Push $R0
	Push $R1
	Push $R2
	Push $R3
	StrCpy $R2 1
	StrLen $R3 $CMDLINE
	;Check for quote or space
	StrCpy $R0 $CMDLINE $R2
	StrCmp $R0 '"' 0 +3
		StrCpy $R1 '"'
		Goto loop
	StrCpy $R1 " "
	loop:
		IntOp $R2 $R2 + 1
		StrCpy $R0 $CMDLINE 1 $R2
		StrCmp $R0 $R1 get
		StrCmp $R2 $R3 get
		Goto loop
   
	get:
		IntOp $R2 $R2 + 1
		StrCpy $R0 $CMDLINE 1 $R2
		StrCmp $R0 " " get
		StrCpy $R0 $CMDLINE "" $R2
	Pop $R3
	Pop $R2
	Pop $R1
	Exch $R0
FunctionEnd

;----------------------------------------------------------------------------------------
; /A 옵션으로 실행하면
; 자동 실행을 처리한다.
Function CheckAndRunAutoInstall
	Pop $0
	StrCmp $0 "/A" 0 END
		SetOutPath $TEMP														; 임시 폴더에 플러그인 복사후 
		File NSISAutoSetupPlugin.dll
		CallInstDLL $TEMP\NSISAutoSetupPlugin.dll /NOUNLOAD StartAutoSetup		; 플러그인 처리
	END:
FunctionEnd


;;;;;;;;;;;;;;;; 예제 끝 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


*/
/// 
/// @author   koder@popdesk.co.kr
/// @date     2004-01-12 오후 3:16:51
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "exdll.h"

HINSTANCE	g_hInstance = NULL;
HWND		g_hNsisDlg = NULL;
#define		MyWindowClass	"NSIS AUTO SETUP PLUGIN WINDOW"

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL WINAPI DllMain(HANDLE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
	g_hInstance=hInst;
	return TRUE;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= 0;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= MyWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}




void __declspec(dllexport) StartAutoSetup(HWND hwndParent, int string_size, 
                                      char *variables, stack_t **stacktop)
{
	HWND hWnd;

	EXDLL_INIT();

	
	MyRegisterClass(g_hInstance);
	hWnd = CreateWindow(MyWindowClass, "", WS_CHILD, 0, 0, 0, 0, hwndParent, NULL, g_hInstance, NULL);

	// 타이머 세팅
	SetTimer(hWnd, 1, 100, NULL);
	g_hNsisDlg = hwndParent;

	/*
	char temp[64];
	wsprintf(temp,"%d",ret);
	pushstring(temp);
	*/
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{

	// 강제로 OK 버튼을 눌러 준다..
	case WM_TIMER :
		{
			HWND hWndOK = GetDlgItem(g_hNsisDlg, IDOK);
			if(hWndOK)
			{
				if(IsWindowEnabled(hWndOK))
				{
					PostMessage(g_hNsisDlg, WM_COMMAND, IDOK, 0);
				}
			}
		}
		break;

	case WM_DESTROY:
		//MessageBox(hWnd, "WM_DESTORY", "", MB_OK);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
