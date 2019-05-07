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
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CTailVertex::Release()
{
}
