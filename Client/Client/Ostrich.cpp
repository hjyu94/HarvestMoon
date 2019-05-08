#include "stdafx.h"
#include "Ostrich.h"
#include "Player.h"
#include "ObjMgr.h"
#include "Line.h"
#include "LineMgr.h"

COstrich::COstrich()
{
}


COstrich::~COstrich()
{
}

void COstrich::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/OSTRICH_STOP.bmp", L"OSTRICH_STOP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/OSTRICH_RUN.bmp", L"OSTRICH_RUN");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/OSTRICH_DOWN.bmp", L"OSTRICH_DOWN");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/OSTRICH_JUMP.bmp", L"OSTRICH_JUMP");

	m_pFrameKey = L"OSTRICH_STOP";
	m_tInfo.fCX = 224.f;
	m_tInfo.fCY = 144.f;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 1;
	m_tFrame.iFrameStart_Y = 0;

	m_eCurState = STOP;
	m_eNextState = STOP;

	m_fSpeed = 3.f;

	m_bIs_With_Player = false;
	m_pPlayer = nullptr;
	m_pLine = nullptr;
}

int COstrich::Update()
{
	if (m_bIs_With_Player)
	{
		m_tInfo.fX += 5.f;

		// 플레이어가 땅에 떨어져야 얘도 Jump 상태 변함
		if (!m_pPlayer->Get_IsJumping())
		{
			m_bIsJump = false;
		}

		if (m_pPlayer->Get_CurState() == CPlayer::DOWN)
		{
			if (!m_bIsJump)
			{
				m_eNextState = DOWN;
				m_pFrameKey = L"OSTRICH_DOWN";
			}
		}
		else if (m_pPlayer->Get_CurState() == CPlayer::STANDING_JUMP)
		{
			if (!m_bIsJump)
			{
				m_eNextState = JUMP;
				m_pFrameKey = L"OSTRICH_JUMP";
				m_bIsJump = true;
				m_fJumpPower = -15.f;
				m_fDeltaTime = 0.f;
			}
		}
		else
		{
			if (!m_bIsJump)
			{
				m_eNextState = RUN;
				m_pFrameKey = L"OSTRICH_RUN";
			}
		}
	}
	
	IsJumping();
	if (m_bIsInit)
	{
		CObj::UpdateRect();
		m_pLine->Set_LineInfo(LINEPOS(m_tInfo.fX - 10 - 30, m_tInfo.fY - 36), LINEPOS(m_tInfo.fX - 10 + 30, m_tInfo.fY - 36));
	}

	if (m_tInfo.fX > 10700)
	{
		if (m_bIs_With_Player)
		{
			m_bIs_With_Player = false;
			m_pPlayer->FinalShooting();
			m_pPlayer = nullptr;
			CSoundMgr::Get_Instance()->PlaySound(L"OSTRICH.MP3", CSoundMgr::MONSTER);
		}
	}
	FrameMove();
	StateChange();

	return 0;
}

void COstrich::LateUpdate()
{
	if (!m_bIsInit)
	{
		m_pLine = new CLine(LINEINFO(LINEPOS(m_tInfo.fX-10-30, m_tInfo.fY-36), LINEPOS(m_tInfo.fX-10+30, m_tInfo.fY - 36)));
		CLineMgr::Get_Instance()->AddLine(m_pLine);
		m_bIsInit = true;
	}
}

void COstrich::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

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

void COstrich::Release()
{
}

void COstrich::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::STOP:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 1;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::RUN:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 6;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::JUMP:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 3;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::DOWN:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 2;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}

		m_eCurState = m_eNextState;
	}
}

void COstrich::Collision_Proc(CObj * pCounterObj)
{
	if (Is_Counter_One_Of(CPlayer))
	{
		// 한번만 수행되도록
		if (!m_bIs_With_Player)
		{
			float fPlayer_X = pCounterObj->Get_Info().fX;
			float fPlayer_Bottom = pCounterObj->Get_Rect().bottom;

			if (fPlayer_X - 10 <= m_tInfo.fX - 10 && m_tInfo.fX - 10 <= fPlayer_X + 10
				&& m_tInfo.fY <= fPlayer_Bottom && fPlayer_Bottom <= m_tRect.bottom)
			{
				m_bIs_With_Player = true;
				m_fSpeed = 5.f;
				m_eNextState = RUN;
				m_pFrameKey = L"OSTRICH_RUN";
				m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
				m_pPlayer->Riding_On_Ostrich();
			}
		}
	}
}

void COstrich::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		if (m_eCurState == DOWN)
			--m_tFrame.iFrameStart_X;
		else
			m_tFrame.iFrameStart_X = 0;
	}
}

void COstrich::IsJumping()
{
	float fy = 300 + 72;
	if (fabs(m_tInfo.fY - fy) > 30.f) m_bIsJump = true;

	if (m_bIsJump)
	{
		m_fVelY = m_fDeltaTime + m_fJumpPower;
		m_tInfo.fY += m_fVelY;
		m_fDeltaTime += 0.5f;

		if (m_tInfo.fY >= fy)
		{
			m_fDeltaTime = 0.f;
			m_fJumpPower = 0.f;
			m_tInfo.fY = fy;
		}
	}
}

