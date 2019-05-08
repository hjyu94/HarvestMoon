#include "stdafx.h"
#include "Stage_2.h"
#include "Player.h"
#include "RhinoHead.h"
#include "RhinoTail.h"

#include "LineMgr.h"
#include "CollisionMgr.h"
#include "Giraffe.h"
#include "Monkey.h"
#include "Ostrich.h"

#include "VerticalBlocck.h"
#include "Item.h"

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
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Stage/GAME_CLEAR.bmp", L"GAME_CLEAR");
	
	if (CObjMgr::Get_Instance()->Get_Player() == nullptr)
	{
		CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create(125, 220));
	}
	else
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(125.f, 220.f);
	}
	CScrollMgr::Reset_Scroll();

	CObjMgr::Get_Instance()->Get_Player()->Set_CurStage(2);

	//// �ڻԼ�
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CRhinoTail>::Create(290, 282));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CRhinoHead>::Create(462, 307));

	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CRhinoTail>::Create(2552-27, 282));
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CRhinoHead>::Create(2724-27, 307));

	// ������ �߰�
	CMonkey* pMonkey;

	// ##1
	pMonkey = CAbstractFactory<CMonkey>::Create(2435,-190);
	pMonkey->Set_Color(CMonkey::C_BLUE);
	pMonkey->Set_ThrowDir(CMonkey::DOWN);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pMonkey);
	
	// ##2
	pMonkey = CAbstractFactory<CMonkey>::Create(2690, -190);
	pMonkey->Set_Color(CMonkey::C_PINK);
	pMonkey->Set_ThrowDir(CMonkey::LEFT);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pMonkey);

	// ##3
	pMonkey = CAbstractFactory<CMonkey>::Create(2925, -190);
	pMonkey->Set_Color(CMonkey::C_BLUE);
	pMonkey->Set_ThrowDir(CMonkey::DOWN);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pMonkey);

	// ##4
	pMonkey = CAbstractFactory<CMonkey>::Create(3155, -190);
	pMonkey->Set_Color(CMonkey::C_BLUE);
	pMonkey->Set_ThrowDir(CMonkey::RIGHT);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pMonkey);
	
	// ##5
	pMonkey = CAbstractFactory<CMonkey>::Create(2575, -60);
	pMonkey->Set_Color(CMonkey::C_BLUE);
	pMonkey->Set_ThrowDir(CMonkey::RIGHT);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pMonkey);
	
	// ##6
	pMonkey = CAbstractFactory<CMonkey>::Create(3070, -60);
	pMonkey->Set_Color(CMonkey::C_BLUE);
	pMonkey->Set_ThrowDir(CMonkey::RIGHT);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pMonkey);
	
	// ##7
	pMonkey = CAbstractFactory<CMonkey>::Create(2575, 135);
	pMonkey->Set_Color(CMonkey::C_PINK);
	pMonkey->Set_ThrowDir(CMonkey::DOWN);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pMonkey);
	
	// ##8
	pMonkey = CAbstractFactory<CMonkey>::Create(2925, 135);
	pMonkey->Set_Color(CMonkey::C_BLUE);
	pMonkey->Set_ThrowDir(CMonkey::LEFT);
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, pMonkey);
	
	// Save Item
	CItem* pItem;
	pItem = CAbstractFactory<CItem>::Create(2320, 160);
	pItem->Set_ID(CItem::ID::SAVE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);

	pItem = CAbstractFactory<CItem>::Create(4000, 160);
	pItem->Set_ID(CItem::ID::SAVE);
	CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);


	// Ostrich 
	CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<COstrich>::Create(4112, 300));
	
	//// �׽�Ʈ
	//CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<COstrich>::Create(300, 300));
	//CObjMgr::Get_Instance()->AddObject(OBJID::VERTICAL_BLOCK, CAbstractFactory<CVerticalBlocck>::Create(500, 300));

	
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage2BGM.mp3");
	//this->Set_Pos(125.f, 220.f);
	m_bIsClear = false;
	m_dwClear = GetTickCount();
	m_bEndingMusicStart = false;
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
	
	
	if (pPlayer->Get_Info().fX >= 11300 && !m_bIsClear)
	{
		m_bIsClear = true;
		m_dwClear = GetTickCount();
		
	}
	CScrollMgr::ScrollLock();

}

