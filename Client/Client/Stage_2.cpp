#include "stdafx.h"
#include "Stage_2.h"
#include "Player.h"
#include "RhinoHead.h"
#include "RhinoTail.h"

#include "LineMgr.h"
#include "CollisionMgr.h"
#include "Giraffe.h"

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
	
	if (CObjMgr::Get_Instance()->Get_Player() == nullptr)
	{
		CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(125, 220));
	}
	else
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(125.f, 220.f);
	}

	CObjMgr::Get_Instance()->Get_Player()->Set_CurStage(2);

	// 코뿔소
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CRhinoTail>::Create(290, 282));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CRhinoHead>::Create(462, 307));

	CSoundMgr::Get_Instance()->PlayBGM(L"Stage2BGM.mp3");
	
	
	CScrollMgr::Reset_Scroll();
}

void CStage_2::Update()
{
	if (!m_bIsInit)
	{
		CLineMgr::Get_Instance()->Initialize();
		m_bIsInit = true;
	}

	
	CObjMgr::Get_Instance()->Update();
	CPlayer* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	if (pPlayer->Get_Info().fY >= WINCY/* && CScrollMgr::Get_ScrollY() == 0*/)
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_Hp(0);
	}
	CScrollMgr::ScrollLock();
}

void CStage_2::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

	// ## 충돌 처리
	OBJLIST listPlayer = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::PLAYER);
	OBJLIST listMonster = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::MONSTER);

	// 라이노 꼬리(MONSTER) ~ 플레이어
	// 라이노 머리 ~ 플레이어
	CCollisionMgr::CollisionRect(listPlayer, listMonster);
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
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
}
