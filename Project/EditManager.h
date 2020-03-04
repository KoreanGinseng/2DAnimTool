#pragma once
#include	"Mof.h"
#include	"AreaManager.h"
#include	"ToolControll.h"

constexpr	int		Margin = 24;

// ********************************************************************************
/// <summary>
/// 
/// </summary>
// ********************************************************************************
class CEditManager
{
private:
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	// ********************************************************************************
	struct NumBox {
		CTextBox txtBox;
		CButton  btnUp;
		CButton  btnDown;
		// ********************************************************************************
		/// <summary>
		/// 
		/// </summary>
		/// <param name="info"></param>
		/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/02</created>
		/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/02</changed>
		// ********************************************************************************
		void SetInfo(CControll::CreateInfo info)
		{
			info.Size.x -= 20;
			txtBox.FontCreate(24, "");
			txtBox.SetInfo(info);
			txtBox.SetNumOnly(TRUE);
			txtBox.SetTxtAlign(CTextBox::TXTALI_RIGHT);
			info.Pos.x = txtBox.GetRect().Right;
			info.Size.x = 20;
			info.Size.y *= 0.5f;
			info.Text = "Å£";
			btnUp.SetTextColor(MOF_COLOR_CBLACK);
			btnUp.FontCreate(16, "");
			btnUp.SetInfo(info);
			info.Pos.y = btnUp.GetRect().Bottom;
			info.Text = "Å•";
			btnDown.SetTextColor(MOF_COLOR_CBLACK);
			btnDown.FontCreate(16, "");
			btnDown.SetInfo(info);
		}
		void Update(void)
		{
			if (btnUp.IsPush())
			{
				txtBox.AddNum(1.0f);
			}
			if (btnDown.IsPush())
			{
				txtBox.SubNum(1.0f);
			}
			txtBox.Update();
		}
		void Render(void)
		{
			txtBox.Render();
			btnUp.Render();
			btnDown.Render();
		}
		void Release(void)
		{
			btnDown.Release();
			btnUp.Release();
		}
	};
	CTextBox	m_tbName;
	CLabel		m_lblOffSetX;
	NumBox		m_nbOffSetX;
	CLabel		m_lblOffSetY;
	NumBox		m_nbOffSetY;
	CLabel		m_lblWidth;
	NumBox		m_nbWidth;
	CLabel		m_lblHeight;
	NumBox		m_nbHeight;
	CCheckBox	m_cbLoop;
	CButton		m_btnPlay;
	CLabel		m_lblComa;
	NumBox		m_nbComa;
	CLabel		m_lblAllFlame;
	NumBox		m_nbAllFlame;
	CButton		m_btnChange;
	CButton		m_btnPrev;
	CButton		m_btnNext;
	CLabel		m_lblNowComa;
	CLabel		m_lblFlame;
	NumBox		m_nbFlame;
	CLabel		m_lblNo;
	NumBox		m_nbNo;
	CLabel		m_lblStep;
	NumBox		m_nbStep;
	CListBox	m_lbAnimList;
	CButton		m_btnUpList;
	CButton		m_btnDownList;
	CButton		m_btnAddAnim;
	CButton		m_btnDeleteAnim;
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/02</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/02</changed>
	// ********************************************************************************
	CEditManager(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/02</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/02</changed>
	// ********************************************************************************
	~CEditManager(void);
public:
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/02</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/02</changed>
	// ********************************************************************************
	static CEditManager& GetManager(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/02</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/02</changed>
	// ********************************************************************************
	void Initailize(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/02</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/02</changed>
	// ********************************************************************************
	void Update(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/02</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/02</changed>
	// ********************************************************************************
	void Render(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/02</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/02</changed>
	// ********************************************************************************
	void Release(void);

	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/04</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/04</changed>
	// ********************************************************************************
	void UpdateList(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/04</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/04</changed>
	// ********************************************************************************
	void AddAnim(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <created>Ç¢ÇÃÇ§Ç¶,2020/03/04</created>
	/// <changed>Ç¢ÇÃÇ§Ç¶,2020/03/04</changed>
	// ********************************************************************************
	void DeleteAnim(void);
};

#define theEditManager CEditManager::GetManager()

