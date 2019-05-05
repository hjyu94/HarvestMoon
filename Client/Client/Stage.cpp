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
#include "Hyena.h"

#include "Item.h"

#include "Vertex.h"
#include "Block.h"
#include "VerticalBlocck.h"


CStage::CStage()
{
	iBackgroundWidth = 3000;
	iBackgroundHeight = 2500;
	m_bIsBossInit = false;
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
	//CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(2000, -2000));
	
	// 테스트
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CHyena>::Create(300, 390));

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


	CItem* pItem = CAbstractFactory<CItem>::Create(800, -300);
	pItem->Set_ID(CItem::ID::SAVE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);


	CLineMgr::Get_Instance()->Initialize();
/*
	CScrollMgr::Sum_ScrollX(2200);
	CScrollMgr::Sum_ScrollY(2050);*/

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

	if (CKeyMgr::Get_Instance()->KeyPressing(VK_F4))
	{
		iLife = 1;
	}


	CPlayer* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	if (pPlayer->Get_Info().fX > 2600 && pPlayer->Get_Info().fY < -1500)
	{
		if (!m_bIsBossInit)
		{
			CHyena* pHyena = CAbstractFactory<CHyena>::Create(3000 - 77, -1600);
			CObjMgr::Get_Instance()->Set_Boss(pHyena);
			CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pHyena);
			m_bIsBossInit = true;
		}
	}
}

void CStage::LateUpdate()
{
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
	// 플레이어 ~ 세로 블락
	CCollisionMgr::CollisionRect(listPlayer, listVerticalBlock);

	// 하이에나 ~ 세로블락
	CCollisionMgr::CollisionRect(listMonster, listVerticalBlock);
	
	CObjMgr::Get_Instance()->LateUpdate();

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

	// HP, MP 표시
	CPlayer* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	int iHpLvl = pPlayer->Get_Hp() / 10;
	HDC hHpDC = CBitmapMgr::Get_Instance()->FindImage(L"HP");
	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		40, 40, //출력될 위치의 xy 좌표 
		60, 28, // 출력할 비트맵의 가로세로 사이즈. 
		hHpDC,
		60 *iHpLvl, 0, // 시작 위치 
		60, 28,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255,255,255)
	);

	int iMpLvl = pPlayer->Get_Mp() / 10;
	HDC hMpDC = CBitmapMgr::Get_Instance()->FindImage(L"MP");
	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		WINCX-60-40, 40, //출력될 위치의 xy 좌표 
		60, 28, // 출력할 비트맵의 가로세로 사이즈. 
		hMpDC,
		60 * iMpLvl, 0, // 시작 위치 
		60, 28,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);
	
	// 목숨 표시
	HDC hLionzKingDC = CBitmapMgr::Get_Instance()->FindImage(L"LIONKING");
	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		40, WINCY - 80, //출력될 위치의 xy 좌표 
		47, 63, // 출력할 비트맵의 가로세로 사이즈. 
		hLionzKingDC,
		0, 0, // 시작 위치 
		47, 63,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(0, 0, 0)
	);

	HDC hLife = nullptr;
	if (iLife >= 3) hLife = CBitmapMgr::Get_Instance()->FindImage(L"NUM_3");
	else if (iLife == 2) hLife = CBitmapMgr::Get_Instance()->FindImage(L"NUM_2");
	else if (iLife == 1) hLife = CBitmapMgr::Get_Instance()->FindImage(L"NUM_1");
	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		90, WINCY - 60, //출력될 위치의 xy 좌표 
		38, 38, // 출력할 비트맵의 가로세로 사이즈. 
		hLife,
		0, 0, // 시작 위치 
		38, 38,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(32, 81, 12)
	);
}

void CStage::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
	CObjMgr::Get_Instance()->DeleteID(OBJID::ITEM);
}
