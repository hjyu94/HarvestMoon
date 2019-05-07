#include "stdafx.h"
#include "BridgeScene.h"


CBridgeScene::CBridgeScene()
{
}


CBridgeScene::~CBridgeScene()
{
	Release();
}

void CBridgeScene::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Stage/BRIDGE.bmp", L"BRIDGE");
	dwClose = GetTickCount();
	m_bIsSound = false;

}

void CBridgeScene::Update()
{
	if (dwClose + 1000 < GetTickCount() && !m_bIsSound)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"BridgeBGM.mp3",  CSoundMgr::CHANNELID::BGM);
		m_bIsSound = true;
	}

	if (dwClose + 4000 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->StopAll();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE_2);
	}
}

void CBridgeScene::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CBridgeScene::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"BRIDGE");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CBridgeScene::Release()
{
}
