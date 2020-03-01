#include "Button.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CButton::CButton(void) :
		CControll()
	{
		m_BackColorOver = MOF_XRGB(192, 192, 224);
		m_LineColorOver = MOF_COLOR_BLUE;
		m_PushBackColor = MOF_XRGB(128, 128, 192);
		m_PushLineColor = MOF_COLOR_BLUE;
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CButton::~CButton(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// ボタン生成
	/// </summary>
	/// <returns>ボタンのポインタ</returns>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	LPButton CButton::CreateButton(void)
	{
		LPButton p = std::make_shared<CButton>();
		return p;
	}
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CButton::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}

		CRectangle rect = GetRect();

		MofU32 backColor = m_BackColor;
		MofU32 lineColor = m_LineColor;
		//マウスオーバー描画
		if (IsMouseOver() || IsHold())
		{
			backColor = m_BackColorOver;
			lineColor = m_LineColorOver;
		}
		//押してる間の描画
		if (IsHold())
		{
			backColor = m_PushBackColor;
			lineColor = m_PushLineColor;
		}
		//土台描画
		CGraphicsUtilities::RenderFillRect(rect, backColor);
		//枠描画
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(rect, lineColor);
		}

		//文字描画
		if (m_Text != "")
		{
			CRectangle outrect;
			CGraphicsUtilities::CalculateStringRect(0, 0, m_Text, outrect);
			float w = (rect.GetWidth() - outrect.GetWidth()) * 0.5f;
			float h = (rect.GetHeight() - outrect.GetHeight()) * 0.5f;
			m_Font.RenderString(rect.Left + w, rect.Top + h, m_TextColor, m_Text);
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 押している間の色の設定
	/// </summary>
	/// <param name="color">色</param>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CButton::SetPushBackColor(const MofU32 & color)
	{
		m_PushBackColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// 押している間の線の色の設定
	/// </summary>
	/// <param name="color">色</param>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CButton::SetPushLineColor(const MofU32 & color)
	{
		m_PushLineColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// 背景色の設定(マウスオーバー時)
	/// </summary>
	/// <param name="color">色</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CButton::SetBackColorOver(const MofU32 & color)
	{
		m_BackColorOver = color;
	}
	// ********************************************************************************
	/// <summary>
	/// 枠線の色の設定(マウスオーバー時)
	/// </summary>
	/// <param name="color">色</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CButton::SetLineColorOver(const MofU32 & color)
	{
		m_LineColorOver = color;
	}
}