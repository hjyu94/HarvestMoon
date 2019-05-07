#include "stdafx.h"
#include "RhinoHead.h"


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
	return OBJ_NOEVENT;
}

void CRhinoHead::LateUpdate()
{
}

void CRhinoHead::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left, m_tRect.top, //출력될 위치의 xy 좌표 
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

void CRhinoHead::FrameMove()
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
