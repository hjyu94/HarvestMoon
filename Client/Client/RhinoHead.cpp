#include "stdafx.h"
#include "RhinoHead.h"
#include "Player.h"

CRhinoHead::CRhinoHead()
{
}


CRhinoHead::~CRhinoHead()
{
	Release();
}

void CRhinoHead::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/RHINO_HEAD_IDLE.bmp", L"RHINO_HEAD_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/RHINO_HEAD_UP.bmp", L"RHINO_HEAD_UP");

	m_pFrameKey = L"RHINO_HEAD_IDLE";
	m_tInfo.fCX = 138.f;
	m_tInfo.fCY = 216.f;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 6;
	m_tFrame.iFrameStart_Y = 0;

	m_eCurState = IDLE;
	m_eNextState = IDLE;
}

int CRhinoHead::Update()
{
	CObj::UpdateRect();
	FrameMove();
	StateChange();
	return OBJ_NOEVENT;
}

void CRhinoHead::LateUpdate()
{
}

void CRhinoHead::Render(HDC hDC)
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

	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart_X,
		m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
		m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 0, 255)
	);
}

void CRhinoHead::Release()
{
}

void CRhinoHead::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::IDLE:
			m_pFrameKey = L"RHINO_HEAD_IDLE";
			m_tInfo.fCX = 138.f;
			m_tInfo.fCY = 216.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 6;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::UP:
			m_pFrameKey = L"RHINO_HEAD_UP";
			m_tInfo.fCX = 138.f;
			m_tInfo.fCY = 216.f;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 4;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}

		m_eCurState = m_eNextState;
	}
}

void CRhinoHead::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{

		if (m_eCurState == UP)
		{
			m_eNextState = IDLE;
			m_pFrameKey = L"RHINO_HEAD_IDLE";
		}

		m_tFrame.iFrameStart_X = 0;
	}
}

void CRhinoHead::Collision_Proc(CObj * pCounterObj)
{
	if (Is_Counter_One_Of(CPlayer))
	{
		float fPlayerY = pCounterObj->Get_Info().fY;
		if (static_cast<CPlayer*>(pCounterObj)->Get_CurState() == CPlayer::ROLLING
			&& m_tRect.top <= fPlayerY && fPlayerY <= m_tInfo.fY
			&& m_tInfo.fX -20 <= pCounterObj->Get_Info().fX && pCounterObj->Get_Info().fX <= m_tInfo.fX+20)
		{
			m_eNextState = UP;
			m_pFrameKey = L"RHINO_HEAD_UP";
			static_cast<CPlayer*>(pCounterObj)->Drag_Jump();
		}
	}
}
