#include "TextBox.h"
#include "../WindowProc.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	CTextBox::CTextBox(void) :
		m_bInput(FALSE),
		m_CursorPos(0.0f),
		m_CursorTime(0),
		m_CursorPoint(0),
		m_bNumOnly(FALSE),
		m_Error(0),
		m_TxtAlign(TXTALI_LEFT),
		m_NumMin(INT16_MIN),
		m_NumMax(INT16_MAX)
	{
		m_BackColor = MOF_COLOR_WHITE;
		GetList().Add(this);
	}
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	CTextBox::~CTextBox(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// テキストボックス生成クラス
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	LPTextBox CTextBox::CreateTextBox(void)
	{
		std::shared_ptr<CTextBox> p = std::make_shared<CTextBox>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// テキストボックスの制御リスト取得
	/// </summary>
	/// <returns>制御リスト</returns>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	CDynamicArray<CTextBox*>& CTextBox::GetList(void)
	{
		static CDynamicArray<CTextBox*> list;
		return list;
	}
	// ********************************************************************************
	/// <summary>
	/// リストの解放
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::ReleaseList(void)
	{
		for (int i = 0; i < GetList().GetArrayCount(); i++)
		{
			GetList()[i] = nullptr;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ImeInputの更新
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::RefreshImeInput(void)
	{
		for (int i = 0; i < GetList().GetArrayCount(); i++)
		{
			CTextBox* p = GetList()[i];
			if (!p->IsInput() ||
				(p->IsInput() && g_pImeInput->GetInputString()->GetLength() > 0))
			{
				continue;
			}
			g_pImeInput->SetEnable(TRUE);
			g_pImeInput->SetInputString(p->GetText());
			p->SetText("");
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 初期化
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::Initialize(void)
	{
		g_pImeInput->SetEnable(FALSE);
		g_pImeInput->SetInputString("");
	}
	// ********************************************************************************
	/// <summary>
	/// 更新
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::Update(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		//枠外クリックで入力中断
		if (m_bInput && (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !IsMouseOver()))
		{
			g_pImeInput->GetInputImeString(m_Text);
			g_pImeInput->ResetInput();
			g_pImeInput->SetEnable(FALSE);
			//中断時文字がない場合文字を入れておく
			if (m_bNumOnly && m_Text == "")
			{
				m_Text = "0";
			}
			else if (!m_bNumOnly && m_Text == "")
			{
				m_Text = "NoName";
			}
			m_Font.SetBold(600);
			m_bInput = FALSE;
		}
		//数字のみの処理
		NumUpdate();
		//クリックされたとき入力状態にする
		if (IsPush() && !m_bInput)
		{
			m_bInput = TRUE;
			m_Font.SetBold(0);
		}
		//確定文字がある場合文字列を追加する
		if (m_bInput && g_pImeInput->GetEnterString()->GetLength() > 0)
		{
			m_Text += g_pImeInput->GetEnterString()->GetString();
			g_pImeInput->ResetEnterString();
			g_pImeInput->SetEnable(FALSE);
			m_Font.SetBold(600);
			m_bInput = FALSE;
		}
		//カーソルの処理
		CursorUpdate();
	}
	// ********************************************************************************
	/// <summary>
	/// カーソルの更新
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::CursorUpdate(void)
	{
		//点滅用カウント
		if (--m_CursorTime < 0)
		{
			m_CursorTime = 60;
		}
		//入力中ならカーソルの場所を計算する
		if (m_bInput)
		{
			CString str;
			g_pImeInput->GetInputImeString(str);
			m_CursorPoint = ((CWindowProc*)g_pImeInput)->GetInsertPoint();
			str.Delete(m_CursorPoint);
			CRectangle outRect;
			m_Font.CalculateStringRect(0, 0, str.GetString(), outRect);
			m_CursorPos = outRect.Right;
			if (m_TxtAlign == TXTALI_RIGHT)
			{
				m_CursorPos = GetRect().GetWidth() - 4;
			}
			else if (m_TxtAlign == TXTALI_CENTER)
			{
				m_CursorPos += (GetRect().GetWidth() - outRect.GetWidth()) * 0.5f;
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 描画
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		CRectangle rect = GetRect();
		//土台の描画
		CGraphicsUtilities::RenderFillRect(rect, m_BackColor);
		//枠の描画
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(rect, m_LineColor);
		}
		//カーソルの描画
		if (m_CursorTime % 60 < 30 && m_bInput)
		{
			CGraphicsUtilities::RenderLine(
				rect.GetTopLeft() + Vector2(m_CursorPos + 2, 2),
				rect.GetBottomLeft() + Vector2(m_CursorPos + 2, -2),
				m_TextColor
			);
		}
		//入力中なら少し文字を持ち上げる
		CString str;
		if (m_bInput)
		{
			g_pImeInput->GetInputImeString(str);
			rect.Top = GetRect().Top - 2;
		}
		else
		{
			str = m_Text;
		}
		//数字のみでエラーが発生している場合文字列を消しておく
		if (m_bNumOnly)
		{
			switch (m_Error & 0xFF)
			{
			case NE_NOCONVERSION:
			case NE_OUTOFRANGE:
				str = "";
				break;
			}
		}
		CRectangle outRect;
		m_Font.CalculateStringRect(0, 0, str.GetString(), outRect);
		float offsetX = 0;
		float offsetY = (rect.GetHeight() - outRect.GetHeight()) * 0.5f;
		if (m_TxtAlign == TXTALI_RIGHT)
		{
			offsetX = rect.GetWidth() - outRect.GetWidth();
		}
		else if (m_TxtAlign == TXTALI_CENTER)
		{
			offsetX = (rect.GetWidth() - outRect.GetWidth()) * 0.5f;
		}
		//文字の描画
		m_Font.RenderString(rect.Left + offsetX, rect.Top + offsetY, m_TextColor, str.GetString());
	}
	// ********************************************************************************
	/// <summary>
	/// 入力フラグの設定
	/// </summary>
	/// <param name="b">フラグ</param>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::SetInput(const MofBool & b)
	{
		m_bInput = b;
	}
	// ********************************************************************************
	/// <summary>
	/// 入力フラグの取得
	/// </summary>
	/// <returns>入力フラグ</returns>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	MofBool CTextBox::IsInput(void) const
	{
		return m_bInput;
	}
	// ********************************************************************************
	/// <summary>
	/// 数字のみフラグの設定
	/// </summary>
	/// <param name="b">フラグ</param>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::SetNumOnly(const MofBool & b)
	{
		m_bNumOnly = b;
		m_Text = "0";
	}
	// ********************************************************************************
	/// <summary>
	/// 数字のみフラグの取得
	/// </summary>
	/// <returns>フラグ</returns>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	MofBool CTextBox::IsNumOnly(void) const
	{
		return m_bNumOnly;
	}
	// ********************************************************************************
	/// <summary>
	/// 数字のみの場合の制御
	/// </summary>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::NumUpdate(void)
	{
		if (!m_bNumOnly)
		{
			return;
		}
		//エラーを消す
		m_Error &= ~m_Error;
		//入力中ならエラーを監視
		if (m_bInput)
		{
			CString str;
			if (g_pImeInput->GetEnterString()->GetLength() > 0)
			{
				str = g_pImeInput->GetEnterString()->GetString();
			}
			else
			{
				g_pImeInput->GetInputImeString(str);
				if (str == "")
				{
					str = "0";
				}
			}
			//エラーチェック
			try 
			{
				std::stof(str.GetString());
			}
			//変換失敗
			catch (const std::invalid_argument&) 
			{
				m_Error |= NE_NOCONVERSION;
				g_pImeInput->SetInputString("0");
			}
			//オーバーフロー
			catch (const std::out_of_range&)
			{
				m_Error |= NE_OUTOFRANGE;
				g_pImeInput->SetInputString("0");
			}
		}
		else
		{
			if (GetNum() < m_NumMin)
			{
				SetNum(m_NumMin);
			}
			else if (GetNum() > m_NumMax)
			{
				SetNum(m_NumMax);
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// 数字の取得
	/// </summary>
	/// <returns></returns>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	MofFloat CTextBox::GetNum(void) const
	{
		//文字列から数字を取得
		//失敗した場合0が返る
		MofFloat re = 0.0f;
		try
		{
			re = std::stof(m_Text.GetString());
		}
		catch (...) {}
		return re;
	}
	// ********************************************************************************
	/// <summary>
	/// 数字の設定
	/// </summary>
	/// <param name="num">数字</param>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::SetNum(const MofFloat & num)
	{
		if (!m_bNumOnly || m_bInput)
		{
			return;
		}
		m_Text = std::_Floating_to_string("%.0f", num).c_str();
	}
	// ********************************************************************************
	/// <summary>
	/// 数字の加算処理
	/// </summary>
	/// <param name="num">数字</param>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::AddNum(const MofFloat & num)
	{
		SetNum(GetNum() + num);
	}
	// ********************************************************************************
	/// <summary>
	/// 数字の減算処理
	/// </summary>
	/// <param name="num">数字</param>
	/// <created>いのうえ,2020/03/01</created>
	/// <changed>いのうえ,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::SubNum(const MofFloat & num)
	{
		AddNum(-num);
	}
	// ********************************************************************************
	/// <summary>
	/// 描画位置の設定
	/// </summary>
	/// <param name="align">描画位置</param>
	/// <created>いのうえ,2020/03/03</created>
	/// <changed>いのうえ,2020/03/03</changed>
	// ********************************************************************************
	void CTextBox::SetTxtAlign(const TxtAlign & align)
	{
		m_TxtAlign = align;
	}
	// ********************************************************************************
	/// <summary>
	/// 最小値と最大値の設定
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <created>いのうえ,2020/03/03</created>
	/// <changed>いのうえ,2020/03/03</changed>
	// ********************************************************************************
	void CTextBox::SetNumMinMax(const MofInt & min, const MofInt & max)
	{
		m_NumMin = min;
		m_NumMax = max;
	}
}