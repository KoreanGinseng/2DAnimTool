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