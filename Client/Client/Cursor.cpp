#include "stdafx.h"
#include "Cursor.h"


CCursor::CCursor()
{
}


CCursor::~CCursor()
{
}

void CCursor::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Cursor/CURSOR.bmp", L"CURSOR");

	m_pFrameKey = L"CURSOR";
	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 58.f;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 4;
	m_tFrame.iFrameStart_Y = 0;
}

int CCursor::Update()
{
	CObj::UpdateRect();
	FrameMove();

	return 0;
}

void CCursor::LateUpdate()
{
}

void CCursor::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"CURSOR");

	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left, m_tRect.top, //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart_X,
		m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
		m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(0, 0, 0)
	);
}

void CCursor::Release()
{
}

//void CCursor::StateChange()
//{
//	if (m_eCurState != m_eNextState)
//	{
//		switch (m_eNextState)
//		{
//		case STATE::IDLE:
//		case STATE::IDLE_LEFT:
//			m_tInfo.fCX = 48.f;
//			m_tInfo.fCY = 28.f;
//			m_tFrame.dwFrameSpeed = 80;
//			m_tFrame.dwFrameTime = GetTickCount();
//			m_tFrame.iFrameStart_X = 0;
//			m_tFrame.iFrameEnd_X = 6;
//			m_tFrame.iFrameStart_Y = 0;
//			break;
//
//		case STATE::DIE:
//		case STATE::DIE_LEFT:
//			m_tInfo.fCX = 50.f;
//			m_tInfo.fCY = 44.f;
//			m_tFrame.dwFrameSpeed = 200;
//			m_tFrame.dwFrameTime = GetTickCount();
//			m_tFrame.iFrameStart_X = 0;
//			m_tFrame.iFrameEnd_X = 5;
//			m_tFrame.iFrameStart_Y = 0;
//			break;
//
//		case STATE::BOMB:
//			m_pFrameKey = L"FLY_BOMB";
//			m_tInfo.fCX = 52.f;
//			m_tInfo.fCY = 52.f;
//			m_tFrame.dwFrameSpeed = 150;
//			m_tFrame.dwFrameTime = GetTickCount();
//			m_tFrame.iFrameStart_X = 0;
//			m_tFrame.iFrameEnd_X = 4;
//			m_tFrame.iFrameStart_Y = 0;
//			break;
//		}
//
//		m_eCurState = m_eNextState;
//	}
//}
