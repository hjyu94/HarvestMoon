#include "stdafx.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

int CScrollMgr::m_iScrollX = 0;
int CScrollMgr::m_iScrollY = 0;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::ScrollLock()
{
	POINT ptScene = CSceneMgr::Get_Instance()->Get_SceneRect();
	
	// 3000 - 650 = 2350
	if (m_iScrollX < 0) m_iScrollX = 0;
	if (m_iScrollX > ptScene.x - WINCX) m_iScrollX = ptScene.x - WINCX;
	
	// 2500 - 450 = 2050
	if (m_iScrollY < 0) m_iScrollY = 0;
	if (m_iScrollY > ptScene.y - WINCY) m_iScrollY = ptScene.y - WINCY;
}
