#include "Button.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/29</changed>
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
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CButton::~CButton(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �{�^������
	/// </summary>
	/// <returns>�{�^���̃|�C���^</returns>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	LPButton CButton::CreateButton(void)
	{
		LPButton p = std::make_shared<CButton>();
		return p;
	}
	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/29</changed>
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
		//�}�E�X�I�[�o�[�`��
		if (IsMouseOver() || IsHold())
		{
			backColor = m_BackColorOver;
			lineColor = m_LineColorOver;
		}
		//�����Ă�Ԃ̕`��
		if (IsHold())
		{
			backColor = m_PushBackColor;
			lineColor = m_PushLineColor;
		}
		//�y��`��
		CGraphicsUtilities::RenderFillRect(rect, backColor);
		//�g�`��
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(rect, lineColor);
		}

		//�����`��
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
	/// �����Ă���Ԃ̐F�̐ݒ�
	/// </summary>
	/// <param name="color">�F</param>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CButton::SetPushBackColor(const MofU32 & color)
	{
		m_PushBackColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// �����Ă���Ԃ̐��̐F�̐ݒ�
	/// </summary>
	/// <param name="color">�F</param>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CButton::SetPushLineColor(const MofU32 & color)
	{
		m_PushLineColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// �w�i�F�̐ݒ�(�}�E�X�I�[�o�[��)
	/// </summary>
	/// <param name="color">�F</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CButton::SetBackColorOver(const MofU32 & color)
	{
		m_BackColorOver = color;
	}
	// ********************************************************************************
	/// <summary>
	/// �g���̐F�̐ݒ�(�}�E�X�I�[�o�[��)
	/// </summary>
	/// <param name="color">�F</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CButton::SetLineColorOver(const MofU32 & color)
	{
		m_LineColorOver = color;
	}
}