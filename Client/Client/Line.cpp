#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(LINEINFO & rLineInfo)
	:m_tInfo(rLineInfo)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	MoveToEx(hDC, static_cast<int>(m_tInfo.tLeftPoint.fx) - iScrollX, static_cast<int>(m_tInfo.tLeftPoint.fy)+iScrollY, nullptr);
/*
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
		LineTo(hDC, static_cast<int>(m_tInfo.tRightPoint.fx) - iScrollX, static_cast<int>(m_tInfo.tRightPoint.fy)+iScrollY);
	*/
	LineTo(hDC, static_cast<int>(m_tInfo.tRightPoint.fx) - iScrollX, static_cast<int>(m_tInfo.tRightPoint.fy)+iScrollY);
}
