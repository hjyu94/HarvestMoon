#include "stdafx.h"
#include "Monkey.h"
#include "Player.h"
#include "ObjMgr.h"

CMonkey::CMonkey()
{
}

CMonkey::~CMonkey()
{
	Release();
}

void CMonkey::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/BLUE_MONKEY.bmp", L"BLUE_MONKEY");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/BLUE_MONKEY_LEFT.bmp", L"BLUE_MONKEY_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/BLUE_MONKEY_THROW.bmp", L"BLUE_MONKEY_THROW");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/BLUE_MONKEY_THROW_LEFT.bmp", L"BLUE_MONKEY_THROW_LEFT");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/PINK_MONKEY.bmp", L"PINK_MONKEY");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/PINK_MONKEY_LEFT.bmp", L"PINK_MONKEY_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/PINK_MONKEY_THROW.bmp", L"PINK_MONKEY_THROW");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/PINK_MONKEY_THROW_LEFT.bmp", L"PINK_MONKEY_THROW_LEFT");

	
	m_eColor = C_BLUE;
	m_eDir = LEFT;

	m_bIsRightDir = true;
	m_eCurState = IDLE;
	m_eNextState = IDLE;

	m_pFrameKey = L"BLUE_MONKEY";

	m_tInfo.fCX = 167.f;
	m_tInfo.fCY = 233.f;
	m_tFrame.dwFrameSpeed = 80;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 1;
	m_tFrame.iFrameStart_Y = 0;

	m_dwTurnCoolTime = GetTickCount();
}

int CMonkey::Update()
{
	CObj::UpdateRect();
	FrameMove();
	StateChange();

	switch (m_eColor)
	{
	case CMonkey::C_PINK:
		switch (m_eCurState)
		{
		case IDLE:
		case IDLE_LEFT:
			if (m_bIsRightDir)
				m_pFrameKey = L"PINK_MONKEY";
			else
				m_pFrameKey = L"PINK_MONKEY_LEFT";

			break;

		case THROW:
		case THROW_LEFT:
			if (m_bIsRightDir)
				m_pFrameKey = L"PINK_MONKEY_THROW";
			else
				m_pFrameKey = L"PINK_MONKEY_THROW_LEFT";
			break;
		}
		break;

	case CMonkey::C_BLUE:
		switch (m_eCurState)
		{
		case IDLE:
		case IDLE_LEFT:
			if (m_bIsRightDir)
				m_pFrameKey = L"BLUE_MONKEY";
			else
				m_pFrameKey = L"BLUE_MONKEY_LEFT";

			break;

		case THROW:
		case THROW_LEFT:
			if (m_bIsRightDir)
				m_pFrameKey = L"BLUE_MONKEY_THROW";
			else
				m_pFrameKey = L"BLUE_MONKEY_THROW_LEFT";
			break;
		}
		break;

	}
	return 0;
}

void CMonkey::LateUpdate()
{
}

void CMonkey::Render(HDC hDC)
{
	CObj::UpdateRect();
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
		RGB(255,255,255)
	);

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Ellipse(hDC, m_tInfo.fX - 5 - iScrollX, m_tInfo.fY - 5 + iScrollY, m_tInfo.fX + 5 - iScrollX, m_tInfo.fY + 5 + iScrollY);
	}
}

void CMonkey::Release()
{
}

void CMonkey::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::IDLE:
		case STATE::IDLE_LEFT:
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 1;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::THROW:
		case STATE::THROW_LEFT:
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 3;
			m_tFrame.iFrameStart_Y = 0;

			break;
		}
		m_eCurState = m_eNextState;
	}
}

void CMonkey::Collision_Proc(CObj * pCounterObj)
{
	if (Is_Counter_One_Of(CPlayer))
	{
		float fPlayerX = pCounterObj->Get_Info().fX;
		float fPlayerY = pCounterObj->Get_Info().fY;

		if (fPlayerX - 20 <= m_tInfo.fX && m_tInfo.fX <= fPlayerX + 20
			&& fPlayerY - 20 <= m_tInfo.fY && m_tInfo.fY <= fPlayerY + 20)
		{
			m_eNextState = THROW;
			Thorw_Player(m_eDir);
		}

	}
}

void CMonkey::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		if (m_eCurState == THROW || m_eCurState == THROW_LEFT)
		{
			if(m_bIsRightDir) m_eNextState = IDLE;
			else m_eNextState = IDLE_LEFT;
		}
		else if (m_eCurState == IDLE || m_eCurState == IDLE_LEFT)
			m_tFrame.iFrameStart_X = 0;


	}
}

void CMonkey::Thorw_Player(DIR eDIR)
{
	CSoundMgr::Get_Instance()->PlaySound(L"MONKEY.MP3", CSoundMgr::CHANNELID::MONSTER);

	CPlayer* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	switch (eDIR)
	{
	case CMonkey::LEFT:
		pPlayer->Rolling_With_Monkey(CPlayer::D_LEFT);
		break;

	case CMonkey::RIGHT:
		pPlayer->Rolling_With_Monkey(CPlayer::D_RIGHT);
		break;

	case CMonkey::DOWN:
		pPlayer->Rolling_With_Monkey(CPlayer::D_DOWN);
		break;

	case CMonkey::UP:
		pPlayer->Rolling_With_Monkey(CPlayer::D_UP);
		break;
	}
}

void CMonkey::Turn_Around()
{
	CSoundMgr::Get_Instance()->PlaySound(L"MONKEY_GUGUKAKA.MP3", CSoundMgr::MONSTER);

	m_dwTurnCoolTime = GetTickCount();
	
	m_bIsRightDir = !m_bIsRightDir;

	switch (m_eDir)
	{
	case CMonkey::LEFT:
		m_eDir = CMonkey::RIGHT;
		break;
	case CMonkey::RIGHT:
		m_eDir = CMonkey::LEFT;
		break;

	case CMonkey::DOWN:
		m_eDir = CMonkey::UP;
		break;
	case CMonkey::UP:
		m_eDir = CMonkey::DOWN;
		break;
	}
}

void CMonkey::Set_Color(COLOR eCol)
{
	m_eColor = eCol;
}

CMonkey::COLOR& CMonkey::Get_Color()
{
	return m_eColor;
}

void CMonkey::Set_ThrowDir(DIR eDir)
{
	m_eDir = eDir;
}

CMonkey::DIR & CMonkey::Get_ThrowDir()
{
	return m_eDir;
}

void CMonkey::Change_Color()
{
	if (m_eColor == C_PINK)
	{
		m_eColor = C_BLUE;
	}
	else
	{
		m_eColor = C_PINK;
	}
}

void CMonkey::Change_Dir()
{
	m_bIsRightDir = !m_bIsRightDir;
}
