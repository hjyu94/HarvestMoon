#include "stdafx.h"
#include "TestPlayer.h"
#include "LineMgr.h"

CTestPlayer::CTestPlayer()
{
}


CTestPlayer::~CTestPlayer()
{
}

void CTestPlayer::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_bIsJump = false;
	m_fJumpAccel = 0.f;
	m_fJumpPower = 15.f;

}

int CTestPlayer::Update()
{
	float fy = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fy);

	// 사용자가 점프를 눌렀을때!
	if (m_bIsJump)
	{
		// 자유낙하 공식 사용 
		// y= 힘 * sin@(1이라 생략) * 시간 - 1/2 * 중력 * 시간 * 시간;
		m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - 9.8 * m_fJumpAccel * m_fJumpAccel * 0.5f;

		m_fJumpAccel += 0.21f;

		if (bIsColl && m_tInfo.fY > fy)
		{
			m_bIsJump = false;
			m_fJumpAccel = 0.f;
			m_tInfo.fY = fy;
		}
		// 		system("cls");
		// 		cout << m_tInfo.fY << endl; 
		// 		int i = 0; 
	}
	else if (bIsColl)
		m_tInfo.fY = fy;


	return 0;
}

void CTestPlayer::LateUpdate()
{
}

void CTestPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CTestPlayer::Release()
{
}
