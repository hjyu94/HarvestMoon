#include "stdafx.h"
#include "Logo.h"

#include "Player.h"
#include "Giraffe.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Logo/Logo.bmp", L"Logo");

	//CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CGiraffe>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());
}

void CLogo::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CLogo::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();

	// 추후 뭔가 키를 누르면 씬이 바뀌도록 만들것이다. 
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
	}
}

void CLogo::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Logo");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release()
{
}
