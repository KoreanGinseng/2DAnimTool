#include "WindowProc.h"

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
		break;
	case WM_COMMAND:
		switch(DWORD(wpar))
		{

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
