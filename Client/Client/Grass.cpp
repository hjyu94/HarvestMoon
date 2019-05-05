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

	GdiTransparentBlt(hDC, // ���� ������� DC
		m_tRect.left - iScrollX, m_tRect.top + iScrollY, //��µ� ��ġ�� xy ��ǥ 
		m_tInfo.fCX, m_tInfo.fCY, // ����� ��Ʈ���� ���μ��� ������. 
		hMemDC,
		0, 0, // ���� ��ġ 
		m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
		RGB(223, 154, 220)
	);
}

void CGrass::Release()
{
}
