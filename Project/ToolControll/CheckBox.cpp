#include "CheckBox.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/25</created>
	/// <changed>いのうえ,2020/02/25</changed>
	// ********************************************************************************
	CCheckBox::CCheckBox(void) :
		m_bCheck(FALSE)
	{
		m_bLineShow = FALSE;
		m_BackColor = m_LineColor;
		m_TextColor = MOF_COLOR_WHITE;
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/25</created>
	/// <changed>いのうえ,2020/02/25</changed>
	// ********************************************************************************
	CCheckBox::~CCheckBox(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// チェックボックス生成
	/// </summary>
	/// <param name="info">生成情報</param>
	/// <returns>チェックボックス</returns>
	/// <created>いのうえ,2020/02/25</created>
	/// <changed>いのうえ,2020/02/25</changed>
	// ********************************************************************************
	LPCheckBox ToolControll::CCheckBox::CreateCheckBox(void)
	{
		std::shared_ptr<CCheckBox> p = std::make_shared<CCheckBox>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CCheckBox::Update(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		if (IsPush())
		{
			m_bCheck = !m_bCheck;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CCheckBox::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		////計算用矩形
		CRectangle rect = GetRect();
		//最小値を長さにする
		float r = MOF_MIN(GetRect().GetWidth(), GetRect().GetHeight());
		//チェックボックス用矩形
		CRectangle box(rect.Left, rect.Top, rect.Left + r, rect.Top + r);
		//通常色
		MofU32 color = m_LineColor;
		//チェックをつけているときは塗りつぶす
		if (m_bCheck)
		{
			CGraphicsUtilities::RenderFillRect(box, m_BackColor);
		}
		//枠を描画
		CGraphicsUtilities::RenderRect(box, color);
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(rect, color);
		}
		CRectangle outRect;
		m_Font.CalculateStringRect(0, 0, m_Text.GetString(), outRect);
		float offY = (rect.GetHeight() - outRect.GetHeight()) * 0.5f;
		//枠の横に文字を描画
		m_Font.RenderFormatString(
			box.Right + m_Font.GetSize() * 0.5f,
			box.Top + offY, m_TextColor, m_Text.GetString()
		);
	}
	// ********************************************************************************
	/// <summary>
	/// チェックされているかどうか
	/// </summary>
	/// <returns>チェックフラグ</returns>
	/// <created>いのうえ,2020/02/25</created>
	/// <changed>いのうえ,2020/02/25</changed>
	// ********************************************************************************
	MofBool CCheckBox::IsCheck(void) const
	{
		return (m_bCheck);
	}
}
