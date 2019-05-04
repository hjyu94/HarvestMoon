#include "stdafx.h"
#include "Lizard.h"
#include "Player.h"

CLizard::CLizard()
	: m_eNextState(IDLE)
	, m_eCurState(IDLE)
{
}


CLizard::~CLizard()
{
}

void CLizard::Initialize()
{

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/LIZARD_IDLE.bmp", L"LIZARD_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/LIZARD_IDLE_LEFT.bmp", L"LIZARD_IDLE_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/LIZARD_ATTACK.bmp", L"LIZARD_ATTACK");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/LIZARD_ATTACK_LEFT.bmp", L"LIZARD_ATTACK_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/BombEffect.bmp", L"BombEffect");
	
	m_pFrameKey = L"LIZARD_IDLE";
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 40.f;
	m_eCurState = STATE::IDLE;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 7;
	m_tFrame.iFrameStart_Y = 0;

	m_fSpeed = 0.5f;
	m_fMoveDistance = 100.f;

	m_dwAttack = GetTickCount();
	m_dwWalking = GetTickCount();
	m_bIsRightDir = true;
	m_bIsAttacking = false;
	m_bIsStop = false;

	fRandTime = rand() % 1000 + 1000;
	cout << fRandTime << endl;
}

int CLizard::Update()
{
	int i = 0;
	if (!m_bIsInit)
	{
		m_Center_fx = m_tInfo.fX;
		m_Center_fy = m_tInfo.fY;
		m_bIsInit = true;
	}

	if (m_bIsDead)
	{
		return OBJ_DEAD;
	}

	if (m_tInfo.fX - m_Center_fx > m_fMoveDistance)
	{
		m_fSpeed *= -1;
		m_pFrameKey = L"LIZARD_IDLE_LEFT";
		m_eNextState = IDLE_LEFT;
		m_bIsRightDir = false;
	}
	else if (m_tInfo.fX - m_Center_fx < -m_fMoveDistance)
	{
		m_fSpeed *= -1;
		m_pFrameKey = L"LIZARD_IDLE";
		m_eNextState = IDLE;
		m_bIsRightDir = true;
	}

	if (!m_bIsAttacking)
	{
		if (m_dwWalking + fRandTime > GetTickCount())
		{
			if (m_eCurState == STATE::IDLE || m_eCurState == STATE::IDLE_LEFT)
				if(!m_bIsStun)
					m_tInfo.fX += m_fSpeed;
		}
		else if (m_dwWalking + fRandTime < GetTickCount())
		{
			m_bIsStop = true;
			if (m_dwWalking + fRandTime + 1000 < GetTickCount())
			{
				m_dwWalking = GetTickCount();
				m_bIsStop = false;
			}
		}
	}

	if (m_dwAttack + 8000 < GetTickCount() && m_bIsStop)
	{
		if (m_bIsRightDir)
		{
			m_pFrameKey = L"LIZARD_ATTACK";
			m_eNextState = ATTACK;
		}
		else
		{
			m_pFrameKey = L"LIZARD_ATTACK_LEFT";
			m_eNextState = ATTACK_LEFT;
		}

		m_bIsAttacking = true;
		m_dwAttack = GetTickCount();
	}
	
	
	IsJumping();
	CObj::IsStunning();
	CObj::UpdateRect();
	CLizard::FrameMove();
	CLizard::SceneChange();

	return OBJ_NOEVENT;
}

void CLizard::LateUpdate()
{
}

void CLizard::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	
	// 치트키
	if (CKeyMgr::Get_Instance()->KeyPressing('M'))
	{
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}
	
	
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (m_eCurState == IDLE || m_eCurState == IDLE_LEFT)
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
			m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			m_tInfo.fCX * m_tFrame.iFrameStart_X,
			m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
			m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}
	else if (m_eCurState == ATTACK || m_eCurState == ATTACK_LEFT)
	{
		if (m_tFrame.iFrameStart_X == 5)
		{
			GdiTransparentBlt(hDC, // 실제 복사받을 DC
				m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
				m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
				hMemDC,
				470.f,
				m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
				m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
				RGB(255, 255, 255)
			);
		}
		else if (m_tFrame.iFrameStart_X > 5)
		{
			GdiTransparentBlt(hDC, // 실제 복사받을 DC
				m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
				m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
				hMemDC,
				m_tInfo.fCX * m_tFrame.iFrameStart_X + 84.f,
				m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
				m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
				RGB(255, 255, 255)
			);
		}
		else
		{
			GdiTransparentBlt(hDC, // 실제 복사받을 DC
				m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
				m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
				hMemDC,
				m_tInfo.fCX * m_tFrame.iFrameStart_X,
				m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
				m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
				RGB(255, 255, 255)
			);
		}
	}

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Ellipse(hDC, m_tInfo.fX - 5 - iScrollX, m_tInfo.fY - 5 + iScrollY, m_tInfo.fX + 5 - iScrollX, m_tInfo.fY + 5 + iScrollY);
	}
}

void CLizard::Release()
{
}

void CLizard::KeyCheck()
{
}

void CLizard::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CLizard::IDLE:
		case CLizard::IDLE_LEFT:
			m_tInfo.fCX = 70.f;
			m_tInfo.fCY = 40.f;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 7;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CLizard::ATTACK:
		case CLizard::ATTACK_LEFT:
			m_tInfo.fCX = 94.f;
			m_tInfo.fCY = 54.f;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 7;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}
		m_eCurState = m_eNextState;
	}
}

void CLizard::FrameMove()
{
	int i = 0;
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount()
		&& !m_bIsStun)
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_eCurState ==	ATTACK || m_eCurState == ATTACK_LEFT)
	{
		if (m_tFrame.iFrameStart_X == 5)
		{
			m_tInfo.fCX = 176.f;
			/*if (m_bIsRightDir)
			{
				m_tInfo.fX += 70.f;
			}
			else
			{
				m_tInfo.fX -= 70.f;
			}*/
		}
		else if (m_tFrame.iFrameStart_X == 6)
		{
			m_tInfo.fCX = 94.f;
			/*if (m_bIsRightDir)
			{
				m_tInfo.fX -= 70.f;
			}
			else
			{
				m_tInfo.fX += 70.f;
			}*/
		}
		//else
		//{
		//	m_tInfo.fCX = 94.f;
		//}

		if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
		{
			m_bIsAttacking = false;
			m_bIsStop = false;
			if (m_bIsRightDir)
			{
				m_pFrameKey = L"LIZARD_IDLE";
				m_eNextState = IDLE;
			}
			else
			{
				m_pFrameKey = L"LIZARD_IDLE_LEFT";
				m_eNextState = IDLE_LEFT;
			}
		}
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		m_tFrame.iFrameStart_X = 0;
	}
}

