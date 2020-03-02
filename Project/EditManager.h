#pragma once
#include	"Mof.h"
#include	"AreaManager.h"
#include	"ToolControll.h"

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
			info.Pos.x = txtBox.GetRect().Right;
			info.Size.x = 20;
			info.Size.y *= 0.5f;
			info.Text = "Å£";
			btnUp.FontCreate(16, "");
			btnUp.SetInfo(info);
			info.Pos.y = btnUp.GetRect().Bottom;
			info.Text = "Å•";
			btnDown.FontCreate(16, "");
			btnDown.SetInfo(info);
		}
	};
	CTextBox	m_tbName;
	NumBox		m_nbOffSetX;
	NumBox		m_nbOffSetY;
	NumBox		m_nbWidth;
	NumBox		m_nbHeight;
	CCheckBox	m_cbLoop;
	CButton		m_btnPlay;
	NumBox		m_nbComa;
	NumBox		m_nbAllFlame;
	CButton		m_btnChange;
	CButton		m_btnPrev;
	CButton		m_btnNext;
	CLabel		m_lblComa;
	NumBox		m_nbFlame;
	NumBox		m_nbNo;
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
};

