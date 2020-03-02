#pragma once
#include	"Mof.h"


// ********************************************************************************
/// <summary>
/// 
/// </summary>
// ********************************************************************************
class CAreaManager
{
public:
	/// <summary></summary>
	enum ToolArea {
		AREA_BUTTON,
		AREA_TAB,
		AREA_VIEW,
		AREA_EDIT,

		AREA_COUNT,
	};
private:
	CRectangle  m_Rect[AREA_COUNT];
	MofU32		m_BackColor[AREA_COUNT];
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// <created>‚¢‚Ì‚¤‚¦,2020/03/02</created>
	/// <changed>‚¢‚Ì‚¤‚¦,2020/03/02</changed>
	// ********************************************************************************
	CAreaManager(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// <created>‚¢‚Ì‚¤‚¦,2020/03/02</created>
	/// <changed>‚¢‚Ì‚¤‚¦,2020/03/02</changed>
	// ********************************************************************************
	~CAreaManager(void);
public:
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	/// <created>‚¢‚Ì‚¤‚¦,2020/03/02</created>
	/// <changed>‚¢‚Ì‚¤‚¦,2020/03/02</changed>
	// ********************************************************************************
	static CAreaManager& GetManager(void);
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <param name="area"></param>
	/// <returns></returns>
	/// <created>‚¢‚Ì‚¤‚¦,2020/03/02</created>
	/// <changed>‚¢‚Ì‚¤‚¦,2020/03/02</changed>
	// ********************************************************************************
	CRectangle GetRect(const ToolArea& area) const;
	// ********************************************************************************
	/// <summary>
	/// 
	/// </summary>
	/// <created>‚¢‚Ì‚¤‚¦,2020/03/02</created>
	/// <changed>‚¢‚Ì‚¤‚¦,2020/03/02</changed>
	// ********************************************************************************
	void Render(void);
};

#define theAreaManager CAreaManager::GetManager()

