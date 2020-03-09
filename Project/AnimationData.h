#pragma once
#include	"Mof.h"

class CAnimationData
{
private:
	CTexture m_Texture;
	CDynamicArray< SpriteAnimationCreate > m_AnimArray;
	CAnimationData(void);
	~CAnimationData(void);
public:
	static CAnimationData& GetAnimationData(void);
	void LoadTexture(LPCMofChar name);
	void LoadAnim(SpriteAnimationCreate* pAnim);
	void Load(LPCMofChar pName);
};

