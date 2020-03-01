#include "Label.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/25</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CLabel::CLabel(void) :
		CControll()
	{
		m_bLineShow = FALSE;
		m_bBackShow = FALSE;
		m_BackColor = MOF_COLOR_CWHITE;
		m_LineColor = MOF_COLOR_HBLACK;
		m_TextColor = MOF_COLOR_WHITE;
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/25</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CLabel::~CLabel(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// ラベルの生成
	/// </summary>
	/// <returns>ラベルポインタ</returns>
	/// <created>いのうえ,2020/02/25</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	LPLabel CLabel::CreateLabel(void)
	{
		std::shared_ptr<CLabel> p = std::make_shared<CLabel>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CLabel::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		if (m_bBackShow)
		{
			CGraphicsUtilities::RenderFillRect(GetRect(), m_BackColor);
		}
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(GetRect(), m_LineColor);
		}
		m_Font.RenderFormatString(GetRect(), m_TextColor, m_Text);
	}
	// ********************************************************************************
	/// <summary>
	/// 背景色描画フラグの設定
	/// </summary>
	/// <param name="b">フラグ</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CLabel::SetBackShow(const MofBool & b)
	{
		m_bBackShow = b;
	}
}