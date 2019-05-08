#include "stdafx.h"
#include "RestartScene.h"

#include "AbstractFactory.h"
#include "Cursor.h"
#include "MonkeyNPC.h"
#include "Player.h"
CRestartScene::CRestartScene()
{
}


CRestartScene::~CRestartScene()
{
	Release();
}

void CRestartScene::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Stage/DIE_SCENE.bmp", L"DIE_SCENE");
	CObjMgr::Get_Instance()->AddObject(OBJID::ETC, CAbstractFactory<CCursor>::Create(150, 160));
	CObjMgr::Get_Instance()->AddObject(OBJID::ETC, CAbstractFactory<CMonkeyNPC>::Create(WINCX/2, 300));
	CSoundMgr::Get_Instance()->PlaySound(L"RESTART.MP3", CSoundMgr::CHANNELID::BGM);
	m_dwContinueSelect = GetTickCount();
	m_bIsCountinueSelect = false;
}

void CRestartScene::Update()
{
	CObj* pCursor = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::ETC).front();
	CMonkeyNPC* pMonkey = (CMonkeyNPC*)(CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::ETC).back());

	if (CKeyMgr::Get_Instance()->KeyDown(VK_LEFT))
	{
		pCursor->Set_Pos(150.f, 160.f);
		pMonkey->Set_State(CMonkeyNPC::STATE::YES);
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_RIGHT))
	{
		pCursor->Set_Pos(340.f, 160.f);
		pMonkey->Set_State(CMonkeyNPC::STATE::NO);
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		CMonkeyNPC::STATE eState = pMonkey->Get_State();
		if (eState == CMonkeyNPC::STATE::YES)
		{
			m_bIsCountinueSelect = true;
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"MONKEYNPC.MP3", CSoundMgr::CHANNELID::MONSTER);
			m_dwContinueSelect = GetTickCount();
		}
		else if (eState == CMonkeyNPC::STATE::NO)
		{
			PostQuitMessage(0);
		}
	}

	if (m_bIsCountinueSelect)
	{
		if (m_dwContinueSelect + 2500 < GetTickCount())
		{
			int iCurStage = CObjMgr::Get_Instance()->Get_Player()->Get_CurStage();
			if (iCurStage == 1)
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE);
			}
			else if (iCurStage == 2)
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE_2);
			}

			CObjMgr::Get_Instance()->Get_Player()->Initialize();
			CScrollMgr::Reset_Scroll();
			iLife = 3;
		}
	}
	CObjMgr::Get_Instance()->Update();
}

void CRestartScene::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CRestartScene::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"DIE_SCENE");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CRestartScene::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::ETC);
	CSoundMgr::Get_Instance()->StopAll();
}
