#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
// ********************************************************************************
class CWindowProc :	public CImeProc
{
private:
public:
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	CWindowProc(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	virtual ~CWindowProc(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <param name="hWnd"></param>
	/// <param name="msg"></param>
	/// <param name="wpar"></param>
	/// <param name="lpar"></param>
	/// <returns></returns>
	/// <created>いのうえ,2020/02/29</created>
	/// <changed>いのうえ,2020/02/29</changed>
	// ********************************************************************************
	virtual MofProcResult WindowProc(MofWindowHandle hWnd, MofUInt msg,
		MofProcParamW wpar, MofProcParamL lpar);

	MofS32 GetInsertPoint(void);
};

