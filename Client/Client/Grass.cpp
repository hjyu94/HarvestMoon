#include "stdafx.h"
#include "Grass.h"


CGrass::CGrass()
{
}


CGrass::~CGrass()
{
}

void CGrass::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/GRASS.bmp", L"GRASS");
	m_tInfo.fCX = 196.f;
	m_tInfo.fCY = 42.f;
}

int CGrass::Update()
{
	return 0;
}

void CGrass::LateUpdate()
{
}

void CGrass::Render(HDC hDC)
{
	CObj::UpdateRect();
	
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"GRASS");

	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		0, 0, // 시작 위치 
		m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(223, 154, 220)
	);
}

void CGrass::Release()
{
}
