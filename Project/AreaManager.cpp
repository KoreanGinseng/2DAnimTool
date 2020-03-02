#include "AreaManager.h"

CAreaManager::CAreaManager(void)
{
	m_Rect[AREA_BUTTON] = CRectangle(0, 0, 1280, 32);
	m_Rect[AREA_TAB] = CRectangle(0, 32, 1280 - 500, 64);
	m_Rect[AREA_VIEW] = CRectangle(0, 64, 1280, 720);
	m_Rect[AREA_EDIT] = CRectangle(1280 - 500, 32, 1280, 720);
	m_BackColor[AREA_BUTTON] = MOF_COLOR_CBLACK;
	m_BackColor[AREA_TAB]    = MOF_COLOR_CBLACK;
	m_BackColor[AREA_VIEW]   = MOF_COLOR_BLUE;
	m_BackColor[AREA_EDIT]   = MOF_COLOR_CBLACK;
}

CAreaManager::~CAreaManager(void)
{
}

CAreaManager & CAreaManager::GetManager(void)
{
	static CAreaManager manager;
	return manager;
}

CRectangle CAreaManager::GetRect(const ToolArea & area) const
{
	return m_Rect[area];
}

void CAreaManager::Render(void)
{
	for (int i = 0; i < AREA_COUNT; i++)
	{
		CGraphicsUtilities::RenderFillRect(m_Rect[i], m_BackColor[i]);
		CGraphicsUtilities::RenderRect(m_Rect[i], MOF_COLOR_HBLACK);
	}
}
