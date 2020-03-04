#include "EditManager.h"

CEditManager::CEditManager(void)
{
}

CEditManager::~CEditManager(void)
{
}

CEditManager & CEditManager::GetManager(void)
{
	static CEditManager manager;
	return manager;
}

void CEditManager::Initailize(void)
{
	CRectangle rect = theAreaManager.GetRect(CAreaManager::AREA_EDIT);
	CControll::CreateInfo info = {
		Vector2(rect.Left + Margin, rect.Top + Margin),
		Vector2(200, 32),
		"",
	};
	m_tbName.FontCreate(24, "");
	m_tbName.SetInfo(info);
	m_tbName.Initialize();

	info.Pos.y += info.Size.y + Margin;
	info.Size.x = 100;
	info.Text = "OffsetX";
	m_lblOffSetX.FontCreate(24, "");
	m_lblOffSetX.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	info.Text = "OffsetY";
	m_lblOffSetY.FontCreate(24, "");
	m_lblOffSetY.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	info.Text = "Width";
	m_lblWidth.FontCreate(24, "");
	m_lblWidth.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	info.Text = "Height";
	m_lblHeight.FontCreate(24, "");
	m_lblHeight.SetInfo(info);

	info.Text = "0";
	info.Pos.y = m_lblOffSetX.GetPos().y;
	info.Pos.x += info.Size.x + 20;
	info.Size.x = 80;
	m_nbOffSetX.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	m_nbOffSetY.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	m_nbWidth.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	m_nbHeight.SetInfo(info);

	info.Text = "ループ";
	info.Pos.x = m_lblOffSetX.GetPos().x;
	info.Pos.y += info.Size.y + Margin;
	info.Size.x = 140;
	m_cbLoop.FontCreate(24, "");
	m_cbLoop.SetInfo(info);
	m_cbLoop.SetFontSize(24);
	info.Text = "再生";
	info.Pos.x += info.Size.x;
	info.Size.x = 60;
	m_btnPlay.FontCreate(24, "");
	m_btnPlay.SetInfo(info);

	info.Text = "コマ数";
	info.Pos.y += info.Size.y + Margin;
	info.Pos.x = m_tbName.GetPos().x;
	info.Size.x = 80;
	m_lblComa.FontCreate(24, "");
	m_lblComa.SetInfo(info);
	info.Pos.x += info.Size.x + 40;
	info.Size.x = 80;
	m_nbComa.SetInfo(info);

	info.Pos.x = m_tbName.GetPos().x;
	info.Pos.y += info.Size.y + Margin;
	info.Size.x = 120;
	info.Text = "0";
	m_nbAllFlame.SetInfo(info);
	CControll::CreateInfo ci = {
		info.Pos + Vector2(0, -12),
		Vector2(200, 12),
		"フレーム一括変更"
	};
	m_lblAllFlame.FontCreate(12, "");
	m_lblAllFlame.SetInfo(ci);

	info.Pos.x += info.Size.x + 20;
	info.Size.x = 60;
	info.Text = "変更";
	m_btnChange.FontCreate(24, "");
	m_btnChange.SetInfo(info);

	info.Pos.y += info.Size.y + Margin;
	info.Pos.x = m_tbName.GetPos().x;
	info.Size.x = 32;
	info.Text = "";
	m_btnPrev.FontCreate(24, "");
	m_btnPrev.Load("btnicon/PreviousFrame_16x.png");
	m_btnPrev.SetInfo(info);
	info.Pos.x = m_tbName.GetRect().Right - 32;
	m_btnNext.FontCreate(24, "");
	m_btnNext.Load("btnicon/NextFrameArrow_16x.png");
	m_btnNext.SetInfo(info);
	info.Pos.x = m_btnPrev.GetRect().Right + 20;
	info.Size.x = 96;
	info.Text = "コマ:0";
	m_lblNowComa.FontCreate(24, "");
	m_lblNowComa.SetInfo(info);

	info.Pos.y += info.Size.y + Margin;
	info.Pos.x = m_tbName.GetPos().x;
	info.Size.x = 100;
	info.Text = "フレーム";
	m_lblFlame.FontCreate(24, "");
	m_lblFlame.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	info.Text = "No";
	m_lblNo.FontCreate(24, "");
	m_lblNo.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	info.Text = "Step";
	m_lblStep.FontCreate(24, "");
	m_lblStep.SetInfo(info);
	info.Pos.y = m_lblFlame.GetPos().y;
	info.Pos.x += info.Size.x + 20;
	info.Size.x = 80;
	info.Text = "0";
	m_nbFlame.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	m_nbNo.SetInfo(info);
	info.Pos.y += info.Size.y + Margin;
	m_nbStep.SetInfo(info);

	info.Pos.x = m_tbName.GetRect().Right + Margin;
	info.Pos.y = m_tbName.GetPos().y;
	info.Size.x = rect.GetWidth() - (m_tbName.GetRect().GetWidth() + Margin * 3);
	info.Size.y = g_pGraphics->GetTargetHeight() -
		(info.Pos.y + m_nbStep.txtBox.GetRect().GetHeight() + Margin + 16);
	info.Text = "";
	m_lbAnimList.FontCreate(24, "");
	m_lbAnimList.SetInfo(info);
	m_lbAnimList.Initialize();
	AddAnim();
	m_tbName.SetText(m_lbAnimList.GetText());

	info.Pos.x += 14;
	info.Pos.y += info.Size.y + Margin;
	info.Size = Vector2(32, 32);
	m_btnUpList.Load("btnicon/Upload_16x.png");
	m_btnUpList.SetInfo(info);
	info.Pos.x += info.Size.x + Margin;
	m_btnDownList.Load("btnicon/Download_16x.png");
	m_btnDownList.SetInfo(info);
	info.Pos.x += info.Size.x + Margin;
	m_btnAddAnim.Load("btnicon/AddItem_16x.png");
	m_btnAddAnim.SetInfo(info);
	info.Pos.x += info.Size.x + Margin;
	m_btnDeleteAnim.Load("btnicon/DeleteListItem_16x.png");
	m_btnDeleteAnim.SetInfo(info);
}

