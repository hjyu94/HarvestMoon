#include "stdafx.h"
#include "Stage.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "Player.h"
#include "BitmapMgr.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Background.bmp", L"Background");
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());
	CLineMgr::Get_Instance()->Initialize();
}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CStage::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Background");
	BitBlt(hDC, iScrollX, 0, 1920, 1200, hMemDC, 0, 600, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
}
