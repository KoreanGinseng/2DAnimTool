#pragma once
#include	"Mof.h"

enum ToolArea {
	AREA_BUTTON,
	AREA_TAB,
	AREA_VIEW,
	AREA_EDIT,

	AREA_COUNT,
};

class CAreaManager
{
private:
	CRectangle  m_Rect[AREA_COUNT];
	MofU32		m_BackColor[AREA_COUNT];
	CAreaManager(void);
	~CAreaManager(void);
public:
	static CAreaManager& GetManager(void);
	CRectangle GetRect(const ToolArea& area) const;
	void Render(void);
};

#define theAreaManager CAreaManager::GetManager()

