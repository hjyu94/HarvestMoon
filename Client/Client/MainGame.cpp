#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

#include "CollisionMgr.h"
#include "BitmapMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Back.bmp", L"Back");

	// �۾��� ��ȭ��. 
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/BackBuffer.bmp", L"BackBuffer");

	CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOGO);
	
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::Get_Instance()->LateUpdate();
	CKeyMgr::Get_Instance()->KeyUpdate();
}

void CMainGame::Render()
{
	HDC hBackDC = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hmemDC = CBitmapMgr::Get_Instance()->FindImage(L"Back");

	BitBlt(hBackDC, 0, 0, WINCX, WINCY, hmemDC, 0, 0, SRCCOPY);

	// ���⿡�� ���Ŵ��� -> �� -> ObjMgr�� ������ �� ��ü�� �� ���ư��ڳ� 
	CSceneMgr::Get_Instance()->Render(hBackDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	
	CLineMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CBitmapMgr::Destroy_Instance(); 
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destory_Instance();
}
