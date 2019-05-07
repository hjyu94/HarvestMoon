#include "stdafx.h"
#include "Stage_2.h"
#include "Player.h"
#include "RhinoHead.h"
#include "RhinoTail.h"

#include "LineMgr.h"

CStage_2::CStage_2()
{
	iBackgroundWidth = 15000;
	iBackgroundHeight = 842;
}

CStage_2::~CStage_2()
{
	Release();
}

void CStage_2::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Stage/stage2_1.bmp", L"stage2_1");
	
	CScrollMgr::Reset_Scroll();

	
	if (CObjMgr::Get_Instance()->Get_Player() == nullptr)
	{
		CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(125, 220));
	}

	CObjMgr::Get_Instance()->AddObject(OBJID::ETC, CAbstractFactory<CRhinoTail>::Create(290, 282));
	CObjMgr::Get_Instance()->AddObject(OBJID::ETC, CAbstractFactory<CRhinoHead>::Create(462, 307));

	CSoundMgr::Get_Instance()->PlayBGM(L"Stage2BGM.mp3");
}

void CStage_2::Update()
{
	if (!m_bIsInit)
	{
		CLineMgr::Get_Instance()->Initialize();
		m_bIsInit = true;
	}
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::ScrollLock();
}

void CStage_2::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CStage_2::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	HDC hStageDC = CBitmapMgr::Get_Instance()->FindImage(L"stage2_1");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hStageDC
		, 0 + iScrollX, 392 - iScrollY
		, SRCCOPY);

	CLineMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

}

void CStage_2::Release()
{
}
