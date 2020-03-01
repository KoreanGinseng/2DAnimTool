#include "ScrollBar.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	CScrollBar::CScrollBar(void) :
		m_pBtnUp(nullptr),
		m_pBtnScrl(nullptr),
		m_pBtnDown(nullptr),
		m_ScrlArea(),
		m_ScrlBar(),
		m_Type(SCRLTYPE_VIRTICAL),
		m_MaxSize(0),
		m_ScrlWidth(0),
		m_ScrlParPix(0.0f),
		m_Scroll(0),
		m_bBarHold(FALSE)
	{
		m_bLineShow = FALSE;
		m_BackColor = MOF_COLOR_CBLACK;
		m_LineColor = MOF_COLOR_RED;
	}
	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	CScrollBar::~CScrollBar(void)
	{
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[���o�[�̐���
	/// </summary>
	/// <param name="info">�������</param>
	/// <returns>�X�N���[���o�[�|�C���^</returns>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	LPScrollBar CScrollBar::CreateScrollBar(void)
	{
		std::shared_ptr<CScrollBar> p = std::make_shared<CScrollBar>();
		return (p);
	}
	// ********************************************************************************
	/// <summary>
	/// ������
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::Initialize(void)
	{
		//�X�N���[���l�̏�����
		m_Scroll = 0;
		//�o�[�̃T�C�Y���v�Z
		InitBarSize();
		//�{�^���̐���
		CreateButton();
		//�X���C�h�o�[�̈ʒu�̏�����
		InitBarPos();
		//�X���C�h�o�[�̒�����������
		InitBarLength();
	}
	// ********************************************************************************
	/// <summary>
	/// �X�V
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::Update(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}

		//�}�E�X�ɂ��X���C�h����
		MoveMouse();

		//�}�E�X�z�C�[���ɂ��X���C�h����
		MoveWheel();
		
		//�㉺�{�^���ɂ��X���C�h����
		MoveButton();

		//�X�N���[���l�̐���
		CheckOverScroll();

		//�ʒu�̍Čv�Z
		UpdateBarPos();
	}
	// ********************************************************************************
	/// <summary>
	/// �`��
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::Render(void)
	{
		if (!this || !m_bShow)
		{
			return;
		}
		//�y��̕`��
		CGraphicsUtilities::RenderFillRect(m_ScrlBar, m_BackColor);
		if (m_bLineShow)
		{
			CGraphicsUtilities::RenderRect(m_ScrlArea, m_LineColor);
		}
		//�e�{�^���̕`��
		m_pBtnUp->Render();
		m_pBtnScrl->Render();
		m_pBtnDown->Render();
	}
	// ********************************************************************************
	/// <summary>
	/// ���
	/// </summary>
	/// <created>���̂���,2020/02/24</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::Release(void)
	{
		m_pBtnUp = nullptr;
		m_pBtnScrl = nullptr;
		m_pBtnDown = nullptr;
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[�������̐ݒ�
	/// </summary>
	/// <param name="t">�X�N���[������</param>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::SetType(ScrlType t)
	{
		m_Type = t;
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[���o�[�̕��̐ݒ�
	/// </summary>
	/// <param name="w">��</param>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::SetWidth(const int & w)
	{
		m_ScrlWidth = w;
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[������G���A�̐ݒ�
	/// </summary>
	/// <param name="area">�G���A��`</param>
	/// <param name="maxSize">�X�N���[���ő�l</param>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	void CScrollBar::SetScrlArea(const CRectangle & area, const int & maxSize)
	{
		m_ScrlArea = area;
		m_MaxSize = maxSize;
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[���ő�l�̕ύX
	/// </summary>
	/// <param name="maxSize">�ő�l</param>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::ChangeMaxSize(const int & maxSize)
	{
		m_MaxSize = maxSize;
		InitBarLength();
		CheckOverScroll();
		UpdateBarPos();
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[���G���A�̎擾
	/// </summary>
	/// <returns>�X�N���[���G���A</returns>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	CRectangle CScrollBar::GetScrlAreaRect(void) const
	{
		return m_ScrlArea;
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[���l�̎擾
	/// </summary>
	/// <returns></returns>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	float CScrollBar::GetScroll(void) const
	{
		return (m_Scroll * m_ScrlParPix);
	}
	// ********************************************************************************
	/// <summary>
	/// ��{�^���̎擾
	/// </summary>
	/// <returns>��{�^��</returns>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	LPButton CScrollBar::GetBtnUp(void)
	{
		return m_pBtnUp;
	}
	// ********************************************************************************
	/// <summary>
	/// �X���C�h�{�^���̎擾
	/// </summary>
	/// <returns>�X���C�h�{�^��</returns>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	LPButton CScrollBar::GetBtnScrl(void)
	{
		return m_pBtnScrl;
	}
	// ********************************************************************************
	/// <summary>
	/// ���{�^���̎擾
	/// </summary>
	/// <returns>���{�^��</returns>
	/// <created>���̂���,2020/02/28</created>
	/// <changed>���̂���,2020/02/28</changed>
	// ********************************************************************************
	LPButton CScrollBar::GetBtnDown(void)
	{
		return m_pBtnDown;
	}
	// ********************************************************************************
	/// <summary>
	/// �e�{�^���̐���
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::CreateButton(void)
	{
		CControll::CreateInfo info;
		info.Pos = m_ScrlBar.GetTopLeft();
		info.Size = m_ScrlBar.GetBottomRight() - m_ScrlBar.GetTopLeft();
		//�㉺�{�^���̍쐬
		if (!m_pBtnUp)
		{
			m_pBtnUp = CButton::CreateButton();
			m_pBtnScrl = CButton::CreateButton();
			m_pBtnDown = CButton::CreateButton();
			m_pBtnUp->SetInfo(info);
			m_pBtnScrl->SetInfo(info);
			m_pBtnDown->SetInfo(info);
		}
		//�㉺�{�^���̃T�C�Y���m�肷��
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			m_pBtnUp->SetSize(m_ScrlWidth, info.Size.y);
			m_pBtnDown->SetPos((info.Pos.x + info.Size.x) - m_ScrlWidth, info.Pos.y);
			m_pBtnDown->SetSize(m_ScrlWidth, info.Size.y);
			break;
		case SCRLTYPE_VIRTICAL:
			m_pBtnUp->SetSize(info.Size.x, m_ScrlWidth);
			m_pBtnDown->SetPos(info.Pos.x, (info.Pos.y + info.Size.y) - m_ScrlWidth);
			m_pBtnDown->SetSize(info.Size.x, m_ScrlWidth);
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �o�[�̃T�C�Y�̏�����
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::InitBarSize(void)
	{
		//�X�N���[���G���A����X�N���[���o�[�̃T�C�Y���쐬
		m_ScrlBar = m_ScrlArea;
		//�G���A�̓����ɖ��ߍ���
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			m_ScrlBar.Top = m_ScrlBar.Bottom - m_ScrlWidth;
			break;
		case SCRLTYPE_VIRTICAL:
			m_ScrlBar.Left = m_ScrlBar.Right - m_ScrlWidth;
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �X���C�h�{�^���̈ʒu�̏�����
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::InitBarPos(void)
	{
		//�X�N���[���{�^���̈ʒu���m��
		m_pBtnScrl->SetPos(m_pBtnUp->GetPos());
		Vector2 scPos;
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			scPos = Vector2(m_pBtnScrl->GetPos().x + m_pBtnUp->GetSize().x, m_pBtnScrl->GetPos().y);
			m_pBtnScrl->SetPos(scPos);
			break;
		case SCRLTYPE_VIRTICAL:
			scPos = Vector2(m_pBtnScrl->GetPos().x, m_pBtnScrl->GetPos().y + m_pBtnUp->GetSize().y);
			m_pBtnScrl->SetPos(scPos);
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �X���C�h�{�^���̒���������
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::InitBarLength(void)
	{
		//�X�N���[���G���A�̕����擾
		int areaw;
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			areaw = m_ScrlArea.GetWidth();
			break;
		case SCRLTYPE_VIRTICAL:
			areaw = m_ScrlArea.GetHeight();
			break;
		}
		//�X�N���[���{�^���̒������v�Z����
		int scrlw = areaw - m_ScrlWidth * 2;
		if (m_MaxSize <= areaw)
		{
			m_ScrlParPix = 0;
		}
		else
		{
			//�X�N���[���{�^���̃T�C�Y���v�Z����
			scrlw *= (static_cast<float>(areaw) / m_MaxSize);
			//�{�^���̃T�C�Y���ŏ��ȉ��ɂȂ�����X�N���[���|�C���g�𑝂₵�Ē�������
			if (scrlw <= m_ScrlWidth)
			{
				scrlw = m_ScrlWidth;
			}
			//1pixcel�Ɉړ�����X�N���[���ʂ��v�Z����
			//�v�Z�� : �����ĂȂ������̒��� / �X�N�����{�^���̃G���A�̒��� - �X�N���[���{�^���̒���
			m_ScrlParPix = (m_MaxSize - areaw) / ((areaw - m_ScrlWidth * 2.0f) - scrlw);
		}
		//�X�N���[���{�^���̕���ݒ肷��
		Vector2 size = m_pBtnUp->GetSize();
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			m_pBtnScrl->SetSize(scrlw, size.y);
			break;
		case SCRLTYPE_VIRTICAL:
			m_pBtnScrl->SetSize(size.x, scrlw);
			break;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �}�E�X�ł̃X�N���[������
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::MoveMouse(void)
	{
		Vector2 move;
		g_pInput->GetMouseMove(move.x, move.y);
		//�X�N���[���{�^������
		if (m_pBtnScrl->IsPush())
		{
			m_bBarHold = TRUE;
		}
		if (m_bBarHold)
		{
			switch (m_Type)
			{
			case SCRLTYPE_HORIZONTAL:
				m_Scroll += move.x;
				break;
			case SCRLTYPE_VIRTICAL:
				m_Scroll += move.y;
				break;
			}
		}
		if (g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
		{
			m_bBarHold = FALSE;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �}�E�X�z�C�[���ł̃X�N���[������
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::MoveWheel(void)
	{
		Vector2 mousePos;
		g_pInput->GetMousePos(mousePos);
		//�X�N���[������
		float movew = g_pInput->GetMouseWheelMove();
		if (m_ScrlArea.CollisionPoint(mousePos) && movew != 0)
		{
			switch (m_Type)
			{
			case SCRLTYPE_HORIZONTAL:
				if (g_pInput->IsKeyHold(MOFKEY_LCONTROL))
				{
					m_Scroll -= movew;
				}
				break;
			case SCRLTYPE_VIRTICAL:
				if (!g_pInput->IsKeyHold(MOFKEY_LCONTROL))
				{
					m_Scroll -= movew;
				}
				break;
			}
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �㉺�{�^���ł̃X�N���[������
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::MoveButton(void)
	{
		//�㉺�{�^������
		if (m_pBtnUp->IsHold())
		{
			m_Scroll--;
		}
		else if (m_pBtnDown->IsHold())
		{
			m_Scroll++;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �X�N���[���l�̐���
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::CheckOverScroll(void)
	{
		int areaw;
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			areaw = m_ScrlArea.GetWidth() - m_pBtnScrl->GetSize().x;
			break;
		case SCRLTYPE_VIRTICAL:
			areaw = m_ScrlArea.GetHeight() - m_pBtnScrl->GetSize().y;
			break;
		}
		if (m_Scroll < 0)
		{
			m_Scroll = 0;
		}
		else if (m_Scroll > areaw - m_ScrlWidth * 2)
		{
			m_Scroll = areaw - m_ScrlWidth * 2;
		}
	}
	// ********************************************************************************
	/// <summary>
	/// �ʒu�̍Čv�Z
	/// </summary>
	/// <created>���̂���,2020/02/29</created>
	/// <changed>���̂���,2020/02/29</changed>
	// ********************************************************************************
	void CScrollBar::UpdateBarPos(void)
	{
		switch (m_Type)
		{
		case SCRLTYPE_HORIZONTAL:
			m_pBtnScrl->SetPos(m_pBtnUp->GetRect().Right + m_Scroll, m_pBtnScrl->GetPos().y);
			break;
		case SCRLTYPE_VIRTICAL:
			m_pBtnScrl->SetPos(m_pBtnScrl->GetPos().x, m_pBtnUp->GetRect().Bottom + m_Scroll);
			break;
		}
	}
}
