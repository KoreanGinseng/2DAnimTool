#include "TextBox.h"
#include "../WindowProc.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
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
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	CTextBox::~CTextBox(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �e�L�X�g�{�b�N�X�����N���X
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	LPTextBox CTextBox::CreateTextBox(void)
	{
		std::shared_ptr<CTextBox> p = std::make_shared<CTextBox>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// �e�L�X�g�{�b�N�X�̐��䃊�X�g�擾
	/// </summary>
	/// <returns>���䃊�X�g</returns>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	CDynamicArray<CTextBox*>& CTextBox::GetList(void)
	{
		static CDynamicArray<CTextBox*> list;
		return list;
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̉��
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
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
	/// ImeInput�̍X�V
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
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
	/// ������
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::Initialize(void)
	{
		g_pImeInput->SetEnable(FALSE);
		g_pImeInput->SetInputString("");
	}
	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::Update(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		//�g�O�N���b�N�œ��͒��f
		if (m_bInput && (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !IsMouseOver()))
		{
			g_pImeInput->GetInputImeString(m_Text);
			g_pImeInput->ResetInput();
			g_pImeInput->SetEnable(FALSE);
			//���f���������Ȃ��ꍇ���������Ă���
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
		//�����݂̂̏���
		NumUpdate();
		//�N���b�N���ꂽ�Ƃ����͏�Ԃɂ���
		if (IsPush() && !m_bInput)
		{
			m_bInput = TRUE;
			m_Font.SetBold(0);
		}
		//�m�蕶��������ꍇ�������ǉ�����
		if (m_bInput && g_pImeInput->GetEnterString()->GetLength() > 0)
		{
			m_Text += g_pImeInput->GetEnterString()->GetString();
			g_pImeInput->ResetEnterString();
			g_pImeInput->SetEnable(FALSE);
			m_Font.SetBold(600);
			m_bInput = FALSE;
		}
		//�J�[�\���̏���
		CursorUpdate();
	}
	// ********************************************************************************
	/// <summary>
	/// �J�[�\���̍X�V
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::CursorUpdate(void)
	{
		//�_�ŗp�J�E���g
		if (--m_CursorTime < 0)
		{
			m_CursorTime = 60;
		}
		//���͒��Ȃ�J�[�\���̏ꏊ���v�Z����
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
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		CRectangle rect = GetRect();
		//�y��̕`��
		CGraphicsUtilities::RenderFillRect(rect, m_BackColor);
		//�g�̕`��
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(rect, m_LineColor);
		}
		//�J�[�\���̕`��
		if (m_CursorTime % 60 < 30 && m_bInput)
		{
			CGraphicsUtilities::RenderLine(
				rect.GetTopLeft() + Vector2(m_CursorPos + 2, 2),
				rect.GetBottomLeft() + Vector2(m_CursorPos + 2, -2),
				m_TextColor
			);
		}
		//���͒��Ȃ班�������������グ��
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
		//�����݂̂ŃG���[���������Ă���ꍇ������������Ă���
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
		//�����̕`��
		m_Font.RenderString(rect.Left + offsetX, rect.Top + offsetY, m_TextColor, str.GetString());
	}
	// ********************************************************************************
	/// <summary>
	/// ���̓t���O�̐ݒ�
	/// </summary>
	/// <param name="b">�t���O</param>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::SetInput(const MofBool & b)
	{
		m_bInput = b;
	}
	// ********************************************************************************
	/// <summary>
	/// ���̓t���O�̎擾
	/// </summary>
	/// <returns>���̓t���O</returns>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	MofBool CTextBox::IsInput(void) const
	{
		return m_bInput;
	}
	// ********************************************************************************
	/// <summary>
	/// �����̂݃t���O�̐ݒ�
	/// </summary>
	/// <param name="b">�t���O</param>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::SetNumOnly(const MofBool & b)
	{
		m_bNumOnly = b;
		m_Text = "0";
	}
	// ********************************************************************************
	/// <summary>
	/// �����̂݃t���O�̎擾
	/// </summary>
	/// <returns>�t���O</returns>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	MofBool CTextBox::IsNumOnly(void) const
	{
		return m_bNumOnly;
	}
	// ********************************************************************************
	/// <summary>
	/// �����݂̂̏ꍇ�̐���
	/// </summary>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::NumUpdate(void)
	{
		if (!m_bNumOnly)
		{
			return;
		}
		//�G���[������
		m_Error &= ~m_Error;
		//���͒��Ȃ�G���[���Ď�
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
			//�G���[�`�F�b�N
			try 
			{
				std::stof(str.GetString());
			}
			//�ϊ����s
			catch (const std::invalid_argument&) 
			{
				m_Error |= NE_NOCONVERSION;
				g_pImeInput->SetInputString("0");
			}
			//�I�[�o�[�t���[
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
	/// �����̎擾
	/// </summary>
	/// <returns></returns>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	MofFloat CTextBox::GetNum(void) const
	{
		//�����񂩂琔�����擾
		//���s�����ꍇ0���Ԃ�
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
	/// �����̐ݒ�
	/// </summary>
	/// <param name="num">����</param>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
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
	/// �����̉��Z����
	/// </summary>
	/// <param name="num">����</param>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::AddNum(const MofFloat & num)
	{
		SetNum(GetNum() + num);
	}
	// ********************************************************************************
	/// <summary>
	/// �����̌��Z����
	/// </summary>
	/// <param name="num">����</param>
	/// <created>���̂���,2020/03/01</created>
	/// <changed>���̂���,2020/03/01</changed>
	// ********************************************************************************
	void CTextBox::SubNum(const MofFloat & num)
	{
		AddNum(-num);
	}
	// ********************************************************************************
	/// <summary>
	/// �`��ʒu�̐ݒ�
	/// </summary>
	/// <param name="align">�`��ʒu</param>
	/// <created>���̂���,2020/03/03</created>
	/// <changed>���̂���,2020/03/03</changed>
	// ********************************************************************************
	void CTextBox::SetTxtAlign(const TxtAlign & align)
	{
		m_TxtAlign = align;
	}
	// ********************************************************************************
	/// <summary>
	/// �ŏ��l�ƍő�l�̐ݒ�
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <created>���̂���,2020/03/03</created>
	/// <changed>���̂���,2020/03/03</changed>
	// ********************************************************************************
	void CTextBox::SetNumMinMax(const MofInt & min, const MofInt & max)
	{
		m_NumMin = min;
		m_NumMax = max;
	}
}