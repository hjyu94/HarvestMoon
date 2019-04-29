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
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CVertex::Release()
{
}
