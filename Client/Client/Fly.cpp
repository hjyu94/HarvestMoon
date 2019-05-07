#include "stdafx.h"
#include "Fly.h"


CFly::CFly()
{
}

CFly::~CFly()
{
}

void CFly::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/FLY_IDLE.bmp", L"FLY_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/FLY_IDLE_LEFT.bmp", L"FLY_IDLE_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/FLY_DIE.bmp", L"FLY_DIE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/FLY_DIE_LEFT.bmp", L"FLY_DIE_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/FLY_BOMB.bmp", L"FLY_BOMB");

	m_pFrameKey = L"FLY_IDLE";
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 28.f;
	m_tFrame.dwFrameSpeed = 80;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 6;
	m_tFrame.iFrameStart_Y = 0;	

	m_eCurState = IDLE;
	m_eNextState = IDLE;

	m_fSpeed = 3.f;
	m_fMoveDistance = 100.f;

	m_dwWalking = GetTickCount();
	m_bIsRightDir = true;
	m_bIsStop = false;

	fRandTime = rand() % 1000 + 1000;
}

int CFly::Update()
{
	if (!m_bIsInit)
	{
		m_Center_fx = m_tInfo.fX;
		m_Center_fy = m_tInfo.fY;
		m_bIsInit = true;
	}

	if (m_bIsDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"FLY_BOMB.MP3", CSoundMgr::MONSTER);
		return OBJ_DEAD;
	}
	
	if ((m_eCurState == IDLE || m_eCurState == IDLE_LEFT)
		&& !m_bIsStun)
	{
		if (m_tInfo.fX - m_Center_fx > m_fMoveDistance)
		{
			m_fSpeed *= -1;
			m_pFrameKey = L"FLY_IDLE_LEFT";
			m_eNextState = IDLE_LEFT;
			m_bIsRightDir = false;
		}

		else if (m_tInfo.fX - m_Center_fx < -m_fMoveDistance)
		{
			m_fSpeed *= -1;
			m_pFrameKey = L"FLY_IDLE";
			m_eNextState = IDLE;
			m_bIsRightDir = true;
		}
	
		m_tInfo.fX += m_fSpeed;
	}

	IsJumping();
	IsStunning();
	CObj::IsJumping();
	CObj::UpdateRect();
	FrameMove();
	StateChange();

	return OBJ_NOEVENT;
}

void CFly::LateUpdate()
{
}

void CFly::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (m_eCurState == BOMB)
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
			m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			m_tInfo.fCX * m_tFrame.iFrameStart_X,
			m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
			m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(0, 0, 0)
		);
	
	else
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
			m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			m_tInfo.fCX * m_tFrame.iFrameStart_X,
			m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
			m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Ellipse(hDC, m_tInfo.fX - 5 - iScrollX, m_tInfo.fY - 5 + iScrollY, m_tInfo.fX + 5 - iScrollX, m_tInfo.fY + 5 + iScrollY);
	}
}

void CFly::Release()
{
}

void CFly::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::IDLE:
		case STATE::IDLE_LEFT:
			m_tInfo.fCX = 48.f;
			m_tInfo.fCY = 28.f;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 6;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::DIE:
		case STATE::DIE_LEFT:
			CSoundMgr::Get_Instance()->PlaySound(L"MONSTER_HURT.MP3.MP3", CSoundMgr::MONSTER);
			m_tInfo.fCX = 50.f;
			m_tInfo.fCY = 44.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 5;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::BOMB:
			m_pFrameKey = L"FLY_BOMB";
			m_tInfo.fCX = 70.f;
			m_tInfo.fCY = 70.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 4;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}

		m_eCurState = m_eNextState;
	}
}

void CFly::Bombing()
{
	if (m_bIsRightDir)
	{
		m_pFrameKey = L"FLY_DIE";
		m_eNextState = DIE;
	}
	else
	{
		m_pFrameKey = L"FLY_DIE_LEFT";
		m_eNextState = DIE_LEFT;
	}
}

CFly::STATE CFly::Get_State()
{
	return m_eCurState;
}

void CFly::Collision_Proc(CObj * pCounterObj)
{
}

void CFly::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount()
		&& !m_bIsStun)
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		if (m_eCurState == DIE || m_eCurState == DIE_LEFT)
		{
			m_eNextState = BOMB;
		}
		else if (m_eCurState == BOMB)
		{
			Set_Dead();
		}
		else
			m_tFrame.iFrameStart_X = 0;
	}
}
