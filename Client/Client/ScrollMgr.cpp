#include "stdafx.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
float CScrollMgr::m_fScrollX = 0.f;
float CScrollMgr::m_fScrollY = 0.f;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::ScrollLock()
{
	POINT ptScene = CSceneMgr::Get_Instance()->Get_SceneRect();
	
	if (m_fScrollX < 0) m_fScrollX = 0;
	if (m_fScrollX > ptScene.x - WINCX) m_fScrollX = ptScene.x - WINCX;
	
	if (m_fScrollY < 0) m_fScrollY = 0;
	if (m_fScrollY > ptScene.y - WINCY) m_fScrollY = ptScene.y - WINCY;
}
