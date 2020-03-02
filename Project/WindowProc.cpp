#include "WindowProc.h"
#include "Mof.h"
#include "resource.h"

CWindowProc::CWindowProc(void)
{
}

CWindowProc::~CWindowProc(void)
{
}

MofProcResult CWindowProc::WindowProc(MofWindowHandle hWnd, MofUInt msg, MofProcParamW wpar, MofProcParamL lpar)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		//メニューの設定
		SetMenu(hWnd, LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1)));
		int w = 1280 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
		int h = 720 + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + 
			GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
		SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);
		break;
	}
	case WM_COMMAND:
		switch(DWORD(wpar))
		{
		case ID_APPEND:
			PostQuitMessage(0);
			break;
		case ID_VERSION:
			ShellAbout(hWnd, "アニメーションエディタ", "OIC", NULL);
			break;
		default:
			break;
		}
		break;
	default:
		return CImeProc::WindowProc(hWnd, msg, wpar, lpar);
	}
	return DefWindowProc(hWnd, msg, wpar, lpar);
}

MofS32 CWindowProc::GetInsertPoint(void)
{
	return m_InsertPoint;
}
