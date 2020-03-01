#pragma once
#include "Mof.h"
#include "Controll.h"
#include "Button.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// �X�N���[���o�[�N���X
	/// </summary>
	// ********************************************************************************
	class CScrollBar : public CControll
	{
	public:
		enum ScrlType {
			SCRLTYPE_VIRTICAL,				//!<�c����
			SCRLTYPE_HORIZONTAL,			//!<������
		};
	private:
		LPButton		m_pBtnUp;			//!<��{�^��
		LPButton		m_pBtnScrl;			//!<�X���C�h�{�^��
		LPButton		m_pBtnDown;			//!<���{�^��
		CRectangle		m_ScrlArea;			//!<�X�N���[������G���A
		CRectangle		m_ScrlBar;			//!<�X�N���[���o�[�̋�`
		ScrlType		m_Type;				//!<�X�N���[���^�C�v
		MofInt			m_MaxSize;			//!<�X�N���[���̍ő�l
		MofInt			m_ScrlWidth;		//!<�X�N���[���o�[�̕�
		MofFloat		m_ScrlParPix;		//!<�P�s�N�Z���ɓ�����
		MofInt			m_Scroll;			//!<���݂̃X�N���[���l
		MofBool			m_bBarHold;			//!<�X���C�h�̃z�[���h�t���O
	public:
		// ********************************************************************************
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/02/24</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		CScrollBar(void);
		// ********************************************************************************
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <created>���̂���,2020/02/24</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		virtual ~CScrollBar(void);
		// ********************************************************************************
		/// <summary>
		/// �X�N���[���o�[�̐���
		/// </summary>
		/// <param name="info">�������</param>
		/// <returns>�X�N���[���o�[�|�C���^</returns>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		static std::shared_ptr<CScrollBar> CreateScrollBar(void);
		// ********************************************************************************
		/// <summary>
		/// ������
		/// </summary>
		/// <created>���̂���,2020/02/24</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		void Initialize(void);
		// ********************************************************************************
		/// <summary>
		/// �X�V
		/// </summary>
		/// <created>���̂���,2020/02/24</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		void Update(void);
		// ********************************************************************************
		/// <summary>
		/// �`��
		/// </summary>
		/// <created>���̂���,2020/02/24</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		void Render(void);
		// ********************************************************************************
		/// <summary>
		/// ���
		/// </summary>
		/// <created>���̂���,2020/02/24</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		void Release(void);
		// ********************************************************************************
		/// <summary>
		/// �X�N���[�������̐ݒ�
		/// </summary>
		/// <param name="t">�X�N���[������</param>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		void SetType(ScrlType t);
		// ********************************************************************************
		/// <summary>
		/// �X�N���[���o�[�̕��̐ݒ�
		/// </summary>
		/// <param name="w">��</param>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		void SetWidth(const int& w);
		// ********************************************************************************
		/// <summary>
		/// �X�N���[������G���A�̐ݒ�
		/// </summary>
		/// <param name="area">�G���A��`</param>
		/// <param name="maxSize">�X�N���[���ő�l</param>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		void SetScrlArea(const CRectangle& area, const int& maxSize);
		// ********************************************************************************
		/// <summary>
		/// �X�N���[���ő�l�̕ύX
		/// </summary>
		/// <param name="maxSize">�ő�l</param>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void ChangeMaxSize(const int& maxSize);
		// ********************************************************************************
		/// <summary>
		/// �X�N���[���G���A�̎擾
		/// </summary>
		/// <returns>�X�N���[���G���A</returns>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		CRectangle GetScrlAreaRect(void) const;
		// ********************************************************************************
		/// <summary>
		/// �X�N���[���l�̎擾
		/// </summary>
		/// <returns></returns>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		float GetScroll(void) const;
		// ********************************************************************************
		/// <summary>
		/// ��{�^���̎擾
		/// </summary>
		/// <returns>��{�^��</returns>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		LPButton GetBtnUp(void);
		// ********************************************************************************
		/// <summary>
		/// �X���C�h�{�^���̎擾
		/// </summary>
		/// <returns>�X���C�h�{�^��</returns>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		LPButton GetBtnScrl(void);
		// ********************************************************************************
		/// <summary>
		/// ���{�^���̎擾
		/// </summary>
		/// <returns>���{�^��</returns>
		/// <created>���̂���,2020/02/28</created>
		/// <changed>���̂���,2020/02/28</changed>
		// ********************************************************************************
		LPButton GetBtnDown(void);
	private:
		// ********************************************************************************
		/// <summary>
		/// �e�{�^���̐���
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void CreateButton(void);
		// ********************************************************************************
		/// <summary>
		/// �o�[�̃T�C�Y�̏�����
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void InitBarSize(void);
		// ********************************************************************************
		/// <summary>
		/// �X���C�h�{�^���̈ʒu�̏�����
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void InitBarPos(void);
		// ********************************************************************************
		/// <summary>
		/// �X���C�h�{�^���̒���������
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void InitBarLength(void);
		// ********************************************************************************
		/// <summary>
		/// �}�E�X�ł̃X�N���[������
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void MoveMouse(void);
		// ********************************************************************************
		/// <summary>
		/// �}�E�X�z�C�[���ł̃X�N���[������
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void MoveWheel(void);
		// ********************************************************************************
		/// <summary>
		/// �㉺�{�^���ł̃X�N���[������
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void MoveButton(void);
		// ********************************************************************************
		/// <summary>
		/// �X�N���[���l�̐���
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void CheckOverScroll(void);
		// ********************************************************************************
		/// <summary>
		/// �ʒu�̍Čv�Z
		/// </summary>
		/// <created>���̂���,2020/02/29</created>
		/// <changed>���̂���,2020/02/29</changed>
		// ********************************************************************************
		void UpdateBarPos(void);
	};

	//�u������
	typedef std::shared_ptr<CScrollBar> LPScrollBar;
}
