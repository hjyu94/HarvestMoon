#include "stdafx.h"
#include "Block.h"
#include "Line.h"

CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

void CBlock::Initialize()
{
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 10.f;
}

int CBlock::Update()
{
	return 0;
}

void CBlock::LateUpdate()
{
}

void CBlock::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	CObj::UpdateRect();

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);

	//Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
}

void CBlock::Release()
{
}
