////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// NSIS�� �ڵ����� ��ġ�ϱ� ���� �÷�����
///
/// ���� : 
/*
	�ʱ�ȭ �Լ����� 

	SetOutPath $TEMP														; �ӽ� ������ �÷����� ������ 
	File NSISAutoSetupPlugin.dll
	CallInstDLL $TEMP\NSISAutoSetupPlugin.dll /NOUNLOAD StartAutoSetup		; �÷����� ó��



//
// example 
// ���� ������ ��ġ ���α׷� ����� /A �ɼ��� �ָ�
// �ڵ����� �ָ���... ��ġ�Ǵ� ���� �̴�..
//

;;;;;;;;;;;;;;;; ���� ���� ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; �ʱ�ȭ �Լ� 
Function .onInit
	call GetParameters					; ���� �Ķ���� üũ
	call CheckAndRunAutoInstall			; /A �ɼ� ó��
FunctionEnd

; ���� �Ķ���� üũ �Լ� 
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
; /A �ɼ����� �����ϸ�
; �ڵ� ������ ó���Ѵ�.
Function CheckAndRunAutoInstall
	Pop $0
	StrCmp $0 "/A" 0 END
		SetOutPath $TEMP														; �ӽ� ������ �÷����� ������ 
		File NSISAutoSetupPlugin.dll
		CallInstDLL $TEMP\NSISAutoSetupPlugin.dll /NOUNLOAD StartAutoSetup		; �÷����� ó��
	END:
FunctionEnd


;;;;;;;;;;;;;;;; ���� �� ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


*/
/// 
/// @author   koder@popdesk.co.kr
/// @date     2004-01-12 ���� 3:16:51
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

	// Ÿ�̸� ����
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

	// ������ OK ��ư�� ���� �ش�..
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
