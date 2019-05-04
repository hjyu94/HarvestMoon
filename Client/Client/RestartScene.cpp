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
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE);
			iLife = 3;
		}
		else if (eState == CMonkeyNPC::STATE::NO)
		{
			PostQuitMessage(0);
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
}
