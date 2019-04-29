#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
	: m_Center_fx(0.f)
	, m_Center_fy(0.f)
	, m_fMoveDistance(0.f)
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
}

int CMonster::Update()
{
	return 0;
}

void CMonster::LateUpdate()
{
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release()
{
}

void CMonster::Set_Distance(float _distance)
{
	m_fMoveDistance = _distance;
}
