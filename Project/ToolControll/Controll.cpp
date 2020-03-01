#include "Controll.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CControll::CControll(void) :
		m_bLineShow(TRUE),
		m_Pos(0, 0),
		m_Size(0, 0),
		m_Font(),
		m_FontSize(24),
		m_bShow(TRUE)
	{
		m_BackColor = MOF_COLOR_CWHITE;
		m_LineColor = MOF_COLOR_HBLACK;
		m_TextColor = MOF_COLOR_BLACK;
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CControll::~CControll(void)
	{
		m_Font.Release();
	}
	// ********************************************************************************
	/// <summary>
	/// 生成情報の設定
	/// </summary>
	/// <param name="info">生成情報</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetInfo(CreateInfo info)
	{
		SetPos(info.Pos);
		SetSize(info.Size);
		SetText(info.Text);
	}
	// ********************************************************************************
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetPos(const Vector2 & pos)
	{
		m_Pos = pos;
	}
	// ********************************************************************************
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetPos(const float & x, const float & y)
	{
		SetPos(Vector2(x, y));
	}
	// ********************************************************************************
	/// <summary>
	/// サイズの設定
	/// </summary>
	/// <param name="size">サイズ</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetSize(const Vector2 & size)
	{
		m_Size = size;
	}
	// ********************************************************************************
	/// <summary>
	/// サイズの設定
	/// </summary>
	/// <param name="w">横幅</param>
	/// <param name="h">高さ</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetSize(const float & w, const float & h)
	{
		SetSize(Vector2(w, h));
	}
	// ********************************************************************************
	/// <summary>
	/// フォントの生成
	/// </summary>
	/// <param name="s">フォントサイズ</param>
	/// <param name="pFace">字体</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::FontCreate(const MofS32 s, LPCMofChar pFace)
	{
		m_Font.Release();
		m_FontSize = s;
		m_Font.Create(s, pFace);
	}
	// ********************************************************************************
	/// <summary>
	/// テキストの設定
	/// </summary>
	/// <param name="pText">テキスト</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetText(CString text)
	{
		m_Text = text;
	}
	// ********************************************************************************
	/// <summary>
	/// フォントサイズの設定
	/// </summary>
	/// <param name="s">サイズ</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetFontSize(const MofS32 s)
	{
		m_FontSize = s;
		m_Font.SetSize(s);
	}
	// ********************************************************************************
	/// <summary>
	/// 枠線表示フラグの設定
	/// </summary>
	/// <param name="b">フラグ</param>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetLineShow(const MofBool & b)
	{
		m_bLineShow = b;
	}
	// ********************************************************************************
	/// <summary>
	/// 描画フラグの設定
	/// </summary>
	/// <param name="b">フラグ</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetShow(const MofBool & b)
	{
		m_bShow = b;
	}
	// ********************************************************************************
	/// <summary>
	/// 背景色の設定
	/// </summary>
	/// <param name="color">色</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetBackColor(const MofU32 & color)
	{
		m_BackColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// 枠線の色の設定
	/// </summary>
	/// <param name="color">色</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetLineColor(const MofU32 & color)
	{
		m_LineColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// テキストの表示色の設定
	/// </summary>
	/// <param name="color">色</param>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetTextColor(const MofU32 & color)
	{
		m_TextColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// 矩形取得
	/// </summary>
	/// <returns>矩形</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CRectangle CControll::GetRect(void) const
	{
		return CRectangle(m_Pos, m_Pos + m_Size);
	}
	// ********************************************************************************
	/// <summary>
	/// マウスが重なっているかのフラグ取得
	/// </summary>
	/// <returns>マウスが重なっているか</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	MofBool CControll::IsMouseOver(void) const
	{
		Vector2 mousePos;
		g_pInput->GetMousePos(mousePos);
		if (GetRect().CollisionPoint(mousePos))
		{
			return TRUE;
		}
		return FALSE;
	}
	// ********************************************************************************
	/// <summary>
	/// マウス左ボタンで押した瞬間のフラグ取得
	/// </summary>
	/// <returns>マウス左ボタンで押した瞬間のフラグ</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	MofBool CControll::IsPush(void) const
	{
		if (IsMouseOver() &&
			g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			return TRUE;
		}
		return FALSE;
	}
	// ********************************************************************************
	/// <summary>
	/// マウス左ボタンで押されているかのフラグ取得
	/// </summary>
	/// <returns>マウス左ボタンで押されているかのフラグ</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	MofBool CControll::IsHold(void) const
	{
		if (IsMouseOver() &&
			g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
		{
			return TRUE;
		}
		return FALSE;
	}
	// ********************************************************************************
	/// <summary>
	/// マウス左ボタンが離れた瞬間のフラグ取得
	/// </summary>
	/// <returns>マウス左ボタンが離れた瞬間のフラグ</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	MofBool CControll::IsPull(void) const
	{
		if (IsMouseOver() &&
			g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
		{
			return TRUE;
		}
		return FALSE;
	}
	// ********************************************************************************
	/// <summary>
	/// 描画フラグの取得
	/// </summary>
	/// <returns>描画フラグ</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	MofBool CControll::IsShow(void) const
	{
		return m_bShow;
	}
	// ********************************************************************************
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	Vector2 CControll::GetPos(void) const
	{
		return m_Pos;
	}
	// ********************************************************************************
	/// <summary>
	/// サイズの取得
	/// </summary>
	/// <returns>サイズ</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	Vector2 CControll::GetSize(void) const
	{
		return m_Size;
	}
	// ********************************************************************************
	/// <summary>
	/// テキストの取得
	/// </summary>
	/// <returns>テキスト</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CString CControll::GetText(void) const
	{
		return m_Text;
	}
	// ********************************************************************************
	/// <summary>
	/// フォントサイズの取得
	/// </summary>
	/// <returns>フォントサイズ</returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	MofS32 CControll::GetFontSize(void) const
	{
		return m_FontSize;
	}
}