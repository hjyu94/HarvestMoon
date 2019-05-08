#include "stdafx.h"
#include "Giraffe.h"
#include "Line.h"
#include "LineMgr.h"
#include "Player.h"
#include "ObjMgr.h"

CGiraffe::CGiraffe()
	: m_pFrameKey(L"")
	, m_eNextState(IDLE)
	, m_eCurState(IDLE)
{
}


CGiraffe::~CGiraffe()
{
}

void CGiraffe::Initialize()
{
	m_fAngle = 45.f;

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/GIRAFFE_IDLE.bmp", L"GIRAFFE_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/GIRAFFE_NECK.bmp", L"GIRAFFE_NECK");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/GIRAFFE_IDLE_LEFT.bmp", L"GIRAFFE_IDLE_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/GIRAFFE_NECK_LEFT.bmp", L"GIRAFFE_NECK_LEFT");

	m_pFrameKey = L"GIRAFFE_IDLE";

	m_tInfo.fCX = 252.f;
	m_tInfo.fCY = 452.f;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 4;
	m_tFrame.iFrameStart_Y = 0;

	m_bIsRightDir = false;

	m_bIs_Collision_With_Player = false;
	m_dwTiltDelay = GetTickCount();
}

int CGiraffe::Update()
{
	CObj::UpdateRect();
	
	if (!m_bIsInit)
	{
		if (m_bIsRightDir)
		{
			m_pLine = new CLine(
				LINEINFO(
					LINEPOS(m_tInfo.fX, m_tRect.top - 25), LINEPOS(m_tRect.right, m_tRect.top - 25)
				)
			);
		}
		else
		{
			m_pLine = new CLine(
				LINEINFO(
					LINEPOS(m_tRect.left, m_tRect.top - 25), LINEPOS(m_tInfo.fX, m_tRect.top - 25)
				)
			);
		}

		CLineMgr::Get_Instance()->AddLine(m_pLine);
		m_bIsInit = true;
	}

	if (m_bIsRightDir)
	{
		if (m_eCurState == IDLE)
		{
			m_pFrameKey = L"GIRAFFE_IDLE";
		}
		else if (m_eCurState == NECK)
		{
			m_pFrameKey = L"GIRAFFE_NECK";
		}
	}
	else
	{
		if (m_eCurState == IDLE)
		{
			m_pFrameKey = L"GIRAFFE_IDLE_LEFT";
		}
		else if (m_eCurState == NECK)
		{
			m_pFrameKey = L"GIRAFFE_NECK_LEFT";
		}
	}

	if (m_bIs_Collision_With_Player)
	{
		if (m_dwTiltDelay + 1000 < GetTickCount())
		{
			m_eNextState = NECK;
		}
	}

	CObj::UpdateRect();
	SceneChange();
	FrameMove();
	return 0;
}

void CGiraffe::LateUpdate()
{
}

void CGiraffe::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (m_bIsRightDir)
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
			m_tInfo.fCX * (m_tFrame.iFrameEnd_X - m_tFrame.iFrameStart_X -1),
			m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
			m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}
}

void CGiraffe::Release()
{
}

void CGiraffe::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CGiraffe::IDLE:
			m_tInfo.fCX = 252.f;
			m_tInfo.fCY = 452.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 4;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CGiraffe::NECK:
			m_tInfo.fCX = 234.f;
			m_tInfo.fCY = 504.f;
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

void CGiraffe::Collision_Proc(CObj * pCounterObj)
{
	if (Is_Counter_One_Of(CPlayer))
	{
		float fPlayerX = pCounterObj->Get_Info().fX;
		float fPlayerY = pCounterObj->Get_Info().fY;
		
		const RECT& rcPlayer = pCounterObj->Get_Rect();

		if (fPlayerY < m_tRect.top
			/*&& rcPlayer.left > m_tRect.left
			&& rcPlayer.right < m_tRect.right*/
			&& !m_bIs_Collision_With_Player
			&& !pCounterObj->Get_IsJumping())
		{
			m_bIs_Collision_With_Player = true;
			m_dwTiltDelay = GetTickCount();
		}
	}
}

void CGiraffe::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		if (m_eCurState == IDLE)
			m_tFrame.iFrameStart_X = 0;
		else if (m_eCurState == NECK)
		{
			--m_tFrame.iFrameStart_X;
			CObjMgr::Get_Instance()->Get_Player()->Rolling_Along_Giraffe(m_bIsRightDir, m_tRect);
		}
	}
}
