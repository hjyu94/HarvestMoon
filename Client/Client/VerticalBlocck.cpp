#include "stdafx.h"
#include "VerticalBlocck.h"


CVerticalBlocck::CVerticalBlocck()
{
}


CVerticalBlocck::~CVerticalBlocck()
{
}

void CVerticalBlocck::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 50.f;
}

int CVerticalBlocck::Update()
{
	CObj::UpdateRect();
	return 0;
}

void CVerticalBlocck::LateUpdate()
{
}

void CVerticalBlocck::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	CObj::UpdateRect();

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);

	//Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
}

void CVerticalBlocck::Release()
{
}
