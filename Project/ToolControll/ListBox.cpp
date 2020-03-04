#include "ListBox.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CListBox::CListBox(void) :
		CControll(),
		m_pTemplate(nullptr),
		m_pScrollBar(nullptr),
		m_List(),
		m_Select(-1),
		m_PrevSelect(-1)
	{
		m_BackColor = MOF_COLOR_WHITE;
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CListBox::~CListBox(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// リストボックスの生成
	/// </summary>
	/// <returns>リストボックスのポインタ</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	LPListBox CListBox::CreateListBox(void)
	{
		std::shared_ptr<CListBox> p = std::make_shared<CListBox>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Initialize(void)
	{
		if (!m_pTemplate)
		{
			m_pTemplate = CLabel::CreateLabel();
			CControll::CreateInfo tmp = {
				m_Pos,
				Vector2(m_Size.x - 10, 24),
				"List"
			};
			m_pTemplate->FontCreate(24, "");
			m_pTemplate->SetInfo(tmp);
		}
		if (!m_pScrollBar)
		{
			m_pScrollBar = CScrollBar::CreateScrollBar();
			CControll::CreateInfo sbci = {
				m_Pos,
				m_Size,
				""
			};
			m_pScrollBar->SetInfo(sbci);
			m_pScrollBar->FontCreate(24, "");
			m_pScrollBar->SetWidth(10);
			m_pScrollBar->SetScrlArea(m_pScrollBar->GetRect(), 0);
			m_pScrollBar->Initialize();
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Update(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		//選択番号の更新
		m_PrevSelect = m_Select;
		//スクロールバーの更新
		m_pScrollBar->Update();
		//スクロールに対応した場所に変換
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			if (!m_List[i])
			{
				continue;
			}
			Vector2 pos = m_pTemplate->GetPos();
			pos.y += (i * m_pTemplate->GetSize().y);
			pos.y -= m_pScrollBar->GetScroll();
			m_List[i]->SetPos(pos);
		}
		//マウスクリックで線選択
		Vector2 mousePos;
		g_pInput->GetMousePos(mousePos);
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			if (!IsMouseOver())
			{
				break;
			}
			if (!m_List[i])
			{
				continue;
			}
			if (!m_List[i]->IsPush())
			{
				continue;
			}
			m_Select = i;
			break;
		}
		//選択されているのがわかるように色を付ける
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			if (!m_List[i])
			{
				continue;
			}
			if (m_Select == i)
			{
				m_List[i]->SetBackColor(MOF_COLOR_BLUE);
				m_List[i]->SetTextColor(MOF_COLOR_WHITE);
			}
			else
			{
				m_List[i]->SetBackColor(MOF_COLOR_WHITE);
				m_List[i]->SetTextColor(MOF_COLOR_BLACK);
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		//ステンシルバッファの有効化
		g_pGraphics->SetStencilEnable(TRUE);
		//ステンシルバッファの置き換え
		g_pGraphics->SetStencilControl(COMPARISON_ALWAYS,
			STENCIL_REPLACE, STENCIL_REPLACE, STENCIL_REPLACE);
		//ステンシルバッファの値変更
		g_pGraphics->SetStencilValue(255);
		//背景の描画
		CGraphicsUtilities::RenderFillRect(GetRect(), m_BackColor);
		//ステンシルバッファの設定
		g_pGraphics->SetStencilControl(COMPARISON_LESS,
			STENCIL_KEEP, STENCIL_KEEP, STENCIL_KEEP);
		//ステンシルバッファの値変更
		g_pGraphics->SetStencilValue(254);
		//リストの分だけ描画
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			if (!m_List[i])
			{
				continue;
			}
			m_List[i]->Render();
		}
		//ステンシルバッファの無効化
		g_pGraphics->SetStencilEnable(FALSE);
		//スクロールバーの描画
		m_pScrollBar->Render();
	}
	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Release(void)
	{
		m_pTemplate = nullptr;
		m_pScrollBar = nullptr;
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			m_List[i] = nullptr;
		}
		m_List.Release();
	}
	// ********************************************************************************
	/// <summary>
	/// テンプレラベルの取得
	/// </summary>
	/// <returns>ラベル</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	LPLabel CListBox::GetTemplateLabel(void)
	{
		return m_pTemplate;
	}
	// ********************************************************************************
	/// <summary>
	/// スクロールバーの取得
	/// </summary>
	/// <returns>スクロールバー</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	LPScrollBar CListBox::GetScrollBar(void)
	{
		return m_pScrollBar;
	}
	// ********************************************************************************
	/// <summary>
	/// リストに追加
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Add(void)
	{
		AddLast(m_pTemplate->GetText());
	}
	// ********************************************************************************
	/// <summary>
	/// リストに追加
	/// </summary>
	/// <param name="str">文字列</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Add(const CString & str)
	{
		AddLast(str);
	}
	// ********************************************************************************
	/// <summary>
	/// リストの先頭に追加
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddFast(void)
	{
		AddNo(m_pTemplate->GetText(), 0);
	}
	// ********************************************************************************
	/// <summary>
	/// リストの先頭に追加
	/// </summary>
	/// <param name="str">文字列</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddFast(const CString & str)
	{
		AddNo(str, 0);
	}
	// ********************************************************************************
	/// <summary>
	/// 指定番号に追加
	/// </summary>
	/// <param name="no">番号</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddNo(const MofU32 & no)
	{
		AddNo(m_pTemplate->GetText(), 0);
	}
	// ********************************************************************************
	/// <summary>
	/// 指定番号に追加
	/// </summary>
	/// <param name="str">文字列</param>
	/// <param name="no">番号</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddNo(const CString & str, const MofU32 & no)
	{
		if (m_Select < 0)
		{
			m_Select = 0;
			m_PrevSelect = 0;
		}
		LPLabel tmp = CLabel::CreateLabel();
		CControll::CreateInfo info = {
			m_pTemplate->GetPos(),
			m_pTemplate->GetSize(),
			str
		};
		tmp->FontCreate(m_pTemplate->GetFontSize(), "");
		tmp->SetInfo(info);
		tmp->SetTextColor(MOF_COLOR_BLACK);
		tmp->SetBackColor(MOF_COLOR_WHITE);
		tmp->SetBackShow(TRUE);
		Vector2 pos = info.Pos;
		int c = m_List.GetArrayCount();
		float s = info.Size.y;
		pos.y += c * s;
		tmp->SetPos(pos);
		m_List.AddNo(tmp, no);
		m_pScrollBar->ChangeMaxSize(s + c * s);
	}
	// ********************************************************************************
	/// <summary>
	/// リストの最後尾に追加
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddLast(void)
	{
		AddNo(m_pTemplate->GetText(), m_List.GetArrayCount());
	}
	// ********************************************************************************
	/// <summary>
	/// リストの最後尾に追加
	/// </summary>
	/// <param name="str">文字列</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddLast(const CString & str)
	{
		AddNo(str, m_List.GetArrayCount());
	}
	// ********************************************************************************
	/// <summary>
	/// リストの最後尾を削除
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Delete(void)
	{
		DeleteLast();
	}
	// ********************************************************************************
	/// <summary>
	/// リストの先頭を削除
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::DeleteFast(void)
	{
		DeleteNo(0);
	}
	// ********************************************************************************
	/// <summary>
	/// リストの指定番号を削除
	/// </summary>
	/// <param name="no">削除</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::DeleteNo(const MofU32 & no)
	{
		m_List.Delete(no);
		int c = m_List.GetArrayCount();
		float s = m_pTemplate->GetSize().y;
		m_pScrollBar->ChangeMaxSize(c * s);
		if (m_Select < 0)
		{
			return;
		}
		if (no <= m_Select)
		{
			m_Select--;
			m_PrevSelect--;
		}
		else if (m_Select >= m_List.GetArrayCount())
		{
			m_Select = m_List.GetArrayCount() - 1;
			m_PrevSelect = m_List.GetArrayCount() - 1;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// リストの最後尾を削除
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::DeleteLast(void)
	{
		DeleteNo(m_List.GetArrayCount() - 1);
	}
	// ********************************************************************************
	/// <summary>
	/// 入れ替え
	/// </summary>
	/// <param name="idx1">入れ替えるリスト番号１</param>
	/// <param name="idx2">入れ替えるリスト番号２</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Swap(const MofU32 & idx1, const MofU32 & idx2)
	{
		MofBool b = m_List.Swap(idx1, idx2);
		if (!b)
		{
			return;
		}
		if (m_Select == idx1)
		{
			m_Select = idx2;
			m_PrevSelect = idx2;
		}
		else if (m_Select == idx2)
		{
			m_Select = idx1;
			m_PrevSelect = idx1;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 現在選択中の番号取得
	/// </summary>
	/// <returns>現在選択中の番号</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	MofInt CListBox::GetSelectNo(void) const
	{
		return m_Select;
	}
	// ********************************************************************************
	/// <summary>
	/// 現在選択中の文字列取得
	/// </summary>
	/// <returns>文字列</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CString CListBox::GetText(void) const
	{
		if (m_Select < 0)
		{
			return "";
		}
		return m_List[m_Select]->GetText();
	}
	// ********************************************************************************
	/// <summary>
	/// リストの指定番号の文字列取得
	/// </summary>
	/// <param name="no">指定番号</param>
	/// <returns>文字列</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CString CListBox::GetText(const MofInt & no) const
	{
		return m_List[no]->GetText();
	}
	// ********************************************************************************
	/// <summary>
	/// リストの選択番号が変わったフラグ取得
	/// </summary>
	/// <returns>リストの選択番号が変わったフラグ</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	MofBool CListBox::IsChenged(void) const
	{
		return (m_PrevSelect != m_Select);
	}
}