/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"ToolControll.h"

CButton		gBtn;
CLabel		gLbl;
CCheckBox	gCB;
CScrollBar  gSB;
CListBox	gLB;
CTextBox    gTB1;
CTextBox    gTB2;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	CControll::CreateInfo bc = {
		Vector2(100,100),
		Vector2(100,100),
		"btn"
	};
	CControll::CreateInfo lc = {
		Vector2(400,100),
		Vector2(100,24),
		"lbl"
	};
	CControll::CreateInfo cbc = {
		Vector2(400,200),
		Vector2(150,24),
		"CheckBox"
	};
	CControll::CreateInfo sbc = {
		Vector2(600,100),
		Vector2(150,500),
		""
	};
	CControll::CreateInfo lbc = {
		Vector2(600,100),
		Vector2(150,500),
		""
	};
	CControll::CreateInfo tbc1 = {
		Vector2(100,300),
		Vector2(150,24),
		""
	};
	CControll::CreateInfo tbc2 = {
		Vector2(100,400),
		Vector2(150,24),
		""
	};
	gBtn.FontCreate(24, "");
	gBtn.SetInfo(bc);
	gLbl.FontCreate(24, "");
	gLbl.SetInfo(lc);
	gCB.FontCreate(24, "");
	gCB.SetInfo(cbc);
	
	gSB.FontCreate(24, "");
	gSB.SetInfo(sbc);
	gSB.SetWidth(20);
	gSB.SetScrlArea(gSB.GetRect(), 10000);
	gSB.Initialize();
	gSB.SetShow(FALSE);

	gLB.SetInfo(lbc);
	gLB.Initialize();

	gTB1.FontCreate(24,"");
	gTB2.FontCreate(24,"");
	gTB1.SetInfo(tbc1);
	gTB2.SetInfo(tbc2);
	gTB1.Initialize();
	gTB2.Initialize();
	gTB2.SetNumOnly(TRUE);


	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();
	CTextBox::RefreshImeInput();

	gCB.Update();
	gSB.Update();
	gTB1.Update();
	gTB2.Update();

	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		gSB.ChangeMaxSize(1000);
	}
	if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		gSB.ChangeMaxSize(100000);
	}
	if (g_pInput->IsKeyPush(MOFKEY_3))
	{
		gLB.Add();
	}
	if (g_pInput->IsKeyPush(MOFKEY_4))
	{
		gLB.Delete();
	}
	if (g_pInput->IsKeyPush(MOFKEY_5))
	{
		gLB.DeleteFast();
	}
	if (g_pInput->IsKeyPush(MOFKEY_6))
	{
		gLB.AddFast("str");
		gLB.AddLast("rts");
	}
	if (g_pInput->IsKeyPush(MOFKEY_7))
	{
		int idx = gLB.GetSelectNo();
		gLB.Swap(idx, idx + 1);
	}
	if (gBtn.IsPush())
	{
		gTB2.AddNum(10);
	}
	if (gBtn.IsHold())
	{
		gTB2.AddNum(0.2f);
	}
	if (gBtn.IsPull())
	{
		gTB2.SubNum(10);
	}

	gLB.Update();
	
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	gBtn.Render();
	gLbl.Render();
	gCB.Render();
	gSB.Render();
	gLB.Render();
	gTB1.Render();
	gTB2.Render();
	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	gSB.Release();
	gLB.Release();
	CTextBox::ReleaseList();
	return TRUE;
}