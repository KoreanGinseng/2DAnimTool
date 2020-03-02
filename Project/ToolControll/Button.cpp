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
		CControll(),
		m_pTexture(nullptr),
		m_IconAlign(ICON_LEFT)
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
	/// 画像の読み込み
	/// </summary>
	/// <param name="pName">ファイル名</param>
	/// <returns>成功か失敗</returns>
	/// <created>いのうえ,2020/03/02</created>
	/// <changed>いのうえ,2020/03/02</changed>
	// ********************************************************************************
	MofBool CButton::Load(LPCMofChar pName)
	{
		Release();
		m_pTexture = new CTexture();
		return m_pTexture->Load(pName);
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
			m_Font.CalculateStringRect(0, 0, m_Text, outrect);
			int iconW = 0;
			int fontX = 0;
			int iconX = 0;
			if (m_pTexture)
			{
				iconW = m_FontSize;
				switch (m_IconAlign)
				{
				case ICON_LEFT:
					iconX = 0;
					fontX = iconW;
					break;
				case ICON_RIGHT:
					iconX = outrect.GetWidth();
					fontX = 0;
					break;
				}
			}
			float w = (rect.GetWidth() - (outrect.GetWidth() + iconW)) * 0.5f;
			float h = (rect.GetHeight() - outrect.GetHeight()) * 0.5f;

			if (m_pTexture)
			{
				m_pTexture->RenderScale(
					rect.Left + w + iconX,
					rect.Top + h,
					(float)iconW / m_pTexture->GetWidth(),
					(float)iconW / m_pTexture->GetHeight()
				);
			}
			m_Font.RenderString(rect.Left + w + fontX, rect.Top + h, m_TextColor, m_Text);
		}
		else
		{
			if (m_pTexture)
			{
				float sx = (float)m_FontSize / m_pTexture->GetWidth();
				float sy = (float)m_FontSize / m_pTexture->GetHeight();
				float w = (rect.GetWidth() - m_pTexture->GetWidth() * sx) * 0.5f;
				float h = (rect.GetHeight() - m_pTexture->GetHeight() * sy) * 0.5f;
				m_pTexture->RenderScale(
					rect.Left + w,
					rect.Top + h,
					sx, sy
				);
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/03/02</created>
	/// <changed>いのうえ,2020/03/02</changed>
	// ********************************************************************************
	void CButton::Release(void)
	{
		if (m_pTexture)
		{
			m_pTexture->Release();
			delete m_pTexture;
			m_pTexture = nullptr;
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
	// ********************************************************************************
	/// <summary>
	/// アイコンの表示位置設定
	/// </summary>
	/// <param name="ali">位置</param>
	/// <created>いのうえ,2020/03/02</created>
	/// <changed>いのうえ,2020/03/02</changed>
	// ********************************************************************************
	void CButton::SetIconAlign(const BtnIconAlignment & ali)
	{
		m_IconAlign = ali;
	}
}