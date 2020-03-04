#include "CheckBox.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/25</created>
	/// <changed>���̂���,2020/02/25</changed>
	// ********************************************************************************
	CCheckBox::CCheckBox(void) :
		m_bCheck(FALSE)
	{
		m_bLineShow = FALSE;
		m_BackColor = m_LineColor;
		m_TextColor = MOF_COLOR_WHITE;
	}
	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/25</created>
	/// <changed>���̂���,2020/02/25</changed>
	// ********************************************************************************
	CCheckBox::~CCheckBox(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �`�F�b�N�{�b�N�X����
	/// </summary>
	/// <param name="info">�������</param>
	/// <returns>�`�F�b�N�{�b�N�X</returns>
	/// <created>���̂���,2020/02/25</created>
	/// <changed>���̂���,2020/02/25</changed>
	// ********************************************************************************
	LPCheckBox ToolControll::CCheckBox::CreateCheckBox(void)
	{
		std::shared_ptr<CCheckBox> p = std::make_shared<CCheckBox>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CCheckBox::Update(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		if (IsPush())
		{
			m_bCheck = !m_bCheck;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CCheckBox::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		////�v�Z�p��`
		CRectangle rect = GetRect();
		//�ŏ��l�𒷂��ɂ���
		float r = MOF_MIN(GetRect().GetWidth(), GetRect().GetHeight());
		//�`�F�b�N�{�b�N�X�p��`
		CRectangle box(rect.Left, rect.Top, rect.Left + r, rect.Top + r);
		//�ʏ�F
		MofU32 color = m_LineColor;
		//�`�F�b�N�����Ă���Ƃ��͓h��Ԃ�
		if (m_bCheck)
		{
			CGraphicsUtilities::RenderFillRect(box, m_BackColor);
		}
		//�g��`��
		CGraphicsUtilities::RenderRect(box, color);
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(rect, color);
		}
		CRectangle outRect;
		m_Font.CalculateStringRect(0, 0, m_Text.GetString(), outRect);
		float offY = (rect.GetHeight() - outRect.GetHeight()) * 0.5f;
		//�g�̉��ɕ�����`��
		m_Font.RenderFormatString(
			box.Right + m_Font.GetSize() * 0.5f,
			box.Top + offY, m_TextColor, m_Text.GetString()
		);
	}
	// ********************************************************************************
	/// <summary>
	/// �`�F�b�N����Ă��邩�ǂ���
	/// </summary>
	/// <returns>�`�F�b�N�t���O</returns>
	/// <created>���̂���,2020/02/25</created>
	/// <changed>���̂���,2020/02/25</changed>
	// ********************************************************************************
	MofBool CCheckBox::IsCheck(void) const
	{
		return (m_bCheck);
	}
}
