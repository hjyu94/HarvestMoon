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

#include "Item.h"

#include "Vertex.h"

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
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Pridelands.bmp", L"Pridelands");
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(130, 370));
	//CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CHedgeHog>::Create(400, 370));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CLizard>::Create(400, 370));

	CItem* pItem;

	//// HP 아이템
	//pItem = CAbstractFactory<CItem>::Create(100, 200);
	//pItem->Set_ID(CItem::ID::HP);
	//CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

	//// MP 아이템
	//pItem = CAbstractFactory<CItem>::Create(200, 200);
	//pItem->Set_ID(CItem::ID::MP);
	//CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

	//// Save 아이템
	//pItem = CAbstractFactory<CItem>::Create(300, 200);
	//pItem->Set_ID(CItem::ID::LIFE);
	//CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);
	//
	//// Life 아이템
	//pItem = CAbstractFactory<CItem>::Create(400, 200);
	//pItem->Set_ID(CItem::ID::SAVE);
	//CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

	CObjMgr::Get_Instance()->AddObject(OBJID::MAP, CAbstractFactory<CVertex>::Create(100, 200));

	CLineMgr::Get_Instance()->Initialize();

	iLife = 3;
}

void CStage::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (CObjMgr::Get_Instance()->Get_Player()->Get_Hp() <= 0)
	{
		iLife--;
		//CObjMgr::Get_Instance()->Get_Player()->Set_Hp(100);

		CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
		CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(130, 370));
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

	// 플레이어 ~ 몬스터
	CCollisionMgr::CollisionRect(listPlayer, listMonster);
	// 플레이어 ~ 아이템
	CCollisionMgr::CollisionRect(listPlayer, listItem);
	// 플레이어 ~ 맵(동글이)
	CCollisionMgr::CollisionRect(listPlayer, listMap);

}

void CStage::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollX();

	//HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Pridelands");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, iScrollX, 2050-iScrollY, SRCCOPY);
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
}
