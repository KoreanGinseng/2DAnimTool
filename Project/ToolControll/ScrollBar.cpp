#include "ScrollBar.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	CScrollBar::CScrollBar(void) :
		m_pBtnUp(nullptr),
		m_pBtnScrl(nullptr),
		m_pBtnDown(nullptr),
		m_ScrlArea(),
		m_ScrlBar(),
		m_Type(SCRLTYPE_VIRTICAL),
		m_MaxSize(0),
		m_ScrlWidth(0),
		m_ScrlParPix(0.0f),
		m_Scroll(0),
		m_bBarHold(FALSE)
	{
		m_bLineShow = FALSE;
		m_BackColor = MOF_COLOR_CBLACK;
		m_LineColor = MOF_COLOR_RED;
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	CScrollBar::~CScrollBar(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// スクロールバーの生成
	/// </summary>
	/// <param name="info">生成情報</param>
	/// <returns>スクロールバーポインタ</returns>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	LPScrollBar CScrollBar::CreateScrollBar(void)
	{
		std::shared_ptr<CScrollBar> p = std::make_shared<CScrollBar>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::Initialize(void)
	{
		//スクロール値の初期化
		m_Scroll = 0;
		//バーのサイズを計算
		InitBarSize();
		//ボタンの生成
		CreateButton();
		//スライドバーの位置の初期化
		InitBarPos();
		//スライドバーの長さを初期化
		InitBarLength();
	}
	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::Update(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}

		//マウスによるスライド処理
		MoveMouse();

		//マウスホイールによるスライド処理
		MoveWheel();
		
		//上下ボタンによるスライド処理
		MoveButton();

		//スクロール値の制御
		CheckOverScroll();

		//位置の再計算
		UpdateBarPos();
	}
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		//土台の描画
		CGraphicsUtilities::RenderFillRect(m_ScrlBar, m_BackColor);
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(m_ScrlArea, m_LineColor);
		}
		//各ボタンの描画
		m_pBtnUp->Render();
		m_pBtnScrl->Render();
		m_pBtnDown->Render();
	}
	// ********************************************************************************
	/// <summary>
	/// 解放
	/// </summary>
	/// <created>いのうえ,2020/02/24</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::Release(void)
	{
		m_pBtnUp = nullptr;
		m_pBtnScrl = nullptr;
		m_pBtnDown = nullptr;
	}
	// ********************************************************************************
	/// <summary>
	/// スクロール方向の設定
	/// </summary>
	/// <param name="t">スクロール方向</param>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::SetType(ScrlType t)
	{
		m_Type = t;
	}
	// ********************************************************************************
	/// <summary>
	/// スクロールバーの幅の設定
	/// </summary>
	/// <param name="w">幅</param>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::SetWidth(const int & w)
	{
		m_ScrlWidth = w;
	}
	// ********************************************************************************
	/// <summary>
	/// スクロールするエリアの設定
	/// </summary>
	/// <param name="area">エリア矩形</param>
	/// <param name="maxSize">スクロール最大値</param>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::SetScrlArea(const CRectangle & area, const int & maxSize)
	{
		m_ScrlArea = area;
		m_MaxSize = maxSize;
	}
	// ********************************************************************************
	/// <summary>
	/// スクロール最大値の変更
	/// </summary>
	/// <param name="maxSize">最大値</param>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::ChangeMaxSize(const int & maxSize)
	{
		m_MaxSize = maxSize;
		InitBarLength();
		CheckOverScroll();
		UpdateBarPos();
	}
	// ********************************************************************************
	/// <summary>
	/// スクロールエリアの取得
	/// </summary>
	/// <returns>スクロールエリア</returns>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	CRectangle CScrollBar::GetScrlAreaRect(void) const
	{
		return m_ScrlArea;
	}
	// ********************************************************************************
	/// <summary>
	/// スクロール値の取得
	/// </summary>
	/// <returns></returns>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	float CScrollBar::GetScroll(void) const
	{
		return (m_Scroll * m_ScrlParPix);
	}
	// ********************************************************************************
	/// <summary>
	/// 上ボタンの取得
	/// </summary>
	/// <returns>上ボタン</returns>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	LPButton CScrollBar::GetBtnUp(void)
	{
		return m_pBtnUp;
	}
	// ********************************************************************************
	/// <summary>
	/// スライドボタンの取得
	/// </summary>
	/// <returns>スライドボタン</returns>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	LPButton CScrollBar::GetBtnScrl(void)
	{
		return m_pBtnScrl;
	}
	// ********************************************************************************
	/// <summary>
	/// 下ボタンの取得
	/// </summary>
	/// <returns>下ボタン</returns>
	/// <created>いのうえ,2020/02/28</created>
	/// <changed>いのうえ,2020/02/28</changed>
	// ********************************************************************************
	LPButton CScrollBar::GetBtnDown(void)
	{
		return m_pBtnDown;
	}
	// ********************************************************************************
	/// <summary>
	/// 各ボタンの生成
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::CreateButton(void)
	{
		CControll::CreateInfo info;
		info.Pos = m_ScrlBar.GetTopLeft();
		info.Size = m_ScrlBar.GetBottomRight() - m_ScrlBar.GetTopLeft();
		//上下ボタンの作成
		if (!m_pBtnUp)
		{
			m_pBtnUp = CButton::CreateButton();
			m_pBtnScrl = CButton::CreateButton();
			m_pBtnDown = CButton::CreateButton();
			m_pBtnUp->SetInfo(info);
			m_pBtnScrl->SetInfo(info);
			m_pBtnDown->SetInfo(info);
		}
		//上下ボタンのサイズも確定する
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			m_pBtnUp->SetSize(m_ScrlWidth, info.Size.y);
			m_pBtnDown->SetPos((info.Pos.x + info.Size.x) - m_ScrlWidth, info.Pos.y);
			m_pBtnDown->SetSize(m_ScrlWidth, info.Size.y);
			break;
		case SCRLTYPE_VIRTICAL:
			m_pBtnUp->SetSize(info.Size.x, m_ScrlWidth);
			m_pBtnDown->SetPos(info.Pos.x, (info.Pos.y + info.Size.y) - m_ScrlWidth);
			m_pBtnDown->SetSize(info.Size.x, m_ScrlWidth);
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// バーのサイズの初期化
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::InitBarSize(void)
	{
		//スクロールエリアからスクロールバーのサイズを作成
		m_ScrlBar = m_ScrlArea;
		//エリアの内側に埋め込む
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			m_ScrlBar.Top = m_ScrlBar.Bottom - m_ScrlWidth;
			break;
		case SCRLTYPE_VIRTICAL:
			m_ScrlBar.Left = m_ScrlBar.Right - m_ScrlWidth;
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// スライドボタンの位置の初期化
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::InitBarPos(void)
	{
		//スクロールボタンの位置を確定
		m_pBtnScrl->SetPos(m_pBtnUp->GetPos());
		Vector2 scPos;
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			scPos = Vector2(m_pBtnScrl->GetPos().x + m_pBtnUp->GetSize().x, m_pBtnScrl->GetPos().y);
			m_pBtnScrl->SetPos(scPos);
			break;
		case SCRLTYPE_VIRTICAL:
			scPos = Vector2(m_pBtnScrl->GetPos().x, m_pBtnScrl->GetPos().y + m_pBtnUp->GetSize().y);
			m_pBtnScrl->SetPos(scPos);
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// スライドボタンの長さ初期化
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::InitBarLength(void)
	{
		//スクロールエリアの幅を取得
		int areaw;
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			areaw = m_ScrlArea.GetWidth();
			break;
		case SCRLTYPE_VIRTICAL:
			areaw = m_ScrlArea.GetHeight();
			break;
		}
		//スクロールボタンの長さを計算する
		int scrlw = areaw - m_ScrlWidth * 2;
		if (m_MaxSize <= areaw)
		{
			m_ScrlParPix = 0;
		}
		else
		{
			//スクロールボタンのサイズを計算する
			scrlw *= (static_cast<float>(areaw) / m_MaxSize);
			//ボタンのサイズが最小以下になったらスクロールポイントを増やして調整する
			if (scrlw <= m_ScrlWidth)
			{
				scrlw = m_ScrlWidth;
			}
			//1pixcelに移動するスクロール量を計算する
			//計算式 : 見えてない部分の長さ / スクロルボタンのエリアの長さ - スクロールボタンの長さ
			m_ScrlParPix = (m_MaxSize - areaw) / ((areaw - m_ScrlWidth * 2.0f) - scrlw);
		}
		//スクロールボタンの幅を設定する
		Vector2 size = m_pBtnUp->GetSize();
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			m_pBtnScrl->SetSize(scrlw, size.y);
			break;
		case SCRLTYPE_VIRTICAL:
			m_pBtnScrl->SetSize(size.x, scrlw);
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// マウスでのスクロール処理
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::MoveMouse(void)
	{
		Vector2 move;
		g_pInput->GetMouseMove(move.x, move.y);
		//スクロールボタン操作
		if (m_pBtnScrl->IsPush())
		{
			m_bBarHold = TRUE;
		}
		if (m_bBarHold)
		{
			switch (m_Type)
			{
			case SCRLTYPE_HORIZONTAL:
				m_Scroll += move.x;
				break;
			case SCRLTYPE_VIRTICAL:
				m_Scroll += move.y;
				break;
			}
		}
		if (g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
		{
			m_bBarHold = FALSE;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// マウスホイールでのスクロール処理
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::MoveWheel(void)
	{
		Vector2 mousePos;
		g_pInput->GetMousePos(mousePos);
		//スクロール操作
		float movew = g_pInput->GetMouseWheelMove();
		if (m_ScrlArea.CollisionPoint(mousePos) && movew != 0)
		{
			switch (m_Type)
			{
			case SCRLTYPE_HORIZONTAL:
				if (g_pInput->IsKeyHold(MOFKEY_LCONTROL))
				{
					m_Scroll -= movew;
				}
				break;
			case SCRLTYPE_VIRTICAL:
				if (!g_pInput->IsKeyHold(MOFKEY_LCONTROL))
				{
					m_Scroll -= movew;
				}
				break;
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 上下ボタンでのスクロール処理
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::MoveButton(void)
	{
		//上下ボタン操作
		if (m_pBtnUp->IsHold())
		{
			m_Scroll--;
		}
		else if (m_pBtnDown->IsHold())
		{
			m_Scroll++;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// スクロール値の制御
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::CheckOverScroll(void)
	{
		int areaw;
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			areaw = m_ScrlArea.GetWidth() - m_pBtnScrl->GetSize().x;
			break;
		case SCRLTYPE_VIRTICAL:
			areaw = m_ScrlArea.GetHeight() - m_pBtnScrl->GetSize().y;
			break;
		}
		if (m_Scroll < 0)
		{
			m_Scroll = 0;
		}
		else if (m_Scroll > areaw - m_ScrlWidth * 2)
		{
			m_Scroll = areaw - m_ScrlWidth * 2;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 位置の再計算
	/// </summary>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::UpdateBarPos(void)
	{
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			m_pBtnScrl->SetPos(m_pBtnUp->GetRect().Right + m_Scroll, m_pBtnScrl->GetPos().y);
			break;
		case SCRLTYPE_VIRTICAL:
			m_pBtnScrl->SetPos(m_pBtnScrl->GetPos().x, m_pBtnUp->GetRect().Bottom + m_Scroll);
			break;
		}
	}
}