void CStage_2::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

	// ## �浹 ó��
	OBJLIST listPlayer = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::PLAYER);
	OBJLIST listMonster = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::MONSTER);
	OBJLIST listVerticalBlock = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::VERTICAL_BLOCK);
	OBJLIST listItem = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::ITEM);

	// ���̳� ����(MONSTER) ~ �÷��̾�
	// ���̳� �Ӹ� ~ �÷��̾�
	CCollisionMgr::CollisionRect(listPlayer, listMonster);

	// Verticalblock ~ �÷��̾�
	CCollisionMgr::CollisionRect(listPlayer, listVerticalBlock);

	// ������ ~ �÷��̾�
	CCollisionMgr::CollisionRect(listPlayer, listItem);
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



	if (m_bIsClear && m_dwClear + 1000 < GetTickCount())
	{
		if (!m_bEndingMusicStart)
		{
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlayBGM(L"ENDING.mp3");
			CSoundMgr::Get_Instance()->PlaySound(L"CLAPPING.mp3", CSoundMgr::CHANNELID::EFFECT);
			m_bEndingMusicStart = true;
		}
		// Ŭ��¡ ��� ���
		HDC hClearDC = CBitmapMgr::Get_Instance()->FindImage(L"GAME_CLEAR");
		GdiTransparentBlt(hDC, // ���� ������� DC
			132, 40, //��µ� ��ġ�� xy ��ǥ 
			386, 63, // ����� ��Ʈ���� ���μ��� ������. 
			hClearDC,
			0, 0, // ���� ��ġ 
			386, 63,// ����� ��Ʈ���� ��ü ���μ��� ����. 
			RGB(255,255,255)
		);
	}
	else
	{
		// HP, MP ǥ��
		CPlayer* pPlayer = CObjMgr::Get_Instance()->Get_Player();
		int iHpLvl = pPlayer->Get_Hp() / 10;
		HDC hHpDC = CBitmapMgr::Get_Instance()->FindImage(L"HP");
		GdiTransparentBlt(hDC, // ���� ������� DC
			40, 40, //��µ� ��ġ�� xy ��ǥ 
			60, 28, // ����� ��Ʈ���� ���μ��� ������. 
			hHpDC,
			60 * iHpLvl, 0, // ���� ��ġ 
			60, 28,// ����� ��Ʈ���� ��ü ���μ��� ����. 
			RGB(255, 255, 255)
		);

		int iMpLvl = pPlayer->Get_Mp() / 10;
		HDC hMpDC = CBitmapMgr::Get_Instance()->FindImage(L"MP");
		GdiTransparentBlt(hDC, // ���� ������� DC
			WINCX - 60 - 40, 40, //��µ� ��ġ�� xy ��ǥ 
			60, 28, // ����� ��Ʈ���� ���μ��� ������. 
			hMpDC,
			60 * iMpLvl, 0, // ���� ��ġ 
			60, 28,// ����� ��Ʈ���� ��ü ���μ��� ����. 
			RGB(255, 255, 255)
		);

		// ��� ǥ��
		HDC hLionzKingDC = CBitmapMgr::Get_Instance()->FindImage(L"LIONKING");
		GdiTransparentBlt(hDC, // ���� ������� DC
			40, WINCY - 80, //��µ� ��ġ�� xy ��ǥ 
			47, 63, // ����� ��Ʈ���� ���μ��� ������. 
			hLionzKingDC,
			0, 0, // ���� ��ġ 
			47, 63,// ����� ��Ʈ���� ��ü ���μ��� ����. 
			RGB(0, 0, 0)
		);

		HDC hLife = nullptr;
		if (iLife >= 4) hLife = CBitmapMgr::Get_Instance()->FindImage(L"NUM_4");
		else if (iLife >= 3) hLife = CBitmapMgr::Get_Instance()->FindImage(L"NUM_3");
		else if (iLife == 2) hLife = CBitmapMgr::Get_Instance()->FindImage(L"NUM_2");
		else if (iLife == 1) hLife = CBitmapMgr::Get_Instance()->FindImage(L"NUM_1");
		GdiTransparentBlt(hDC, // ���� ������� DC
			90, WINCY - 60, //��µ� ��ġ�� xy ��ǥ 
			38, 38, // ����� ��Ʈ���� ���μ��� ������. 
			hLife,
			0, 0, // ���� ��ġ 
			38, 38,// ����� ��Ʈ���� ��ü ���μ��� ����. 
			RGB(32, 81, 12)
		);
	}
}

void CStage_2::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::MONSTER);
}
