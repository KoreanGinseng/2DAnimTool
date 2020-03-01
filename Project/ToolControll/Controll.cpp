#include "Controll.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
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
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CControll::~CControll(void)
	{
		m_Font.Release();
	}
	// ********************************************************************************
	/// <summary>
	/// �������̐ݒ�
	/// </summary>
	/// <param name="info">�������</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetInfo(CreateInfo info)
	{
		SetPos(info.Pos);
		SetSize(info.Size);
		SetText(info.Text);
	}
	// ********************************************************************************
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetPos(const Vector2 & pos)
	{
		m_Pos = pos;
	}
	// ********************************************************************************
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetPos(const float & x, const float & y)
	{
		SetPos(Vector2(x, y));
	}
	// ********************************************************************************
	/// <summary>
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetSize(const Vector2 & size)
	{
		m_Size = size;
	}
	// ********************************************************************************
	/// <summary>
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="w">����</param>
	/// <param name="h">����</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetSize(const float & w, const float & h)
	{
		SetSize(Vector2(w, h));
	}
	// ********************************************************************************
	/// <summary>
	/// �t�H���g�̐���
	/// </summary>
	/// <param name="s">�t�H���g�T�C�Y</param>
	/// <param name="pFace">����</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::FontCreate(const MofS32 s, LPCMofChar pFace)
	{
		m_Font.Release();
		m_FontSize = s;
		m_Font.Create(s, pFace);
	}
	// ********************************************************************************
	/// <summary>
	/// �e�L�X�g�̐ݒ�
	/// </summary>
	/// <param name="pText">�e�L�X�g</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetText(CString text)
	{
		m_Text = text;
	}
	// ********************************************************************************
	/// <summary>
	/// �t�H���g�T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="s">�T�C�Y</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetFontSize(const MofS32 s)
	{
		m_FontSize = s;
		m_Font.SetSize(s);
	}
	// ********************************************************************************
	/// <summary>
	/// �g���\���t���O�̐ݒ�
	/// </summary>
	/// <param name="b">�t���O</param>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetLineShow(const MofBool & b)
	{
		m_bLineShow = b;
	}
	// ********************************************************************************
	/// <summary>
	/// �`��t���O�̐ݒ�
	/// </summary>
	/// <param name="b">�t���O</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetShow(const MofBool & b)
	{
		m_bShow = b;
	}
	// ********************************************************************************
	/// <summary>
	/// �w�i�F�̐ݒ�
	/// </summary>
	/// <param name="color">�F</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetBackColor(const MofU32 & color)
	{
		m_BackColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// �g���̐F�̐ݒ�
	/// </summary>
	/// <param name="color">�F</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetLineColor(const MofU32 & color)
	{
		m_LineColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// �e�L�X�g�̕\���F�̐ݒ�
	/// </summary>
	/// <param name="color">�F</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CControll::SetTextColor(const MofU32 & color)
	{
		m_TextColor = color;
	}
	// ********************************************************************************
	/// <summary>
	/// ��`�擾
	/// </summary>
	/// <returns>��`</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CRectangle CControll::GetRect(void) const
	{
		return CRectangle(m_Pos, m_Pos + m_Size);
	}
	// ********************************************************************************
	/// <summary>
	/// �}�E�X���d�Ȃ��Ă��邩�̃t���O�擾
	/// </summary>
	/// <returns>�}�E�X���d�Ȃ��Ă��邩</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
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
	/// �}�E�X���{�^���ŉ������u�Ԃ̃t���O�擾
	/// </summary>
	/// <returns>�}�E�X���{�^���ŉ������u�Ԃ̃t���O</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
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
	/// �}�E�X���{�^���ŉ�����Ă��邩�̃t���O�擾
	/// </summary>
	/// <returns>�}�E�X���{�^���ŉ�����Ă��邩�̃t���O</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
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
	/// �}�E�X���{�^�������ꂽ�u�Ԃ̃t���O�擾
	/// </summary>
	/// <returns>�}�E�X���{�^�������ꂽ�u�Ԃ̃t���O</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
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
	/// �`��t���O�̎擾
	/// </summary>
	/// <returns>�`��t���O</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	MofBool CControll::IsShow(void) const
	{
		return m_bShow;
	}
	// ********************************************************************************
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	Vector2 CControll::GetPos(void) const
	{
		return m_Pos;
	}
	// ********************************************************************************
	/// <summary>
	/// �T�C�Y�̎擾
	/// </summary>
	/// <returns>�T�C�Y</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	Vector2 CControll::GetSize(void) const
	{
		return m_Size;
	}
	// ********************************************************************************
	/// <summary>
	/// �e�L�X�g�̎擾
	/// </summary>
	/// <returns>�e�L�X�g</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CString CControll::GetText(void) const
	{
		return m_Text;
	}
	// ********************************************************************************
	/// <summary>
	/// �t�H���g�T�C�Y�̎擾
	/// </summary>
	/// <returns>�t�H���g�T�C�Y</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	MofS32 CControll::GetFontSize(void) const
	{
		return m_FontSize;
	}
}