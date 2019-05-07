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
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Logo/Logo_1.bmp", L"Logo_1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Logo/Logo_2.bmp", L"Logo_2");
	m_dwIntro = GetTickCount();
}

void CLogo::Update()
{
}

void CLogo::LateUpdate()
{
	// ġƮŰ
	// Q ������ ��������1 ����
	if (CKeyMgr::Get_Instance()->KeyDown('Q'))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE);
	}
	// W ������ �������� 2 ����
	if (CKeyMgr::Get_Instance()->KeyDown('W'))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE_2);
	}

	// L ������ ���� ������ ����
	if (CKeyMgr::Get_Instance()->KeyDown('L'))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LINE_EDIT);
	}

	// T ������ stage2 ���� ������ ����
	if (CKeyMgr::Get_Instance()->KeyDown('T'))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LINE_EDIT_2);
	}
	
	
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = nullptr;

	if (m_dwIntro + 2000 > GetTickCount())
	{
		hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Logo_1");
	}
	else
	{
		hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Logo_2");
	}

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release()
{
}
