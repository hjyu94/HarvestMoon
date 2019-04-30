#include "stdafx.h"
#include "HedgeHog.h"
#include "Player.h"
#include "LineMgr.h"

CHedgeHog::CHedgeHog()
{
}


CHedgeHog::~CHedgeHog()
{
}

void CHedgeHog::Initialize()
{
	m_fSpeed = 0.5f;
	m_bIsRightDir = true;
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HedgeHog_IDLE.bmp", L"HedgeHog_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HedgeHog_IDLE_LEFT.bmp", L"HedgeHog_IDLE_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HedgeHog_UPSIDE_DOWN.bmp", L"HedgeHog_UPSIDE_DOWN");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HedgeHog_UPSIDE_DOWN_LEFT.bmp", L"HedgeHog_UPSIDE_DOWN_LEFT");

	m_pFrameKey = L"HedgeHog_IDLE";

	m_fMoveDistance = 100.f;

	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 50.f;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 6;
	m_tFrame.iFrameStart_Y = 0;

	m_bIsUpsidedown = false;
	m_dwWalking = GetTickCount();
	m_bIsStop = false;

	m_bIsJump = false;
	m_fSpeed = 1.f;
	m_fDeltaTime = 0.f;
	m_fVelY = 0.f;
	m_fJumpPower = -10.f;

	m_dwUpsidedown = GetTickCount();
}

int CHedgeHog::Update()
{
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

	// 죽기 전이면
	if (m_eCurState != DIE)
	{
		if (m_tInfo.fX - m_Center_fx > m_fMoveDistance)
		{
			m_fSpeed *= -1;
			m_pFrameKey = L"HedgeHog_IDLE_LEFT";
			m_eNextState = IDLE_LEFT;
			m_bIsRightDir = false;
		}
		else if (m_tInfo.fX - m_Center_fx < -m_fMoveDistance)
		{
			m_fSpeed *= -1;
			m_pFrameKey = L"HedgeHog_IDLE";
			m_eNextState = IDLE;
			m_bIsRightDir = true;
		}

		// 뒤집어지기 전이면
		if (!m_bIsUpsidedown)
		{
			if (m_dwWalking + 1500 > GetTickCount())
			{
				//if (m_eCurState == STATE::IDLE || m_eCurState == STATE::IDLE_LEFT)
				m_tInfo.fX += m_fSpeed;
			}
			else if (m_dwWalking + 1500 < GetTickCount())
			{
				m_bIsStop = true;
				if (m_dwWalking + 2500 < GetTickCount())
				{
					m_dwWalking = GetTickCount();
					m_bIsStop = false;
				}
			}
		}
	}
	// 죽고 났는데 뒤집어진 후면
	else if(m_bIsUpsidedown)
	{
		if (m_dwUpsidedown + 10000 < GetTickCount())
		{
			m_bIsUpsidedown = false;

			if (m_bIsRightDir)
			{
				m_pFrameKey = L"HedgeHog_IDLE";
				m_eNextState = IDLE;
			}
			else
			{
				m_pFrameKey = L"HedgeHog_IDLE_LEFT";
				m_eNextState = IDLE_LEFT;
			}
			m_dwUpsidedown = GetTickCount();
		}
	}
/*
	if (m_eCurState == UPSIDE_DOWN
		|| m_eCurState == UPSIDE_DOWN_LEFT)
	{

	}
	else
		m_tInfo.fX += m_fSpeed;
*/
	IsJumping();
	CObj::UpdateRect();
	StateChange();
	CObj::FrameMove();
	return OBJ_NOEVENT;
}

void CHedgeHog::LateUpdate()
{
}

void CHedgeHog::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (!m_bIsUpsidedown)
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
	else
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
			m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0,0,// 시작 위치 
			m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}
}

void CHedgeHog::Release()
{
}

void CHedgeHog::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::IDLE:
		case STATE::IDLE_LEFT:
			m_tInfo.fCX = 70.f;
			m_tInfo.fCY = 50.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 6;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::UPSIDE_DOWN:
		case STATE::UPSIDE_DOWN_LEFT:
			/*m_tInfo.fCX = 80.f;
			m_tInfo.fCY = 75.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 10;
			m_tFrame.iFrameStart_Y = 0;*/
			break;
		}

		m_eCurState = m_eNextState;
	}
}

void CHedgeHog::Collision_Proc(CObj * pCounterObj)
{
	if (Is_Counter_One_Of(CPlayer))
	{
		if (m_bIsUpsidedown)
		{
			if (static_cast<CPlayer*>(pCounterObj)->Get_CurState() == CPlayer::STANDING_JUMP
				|| static_cast<CPlayer*>(pCounterObj)->Get_CurState() == CPlayer::STANDING_JUMP_LEFT)
			{
				m_eCurState = DIE;

				m_bIsJump = true;
				m_fJumpPower = -10.f;
			}
		}
	}
}

void CHedgeHog::Upside_Down()
{
	if (!m_bIsUpsidedown)
	{
		if (m_bIsRightDir)
		{
			m_pFrameKey = L"HedgeHog_UPSIDE_DOWN";
			m_eNextState = UPSIDE_DOWN;
		}
		else
		{
			m_pFrameKey = L"HedgeHog_UPSIDE_DOWN_LEFT";
			m_eNextState = UPSIDE_DOWN_LEFT;
		}

		m_bIsUpsidedown = true;

		m_bIsJump = true;
		m_fJumpPower = -10.f;
		m_dwUpsidedown = GetTickCount();
	}
}

void CHedgeHog::IsJumping()
{
	float fy = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fy);

	// 죽은 상황이 아니면
	if (m_eCurState != DIE)
	{
		if (m_bIsJump)
		{
			m_fVelY = m_fDeltaTime + m_fJumpPower;
			m_tInfo.fY += m_fVelY;
			m_fDeltaTime += 0.5f;

			if (bIsColl && m_tInfo.fY > fy)
			{
				m_bIsJump = false;
				m_fDeltaTime = 0.f;
				m_fJumpPower = -10.f;
				m_tInfo.fY = fy;
			}
		}
		else if (bIsColl)
		{
			m_tInfo.fY = fy;
		}
	}
	// 죽은 상황이면
	else if(m_eCurState == DIE)
	{
		if (m_bIsJump)
		{
			m_fVelY = m_fDeltaTime + m_fJumpPower;
			m_tInfo.fY += m_fVelY;
			m_fDeltaTime += 0.5f;

			if (bIsColl && m_fVelY > 0)
			{
				m_bIsJump = false;
				m_fDeltaTime = 0.f;
				m_fJumpPower = -10.f;
				m_tInfo.fY = fy;
				m_bIsDead = true;
			}
		}
	}
}
