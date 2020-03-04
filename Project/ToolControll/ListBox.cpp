#include "ListBox.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CListBox::CListBox(void) :
		CControll(),
		m_pTemplate(nullptr),
		m_pScrollBar(nullptr),
		m_List(),
		m_Select(-1),
		m_PrevSelect(-1)
	{
		m_BackColor = MOF_COLOR_WHITE;
	}
	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CListBox::~CListBox(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�{�b�N�X�̐���
	/// </summary>
	/// <returns>���X�g�{�b�N�X�̃|�C���^</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	LPListBox CListBox::CreateListBox(void)
	{
		std::shared_ptr<CListBox> p = std::make_shared<CListBox>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// ������
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Initialize(void)
	{
		if (!m_pTemplate)
		{
			m_pTemplate = CLabel::CreateLabel();
			CControll::CreateInfo tmp = {
				m_Pos,
				Vector2(m_Size.x - 10, 24),
				"List"
			};
			m_pTemplate->FontCreate(24, "");
			m_pTemplate->SetInfo(tmp);
		}
		if (!m_pScrollBar)
		{
			m_pScrollBar = CScrollBar::CreateScrollBar();
			CControll::CreateInfo sbci = {
				m_Pos,
				m_Size,
				""
			};
			m_pScrollBar->SetInfo(sbci);
			m_pScrollBar->FontCreate(24, "");
			m_pScrollBar->SetWidth(10);
			m_pScrollBar->SetScrlArea(m_pScrollBar->GetRect(), 0);
			m_pScrollBar->Initialize();
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Update(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		//�I��ԍ��̍X�V
		m_PrevSelect = m_Select;
		//�X�N���[���o�[�̍X�V
		m_pScrollBar->Update();
		//�X�N���[���ɑΉ������ꏊ�ɕϊ�
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			if (!m_List[i])
			{
				continue;
			}
			Vector2 pos = m_pTemplate->GetPos();
			pos.y += (i * m_pTemplate->GetSize().y);
			pos.y -= m_pScrollBar->GetScroll();
			m_List[i]->SetPos(pos);
		}
		//�}�E�X�N���b�N�Ő��I��
		Vector2 mousePos;
		g_pInput->GetMousePos(mousePos);
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			if (!IsMouseOver())
			{
				break;
			}
			if (!m_List[i])
			{
				continue;
			}
			if (!m_List[i]->IsPush())
			{
				continue;
			}
			m_Select = i;
			break;
		}
		//�I������Ă���̂��킩��悤�ɐF��t����
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			if (!m_List[i])
			{
				continue;
			}
			if (m_Select == i)
			{
				m_List[i]->SetBackColor(MOF_COLOR_BLUE);
				m_List[i]->SetTextColor(MOF_COLOR_WHITE);
			}
			else
			{
				m_List[i]->SetBackColor(MOF_COLOR_WHITE);
				m_List[i]->SetTextColor(MOF_COLOR_BLACK);
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		//�X�e���V���o�b�t�@�̗L����
		g_pGraphics->SetStencilEnable(TRUE);
		//�X�e���V���o�b�t�@�̒u������
		g_pGraphics->SetStencilControl(COMPARISON_ALWAYS,
			STENCIL_REPLACE, STENCIL_REPLACE, STENCIL_REPLACE);
		//�X�e���V���o�b�t�@�̒l�ύX
		g_pGraphics->SetStencilValue(255);
		//�w�i�̕`��
		CGraphicsUtilities::RenderFillRect(GetRect(), m_BackColor);
		//�X�e���V���o�b�t�@�̐ݒ�
		g_pGraphics->SetStencilControl(COMPARISON_LESS,
			STENCIL_KEEP, STENCIL_KEEP, STENCIL_KEEP);
		//�X�e���V���o�b�t�@�̒l�ύX
		g_pGraphics->SetStencilValue(254);
		//���X�g�̕������`��
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			if (!m_List[i])
			{
				continue;
			}
			m_List[i]->Render();
		}
		//�X�e���V���o�b�t�@�̖�����
		g_pGraphics->SetStencilEnable(FALSE);
		//�X�N���[���o�[�̕`��
		m_pScrollBar->Render();
	}
	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Release(void)
	{
		m_pTemplate = nullptr;
		m_pScrollBar = nullptr;
		for (int i = 0; i < m_List.GetArrayCount(); i++)
		{
			m_List[i] = nullptr;
		}
		m_List.Release();
	}
	// ********************************************************************************
	/// <summary>
	/// �e���v�����x���̎擾
	/// </summary>
	/// <returns>���x��</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	LPLabel CListBox::GetTemplateLabel(void)
	{
		return m_pTemplate;
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[���o�[�̎擾
	/// </summary>
	/// <returns>�X�N���[���o�[</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	LPScrollBar CListBox::GetScrollBar(void)
	{
		return m_pScrollBar;
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�ɒǉ�
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Add(void)
	{
		AddLast(m_pTemplate->GetText());
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�ɒǉ�
	/// </summary>
	/// <param name="str">������</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Add(const CString & str)
	{
		AddLast(str);
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̐擪�ɒǉ�
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddFast(void)
	{
		AddNo(m_pTemplate->GetText(), 0);
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̐擪�ɒǉ�
	/// </summary>
	/// <param name="str">������</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddFast(const CString & str)
	{
		AddNo(str, 0);
	}
	// ********************************************************************************
	/// <summary>
	/// �w��ԍ��ɒǉ�
	/// </summary>
	/// <param name="no">�ԍ�</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddNo(const MofU32 & no)
	{
		AddNo(m_pTemplate->GetText(), 0);
	}
	// ********************************************************************************
	/// <summary>
	/// �w��ԍ��ɒǉ�
	/// </summary>
	/// <param name="str">������</param>
	/// <param name="no">�ԍ�</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddNo(const CString & str, const MofU32 & no)
	{
		if (m_Select < 0)
		{
			m_Select = 0;
			m_PrevSelect = 0;
		}
		LPLabel tmp = CLabel::CreateLabel();
		CControll::CreateInfo info = {
			m_pTemplate->GetPos(),
			m_pTemplate->GetSize(),
			str
		};
		tmp->FontCreate(m_pTemplate->GetFontSize(), "");
		tmp->SetInfo(info);
		tmp->SetTextColor(MOF_COLOR_BLACK);
		tmp->SetBackColor(MOF_COLOR_WHITE);
		tmp->SetBackShow(TRUE);
		Vector2 pos = info.Pos;
		int c = m_List.GetArrayCount();
		float s = info.Size.y;
		pos.y += c * s;
		tmp->SetPos(pos);
		m_List.AddNo(tmp, no);
		m_pScrollBar->ChangeMaxSize(s + c * s);
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̍Ō���ɒǉ�
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddLast(void)
	{
		AddNo(m_pTemplate->GetText(), m_List.GetArrayCount());
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̍Ō���ɒǉ�
	/// </summary>
	/// <param name="str">������</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::AddLast(const CString & str)
	{
		AddNo(str, m_List.GetArrayCount());
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̍Ō�����폜
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Delete(void)
	{
		DeleteLast();
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̐擪���폜
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::DeleteFast(void)
	{
		DeleteNo(0);
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̎w��ԍ����폜
	/// </summary>
	/// <param name="no">�폜</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::DeleteNo(const MofU32 & no)
	{
		m_List.Delete(no);
		int c = m_List.GetArrayCount();
		float s = m_pTemplate->GetSize().y;
		m_pScrollBar->ChangeMaxSize(c * s);
		if (m_Select < 0)
		{
			return;
		}
		if (no <= m_Select)
		{
			m_Select--;
			m_PrevSelect--;
		}
		else if (m_Select >= m_List.GetArrayCount())
		{
			m_Select = m_List.GetArrayCount() - 1;
			m_PrevSelect = m_List.GetArrayCount() - 1;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̍Ō�����폜
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::DeleteLast(void)
	{
		DeleteNo(m_List.GetArrayCount() - 1);
	}
	// ********************************************************************************
	/// <summary>
	/// ����ւ�
	/// </summary>
	/// <param name="idx1">����ւ��郊�X�g�ԍ��P</param>
	/// <param name="idx2">����ւ��郊�X�g�ԍ��Q</param>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CListBox::Swap(const MofU32 & idx1, const MofU32 & idx2)
	{
		MofBool b = m_List.Swap(idx1, idx2);
		if (!b)
		{
			return;
		}
		if (m_Select == idx1)
		{
			m_Select = idx2;
			m_PrevSelect = idx2;
		}
		else if (m_Select == idx2)
		{
			m_Select = idx1;
			m_PrevSelect = idx1;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// ���ݑI�𒆂̔ԍ��擾
	/// </summary>
	/// <returns>���ݑI�𒆂̔ԍ�</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	MofInt CListBox::GetSelectNo(void) const
	{
		return m_Select;
	}
	// ********************************************************************************
	/// <summary>
	/// ���ݑI�𒆂̕�����擾
	/// </summary>
	/// <returns>������</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CString CListBox::GetText(void) const
	{
		if (m_Select < 0)
		{
			return "";
		}
		return m_List[m_Select]->GetText();
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̎w��ԍ��̕�����擾
	/// </summary>
	/// <param name="no">�w��ԍ�</param>
	/// <returns>������</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	CString CListBox::GetText(const MofInt & no) const
	{
		return m_List[no]->GetText();
	}
	// ********************************************************************************
	/// <summary>
	/// ���X�g�̑I��ԍ����ς�����t���O�擾
	/// </summary>
	/// <returns>���X�g�̑I��ԍ����ς�����t���O</returns>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	MofBool CListBox::IsChenged(void) const
	{
		return (m_PrevSelect != m_Select);
	}
}