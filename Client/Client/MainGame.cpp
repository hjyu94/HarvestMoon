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
	//m_hBackbufferDC = CreateCompatibleDC(m_hDC); // ���ڸ� �Ѱ��ָ� ���� ����ϰ� �ִ� DC�� ȣȯ�� �Ǵ� �޸� DC�� �Ҵ����ִ� �Լ�. 

	// �۾��� ��ȭ��. 
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/BackBuffer.bmp", L"BackBuffer");

	// UI
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/LIONKING.bmp", L"LIONKING");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/NUM_1.bmp", L"NUM_1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/NUM_2.bmp", L"NUM_2");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/NUM_3.bmp", L"NUM_3");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/HP.bmp", L"HP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/MP.bmp", L"MP");

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
	CScrollMgr::ScrollLock();
}

void CMainGame::Render()
{
	//HDC hmemDC = CBitmapMgr::Get_Instance()->FindImage(L"Back");
	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	
	HDC hBackDC = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	CSceneMgr::Get_Instance()->Render(hBackDC);


	// �� ����
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
