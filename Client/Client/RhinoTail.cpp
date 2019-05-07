#include "stdafx.h"
#include "RhinoTail.h"
#include "TailVertex.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CRhinoTail::CRhinoTail()
{
}


CRhinoTail::~CRhinoTail()
{
}

void CRhinoTail::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/RHINO_TAIL.bmp", L"RHINO_TAIL");

	m_pFrameKey = L"RHINO_TAIL";
	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 140.f;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 10;
	m_tFrame.iFrameStart_Y = 0;

	m_fDist = 30.f;
	m_pTailVertex = CAbstractFactory<CTailVertex>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, m_pTailVertex);
}

int CRhinoTail::Update()
{
	CObj::UpdateRect();
	FrameMove();
	
	switch (m_tFrame.iFrameStart_X)
	{
	case 0:
		m_fTheta = 45.f;
		break;

	case 1:
		m_fTheta = 60.f;
		break;

	case 2:
		m_fTheta = 80.f;
		break;

	case 3:
		m_fTheta = 90.f;
		break;

	case 4:
		m_fTheta = 120.f;
		break;

	case 5:
		m_fTheta = 135.f;
		break;

	case 6:
		m_fTheta = 120.f;
		break;

	case 7:
		m_fTheta = 90.f;
		break;

	case 8:
		m_fTheta = 80.f;
		break;

	case 9:
		m_fTheta = 60.f;
		break;
	}

	m_pTailVertex->Set_Pos(m_tInfo.fX + m_fDist*cosf(ToRadian(m_fTheta)), m_tInfo.fY + m_fDist*sinf(ToRadian(m_fTheta)));
	m_pTailVertex->Update();
	return 0;
}

void CRhinoTail::LateUpdate()
{
}

void CRhinoTail::Render(HDC hDC)
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
		RGB(255, 255, 255)
	);

	m_pTailVertex->Render(hDC);
	//MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	//LineTo(hDC, );
}

void CRhinoTail::Release()
{
}

void CRhinoTail::FrameMove()
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
