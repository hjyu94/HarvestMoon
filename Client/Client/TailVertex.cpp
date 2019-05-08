#include "stdafx.h"
#include "TailVertex.h"


CTailVertex::CTailVertex()
{
}


CTailVertex::~CTailVertex()
{
}

void CTailVertex::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
}

int CTailVertex::Update()
{
	CObj::UpdateRect();
	return 0;
}

void CTailVertex::LateUpdate()
{
}

void CTailVertex::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Ellipse(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}
}

void CTailVertex::Release()
{
}
