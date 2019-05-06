#include "stdafx.h"
#include "BridgeScene.h"


CBridgeScene::CBridgeScene()
{
}


CBridgeScene::~CBridgeScene()
{
}

void CBridgeScene::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/BLACK_BACKGROUND.bmp", L"BLACK_BACKGROUND");
}

void CBridgeScene::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CBridgeScene::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CBridgeScene::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"BLACK_BACKGROUND");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CBridgeScene::Release()
{
}
