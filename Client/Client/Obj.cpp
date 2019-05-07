#include "stdafx.h"
#include "Obj.h"
#include "LineMgr.h"

CObj::CObj()
	:m_bIsDead(false)
	, m_fAngle(0.f)
	, m_bIsInit(false)
	, m_bMotionEnd(false)
	, m_bIsRightDir(false)
	, m_bIsJump(false)
	, m_fVelY(0.f)
	, m_fJumpPower(0.f)
	, m_fDeltaTime(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	m_dwStun = GetTickCount();
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
	}
}

void CObj::IsJumping()
{
	float fy = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fy);

	// 사이가 너무 멀면 다른 땅인 거고
	// 사이가 조금만 멀면 같은따잉니 점프
	float fDist = fabs(fy - m_tInfo.fY);
	if (fDist > 40.f) m_bIsJump = false;
	else m_bIsJump = true;

	if (m_bIsJump)
	{
		m_fVelY = m_fDeltaTime + m_fJumpPower;
		m_tInfo.fY += m_fVelY;
		m_fDeltaTime += 0.5f;

		if (m_tInfo.fY > fy)
		{
			m_tInfo.fY = fy;
			m_bIsJump = false;
			m_fJumpPower = 0.f;
			m_fDeltaTime = 0.f;
		}
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

void CObj::Set_Stun()
{
	m_bIsStun = true;
	m_dwStun = GetTickCount();
}

void CObj::IsStunning()
{
	if (m_bIsStun)
	{
		if (m_dwStun + 500 < GetTickCount())
		{
			m_bIsStun = false;
		}
	}
}