void CEditManager::Update(void)
{
	m_tbName.Update();
	m_nbOffSetX.Update();
	m_nbOffSetY.Update();
	m_nbWidth.Update();
	m_nbHeight.Update();
	m_cbLoop.Update();
	m_nbComa.Update();
	m_nbAllFlame.Update();
	m_nbFlame.Update();
	m_nbNo.Update();
	m_nbStep.Update();
	m_lbAnimList.Update();

	UpdateList();
}

void CEditManager::Render(void)
{
	m_tbName.Render();
	m_lblOffSetX.Render();
	m_lblOffSetY.Render();
	m_lblWidth.Render();
	m_lblHeight.Render();
	m_nbOffSetX.Render();
	m_nbOffSetY.Render();
	m_nbWidth.Render();
	m_nbHeight.Render();
	m_cbLoop.Render();
	m_btnPlay.Render();
	m_lblComa.Render();
	m_nbComa.Render();
	m_lblAllFlame.Render();
	m_nbAllFlame.Render();
	m_btnChange.Render();
	m_btnPrev.Render();
	m_btnNext.Render();
	m_lblNowComa.Render();
	m_lblFlame.Render();
	m_nbFlame.Render();
	m_lblNo.Render();
	m_nbNo.Render();
	m_lblStep.Render();
	m_nbStep.Render();
	m_lbAnimList.Render();
	m_btnUpList.Render();
	m_btnDownList.Render();
	m_btnAddAnim.Render();
	m_btnDeleteAnim.Render();
}

void CEditManager::Release(void)
{
	m_nbOffSetX.Release();
	m_nbOffSetY.Release();
	m_nbWidth.Release();
	m_nbHeight.Release();
	m_btnPlay.Release();
	m_nbComa.Release();
	m_nbAllFlame.Release();
	m_btnChange.Release();
	m_btnPrev.Release();
	m_btnNext.Release();
	m_nbFlame.Release();
	m_nbNo.Release();
	m_nbStep.Release();
	m_lbAnimList.Release();
	m_btnUpList.Release();
	m_btnDownList.Release();
	m_btnAddAnim.Release();
	m_btnDeleteAnim.Release();
}

void CEditManager::UpdateList(void)
{
	if (m_btnAddAnim.IsPush())
	{
		AddAnim();
	}
	if (m_btnDeleteAnim.IsPush())
	{
		DeleteAnim();
	}
	if (m_btnUpList.IsPush())
	{
		int nowselect = m_lbAnimList.GetSelectNo();
		m_lbAnimList.Swap(nowselect, nowselect - 1);
	}
	if (m_btnDownList.IsPush())
	{
		int nowselect = m_lbAnimList.GetSelectNo();
		m_lbAnimList.Swap(nowselect, nowselect + 1);
	}
}

void CEditManager::AddAnim(void)
{
	m_lbAnimList.Add("NoName");
}

void CEditManager::DeleteAnim(void)
{
	int nowselect = m_lbAnimList.GetSelectNo();
	m_lbAnimList.DeleteNo(nowselect);
}
