#include <windows.h>

#include <winioctl.h>
#include <winsvc.h>
#include "..\\inc\\4Svc_lib.h"
#include "..\\inc\\F_IFACE.H"

#include "resource.h"
#define TRAY_NOTIFY (WM_APP + 100)
#define RUN_MUTEX "ICANRUNONCE"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("아비터 ext");
SC_HANDLE hScm, hSrv;
SERVICE_STATUS ss;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	HANDLE hMutex;

	hMutex=CreateMutex(NULL,FALSE,RUN_MUTEX);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hMutex);
#ifdef _DEBUG
		MessageBox(NULL, "이미 다른 인스턴스가 실행중입니다.","알림",MB_OK);
#endif
		return 0;
	}

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	//ShowWindow(hWnd,nCmdShow);

	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	CloseHandle(hMutex);
	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	NOTIFYICONDATA nid;
	HMENU hMenu, hPopupMenu;
	POINT pt;

	switch (iMessage) {
	case WM_CREATE:
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hWnd;
		nid.uID = 0;
		nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
		nid.uCallbackMessage = TRAY_NOTIFY;
		nid.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON1));
		lstrcpy(nid.szTip, "아비터 서비스 트레이");
		Shell_NotifyIcon(NIM_ADD, &nid);
		if(Init_SvcOpen(&hScm,&ss)==FALSE){
			MessageBox(hWnd,"서비스를 오픈하지못하였습니다","Service Tray",MB_OK);
			DestroyWindow(hWnd);
		}
		return 0;
	case TRAY_NOTIFY:
		switch (lParam) {
		case WM_LBUTTONDOWN:
			
			break;
		case WM_RBUTTONDOWN:
			hMenu=LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_MENU1));
			hPopupMenu=GetSubMenu(hMenu,0);
			GetCursorPos(&pt);
			SetForegroundWindow(hWnd);
			TrackPopupMenu(hPopupMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | 
				TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
			SetForegroundWindow(hWnd);
			DestroyMenu(hPopupMenu);
			DestroyMenu(hMenu);
			break;
		}
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDM_ABOUT:
			MessageBox(hWnd,"아비터 서비스 트레이",
				"프로그램 소개",MB_OK);
			break;
		case IDM_ALLHIDE:
			{
				RQ_ALL_HIDE(&hScm,&ss);
				nid.cbSize = sizeof(NOTIFYICONDATA);
				nid.hWnd = hWnd;
				nid.uID = 0;
				nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
				nid.uCallbackMessage = TRAY_NOTIFY;
				nid.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON1));
				lstrcpy(nid.szTip, "아비터 서비스 트레이");
				Shell_NotifyIcon(NIM_MODIFY,&nid);
				
			}
			break;
		case IDM_ALLSHOW:
			{
				RQ_ALL_SHOW(&hScm,&ss);
				nid.cbSize = sizeof(NOTIFYICONDATA);
				nid.hWnd = hWnd;
				nid.uID = 0;
				nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
				nid.uCallbackMessage = TRAY_NOTIFY;
				nid.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON2));
				lstrcpy(nid.szTip, "아비터 서비스 트레이");
				Shell_NotifyIcon(NIM_MODIFY,&nid);
			}
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		}
		return 0;
	case WM_PAINT:
		return 0;
	case WM_DESTROY:
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hWnd;
		nid.uID = 0;
		Shell_NotifyIcon(NIM_DELETE, &nid);

		CloseServiceHandle(hScm);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

