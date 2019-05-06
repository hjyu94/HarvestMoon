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
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_eDir = DIR::L;
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

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		if (m_eDir == L)
		{
			Ellipse(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
		}
		else
		{
			Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
		}
	}
}

void CVertex::Release()
{
}
