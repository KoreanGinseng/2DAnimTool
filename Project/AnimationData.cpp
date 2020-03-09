#include "AnimationData.h"

CAnimationData::CAnimationData(void)
{
}

CAnimationData::~CAnimationData(void)
{
}

CAnimationData & CAnimationData::GetAnimationData(void)
{
	static CAnimationData animData;
	return animData;
}

void CAnimationData::LoadTexture(LPCMofChar name)
{
}

void CAnimationData::LoadAnim(SpriteAnimationCreate * pAnim)
{
}

void CAnimationData::Load(LPCMofChar pName)
{
}
