#include "stdafx.h"
#include "DeadScene.h"
#include "Player.h"

CDeadScene::CDeadScene()
{
}


CDeadScene::~CDeadScene()
{
	Release();
}

void CDeadScene::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/BLACK_BACKGROUND.bmp", L"BLACK_BACKGROUND");
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySound(L"PLAYER_DEAD.MP3", CSoundMgr::CHANNELID::BGM);
}

void CDeadScene::Update()
{
	CObjMgr::Get_Instance()->Update();
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
	CSoundMgr::Get_Instance()->StopAll();
}
