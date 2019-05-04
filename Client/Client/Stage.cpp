#include "stdafx.h"
#include "Stage.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "CollisionMgr.h"
#include "BitmapMgr.h"

#include "Player.h"

#include "HedgeHog.h"
#include "Lizard.h"
#include "Fly.h"

#include "Item.h"

#include "Vertex.h"
#include "Block.h"
#include "VerticalBlocck.h"


CStage::CStage()
{
	iBackgroundWidth = 3000;
	iBackgroundHeight = 2500;
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Pridelands.bmp", L"Pridelands");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Stage/stage1.bmp", L"stage1");
	
	if(nullptr == CObjMgr::Get_Instance()->Get_Player())
		CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(130, 340));

	// 도마뱀
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CLizard>::Create(790, 390));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CLizard>::Create(1320, 390));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CLizard>::Create(1390, 26));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CLizard>::Create(500, -140));

	// 고슴도치
	CHedgeHog* pHedgeHog;
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CHedgeHog>::Create(1700, 390));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CHedgeHog>::Create(1980, 60));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CHedgeHog>::Create(850, -50));
	

	// 날파리
	CFly* pFly;
	pFly = CAbstractFactory<CFly>::Create(873, -230);
	pFly->Set_Distance(50.f);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pFly);


	CLineMgr::Get_Instance()->Initialize();

}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->KeyDown('L'))
		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CLizard>::Create(300, 390));

	if (CKeyMgr::Get_Instance()->KeyDown('F'))
		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CFly>::Create(300, 390));

	if (CKeyMgr::Get_Instance()->KeyDown('H'))
		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CHedgeHog>::Create(300, 390));


	if (CKeyMgr::Get_Instance()->KeyDown('I'))
	{
		CItem* pItem;

		// HP 아이템
		pItem = CAbstractFactory<CItem>::Create(100, 200);
		pItem->Set_ID(CItem::ID::HP);
		CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

		// MP 아이템
		pItem = CAbstractFactory<CItem>::Create(200, 200);
		pItem->Set_ID(CItem::ID::MP);
		CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

		// Save 아이템
		pItem = CAbstractFactory<CItem>::Create(300, 200);
		pItem->Set_ID(CItem::ID::LIFE);
		CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

		// Life 아이템
		pItem = CAbstractFactory<CItem>::Create(400, 200);
		pItem->Set_ID(CItem::ID::SAVE);
		CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);
	}
}

void CStage::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

	//CPlayer* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	OBJLIST listPlayer = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::PLAYER);
	OBJLIST listMonster = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::MONSTER);
	OBJLIST listItem = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::ITEM);
	OBJLIST listMap = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::MAP);
	OBJLIST listBlock = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::BLOCK);
	OBJLIST listVerticalBlock = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::VERTICAL_BLOCK);

	// 플레이어 ~ 몬스터
	CCollisionMgr::CollisionRect(listPlayer, listMonster);
	// 플레이어 ~ 아이템
	CCollisionMgr::CollisionRect(listPlayer, listItem);
	// 플레이어 ~ 맵(동글이)
	CCollisionMgr::CollisionRect(listPlayer, listMap);
	// 플레이어 ~ 블락(벽돌, 막음, 돌)
	CCollisionMgr::CollisionRect(listPlayer, listBlock);
	// 플레이어 ~ 가로 블락
	CCollisionMgr::CollisionRect(listPlayer, listVerticalBlock);
}

void CStage::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	HDC hStageDC = CBitmapMgr::Get_Instance()->FindImage(L"stage1");
	
	BitBlt(hDC, 0, 0, WINCX, WINCY, hStageDC
		, 0 + iScrollX, 2050-iScrollY
		, SRCCOPY);
	
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);

	CPlayer* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	TCHAR lpOut[1024];
	wsprintf(lpOut, L"HP: %d", pPlayer->Get_Hp());
	TextOut(hDC, 50, 50, lpOut, lstrlen(lpOut));

	wsprintf(lpOut, L"MP: %d", pPlayer->Get_Mp());
	TextOut(hDC, WINCX - 100, 50, lpOut, lstrlen(lpOut));

	wsprintf(lpOut, L"Life: %d", iLife);
	TextOut(hDC, 50, WINCY - 50, lpOut, lstrlen(lpOut));
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
}
