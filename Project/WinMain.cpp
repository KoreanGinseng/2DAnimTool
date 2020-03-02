#include	"GameApp.h"
#include	"WindowProc.h"
#include	"resource.h"

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Mof::LPFramework pFrame = new Mof::CDX11GameFramework(); 
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.WindowCreateInfo.Title = "アニメーションエディタ";
	Info.WindowCreateInfo.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_KIRIN));
	Info.WindowCreateInfo.Width = 1280;
	Info.WindowCreateInfo.Height = 720;
	Info.pApplication = new CGameApp();
	Info.WindowCreateInfo.pProc = new CWindowProc();
	if ( pFrame->Initialize(&Info) )
	{
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	return 0;
}