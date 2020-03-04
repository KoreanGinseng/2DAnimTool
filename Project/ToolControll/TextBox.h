#pragma once
#include "Controll.h"

namespace ToolControll
{
	// ********************************************************************************
	/// <summary>
	/// テキストボックスクラス
	/// </summary>
	// ********************************************************************************
	class CTextBox : public CControll
	{
	public:
		/// <summary>数字変換のerror列挙</summary>
		enum NumError {
			NE_NOCONVERSION = 0b00000001,	//!<エラー番号１：変換失敗
			NE_OUTOFRANGE   = 0b00000010,	//!<エラー番号２：オーバーフロー
		};
		/// <summary>文字描画位置</summary>
		enum TxtAlign {
			TXTALI_LEFT,					//!<左寄せ
			TXTALI_CENTER,					//!<中央寄せ
			TXTALI_RIGHT,					//!<右寄せ
		};
	private:
		MofBool  m_bInput;					//!<入力中フラグ
		MofFloat m_CursorPos;				//!<カーソルの座標
		MofInt   m_CursorPoint;				//!<入力文字の何文字目
		MofInt   m_CursorTime;				//!<点滅用カウンタ
		MofBool  m_bNumOnly;				//!<数字のみの入力を受け付けるフラグ
		UCHAR    m_Error;					//!<エラー
		MofInt   m_TxtAlign;				//!<文字描画位置
		MofInt	 m_NumMax;					//!<最大値
		MofInt	 m_NumMin;					//!<最小値
	public:
		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		CTextBox(void);
		// ********************************************************************************
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		virtual ~CTextBox(void);
		// ********************************************************************************
		/// <summary>
		/// テキストボックス生成クラス
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		static std::shared_ptr<CTextBox> CreateTextBox(void);
		// ********************************************************************************
		/// <summary>
		/// テキストボックスの制御リスト取得
		/// </summary>
		/// <returns>制御リスト</returns>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		static CDynamicArray<CTextBox*>& GetList(void);
		// ********************************************************************************
		/// <summary>
		/// リストの解放
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		static void ReleaseList(void);
		// ********************************************************************************
		/// <summary>
		/// ImeInputの更新
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		static void RefreshImeInput(void);
		// ********************************************************************************
		/// <summary>
		/// 初期化
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void Initialize(void);
		// ********************************************************************************
		/// <summary>
		/// 更新
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void Update(void);
		// ********************************************************************************
		/// <summary>
		/// カーソルの更新
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void CursorUpdate(void);
		// ********************************************************************************
		/// <summary>
		/// 描画
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		virtual void Render(void) override;
		// ********************************************************************************
		/// <summary>
		/// 入力フラグの設定
		/// </summary>
		/// <param name="b">フラグ</param>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void SetInput(const MofBool& b);
		// ********************************************************************************
		/// <summary>
		/// 入力フラグの取得
		/// </summary>
		/// <returns>入力フラグ</returns>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		MofBool IsInput(void) const;
		// ********************************************************************************
		/// <summary>
		/// 数字のみフラグの設定
		/// </summary>
		/// <param name="b">フラグ</param>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void SetNumOnly(const MofBool& b);
		// ********************************************************************************
		/// <summary>
		/// 数字のみフラグの取得
		/// </summary>
		/// <returns>フラグ</returns>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		MofBool IsNumOnly(void) const;
		// ********************************************************************************
		/// <summary>
		/// 数字のみの場合の制御
		/// </summary>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void NumUpdate(void);
		// ********************************************************************************
		/// <summary>
		/// 数字の取得
		/// </summary>
		/// <returns></returns>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		MofFloat GetNum(void) const;
		// ********************************************************************************
		/// <summary>
		/// 数字の設定
		/// </summary>
		/// <param name="num">数字</param>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void SetNum(const MofFloat& num);
		// ********************************************************************************
		/// <summary>
		/// 数字の加算処理
		/// </summary>
		/// <param name="num">数字</param>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void AddNum(const MofFloat& num);
		// ********************************************************************************
		/// <summary>
		/// 数字の減算処理
		/// </summary>
		/// <param name="num">数字</param>
		/// <created>いのうえ,2020/03/01</created>
		/// <changed>いのうえ,2020/03/01</changed>
		// ********************************************************************************
		void SubNum(const MofFloat& num);
		// ********************************************************************************
		/// <summary>
		/// 描画位置の設定
		/// </summary>
		/// <param name="align">描画位置</param>
		/// <created>いのうえ,2020/03/03</created>
		/// <changed>いのうえ,2020/03/03</changed>
		// ********************************************************************************
		void SetTxtAlign(const TxtAlign& align);
		// ********************************************************************************
		/// <summary>
		/// 最小値と最大値の設定
		/// </summary>
		/// <param name="min">最小値</param>
		/// <param name="max">最大値</param>
		/// <created>いのうえ,2020/03/03</created>
		/// <changed>いのうえ,2020/03/03</changed>
		// ********************************************************************************
		void SetNumMinMax(const MofInt& min, const MofInt& max);
	};

	//置き換え
	typedef std::shared_ptr<CTextBox> LPTextBox;
#define g_pImeInput CImeProc::GetImeInput()
}

