#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_bIsDead(false)
	, m_fAngle(0.f)
	, m_bIsInit(false)
	, m_bMotionEnd(false)
	, m_bIsRightDir(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CObj::~CObj()
{
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (int(m_tInfo.fCY) >> 1));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (int(m_tInfo.fCY) >> 1));
}

void CObj::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{

		m_tFrame.iFrameStart_X = 0;
		m_bMotionEnd = true;
	}
}

void CObj::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}

void CObj::Collision_Proc(CObj * pCounterObj)
{
}

bool CObj::Is_Inside(float left, float top, float right, float bottom)
{
	bool bResult = (left < m_tInfo.fX && m_tInfo.fX < right && top < m_tInfo.fY && m_tInfo.fY < bottom);
	return bResult;
}
