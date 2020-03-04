#include "Label.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/25</created>
	/// <changed>���̂���,2020/02/29</changed>
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
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/25</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CLabel::~CLabel(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// ���x���̐���
	/// </summary>
	/// <returns>���x���|�C���^</returns>
	/// <created>���̂���,2020/02/25</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	LPLabel CLabel::CreateLabel(void)
	{
		std::shared_ptr<CLabel> p = std::make_shared<CLabel>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CLabel::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		CRectangle rect = GetRect();
		if (m_bBackShow)
		{
			CGraphicsUtilities::RenderFillRect(rect, m_BackColor);
		}
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(rect, m_LineColor);
		}
		CRectangle outRect;
		m_Font.CalculateStringRect(0, 0, m_Text.GetString(), outRect);
		float offY = (rect.GetHeight() - outRect.GetHeight()) * 0.5f;
		m_Font.RenderFormatString(rect.Left, rect.Top + offY, m_TextColor, m_Text);
	}
	// ********************************************************************************
	/// <summary>
	/// �w�i�F�`��t���O�̐ݒ�
	/// </summary>
	/// <param name="b">�t���O</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CLabel::SetBackShow(const MofBool & b)
	{
		m_bBackShow = b;
	}
}