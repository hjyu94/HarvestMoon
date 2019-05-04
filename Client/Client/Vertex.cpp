#include "stdafx.h"
#include "Vertex.h"


CVertex::CVertex()
{
}


CVertex::~CVertex()
{
}

void CVertex::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
}

int CVertex::Update()
{
	CObj::UpdateRect();
	return 0;
}

void CVertex::LateUpdate()
{
}

void CVertex::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	if(CKeyMgr::Get_Instance()->KeyPressing('A'))
		Ellipse(hDC, m_tRect.left-iScrollX, m_tRect.top+iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);

	//Ellipse(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
}

void CVertex::Release()
{
}
