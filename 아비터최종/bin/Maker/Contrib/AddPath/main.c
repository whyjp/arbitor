////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// 설치 프로그램을 맨위로 올리기위한 플러그인.
///
/// 사용법 : 
/*

	ReserveFile	"${NSISDIR}\Plugins\AlwaysOnTop.dll"							; solid compressing 을 위한 file reserve
	NSISAutoSetupPlugin::SetAlwaysOnTop 


*/
/// 
/// @author   hardkoder@gmail.com
/// @date     2005/02/25
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "exdll.h"

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL WINAPI DllMain(HANDLE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

void __declspec(dllexport) SetAlwaysOnTop(HWND hwndParent, int string_size, 
                                      char *variables, stack_t **stacktop)
{
	EXDLL_INIT();

	// SET TOP MOST
	SetWindowPos(hwndParent, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
}


