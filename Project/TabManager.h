#pragma once
#include	"Mof.h"
#include	"AreaManager.h"
#include	"ToolControll.h"

class CTabManager
{
public:
	enum TabCategory {
		TAB_ALL,
		TAB_PIXTURE,
		TAB_ANIMATION,
		TAB_EDIT,
		TAB_INFO,

		TAB_COUNT,
	};
private:
	CButton	m_TabButton[TAB_COUNT];
	int m_Select;
	int m_PrevSelect;

	CTabManager(void);
	~CTabManager(void);
public:
	static CTabManager& GetManager(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);
	bool IsChanged(void) const;
	int GetNowSelect(void) const;
};

#define theTabManager CTabManager::GetManager()

