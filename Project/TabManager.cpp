#include "TabManager.h"

CTabManager::CTabManager(void) :
	m_Select(0),
	m_PrevSelect(0)
{
}

CTabManager::~CTabManager(void)
{
}

CTabManager & CTabManager::GetManager(void)
{
	static CTabManager manager;
	return manager;
}

void CTabManager::Initialize(void)
{
	char* text[TAB_COUNT] = {
		"ALL",
		"PICTURE",
		"ANIMATION",
		"EDIT",
		"INFO",
	};
	CRectangle rect = theAreaManager.GetRect(CAreaManager::AREA_TAB);
	for (int i = 0; i < TAB_COUNT; i++)
	{
		CControll::CreateInfo info = {
			Vector2(rect.Left + i * 140, rect.Top),
			Vector2(140, rect.GetHeight()),
			text[i],
		};
		m_TabButton[i].FontCreate(24, "");
		m_TabButton[i].SetInfo(info);
		m_TabButton[i].SetLineColor(MOF_COLOR_BLACK);
		if (i == 0)
		{
			continue;
		}
		m_TabButton[i].SetBackColor(MOF_COLOR_HBLACK);
	}
}

void CTabManager::Update(void)
{
	m_PrevSelect = m_Select;
	for (int i = 0; i < TAB_COUNT; i++)
	{
		if (m_TabButton[i].IsPush())
		{
			m_Select = i;
			m_TabButton[m_PrevSelect].SetBackColor(MOF_COLOR_HBLACK);
			m_TabButton[m_Select].SetBackColor(MOF_COLOR_CWHITE);
			break;
		}
	}
}

void CTabManager::Render(void)
{
	for (int i = 0; i < TAB_COUNT; i++)
	{
		m_TabButton[i].Render();
	}
}

void CTabManager::Release(void)
{
	for (int i = 0; i < TAB_COUNT; i++)
	{
		m_TabButton[i].Release();
	}
}

bool CTabManager::IsChanged(void) const
{
	return (m_PrevSelect != m_Select);
}

int CTabManager::GetNowSelect(void) const
{
	return m_Select;
}
