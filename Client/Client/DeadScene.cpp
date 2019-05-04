#include "stdafx.h"
#include "DeadScene.h"
#include "Player.h"

CDeadScene::CDeadScene()
{
}


CDeadScene::~CDeadScene()
{
}

void CDeadScene::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/BLACK_BACKGROUND.bmp", L"BLACK_BACKGROUND");
}

void CDeadScene::Update()
{
	CObjMgr::Get_Instance()->Update();

	/*if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE))
	{
		CObjMgr::Get_Instance()->DeleteID(OBJID::PLAYER);
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE);
	}*/
}

void CDeadScene::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CDeadScene::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"BLACK_BACKGROUND");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CDeadScene::Release()
{
}
