#include "stdafx.h"
#include "Stage2Editor.h"
#include "Stage2EditorMgr.h"

CStage2Editor::CStage2Editor()
{
	iBackgroundWidth = 15000;
	iBackgroundHeight = 842;
}


CStage2Editor::~CStage2Editor()
{
	Release();
}

void CStage2Editor::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Stage/stage2_1.bmp", L"stage2_1");
	CStage2EditorMgr::Get_Instance()->Initialize();
}

void CStage2Editor::Update()
{
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		CScrollMgr::Sum_ScrollX(-10.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		CScrollMgr::Sum_ScrollX(+10.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		CScrollMgr::Sum_ScrollY(+10.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		CScrollMgr::Sum_ScrollY(-10.0f);

	CStage2EditorMgr::Get_Instance()->Update();

}

void CStage2Editor::LateUpdate()
{
	CScrollMgr::ScrollLock();
}

void CStage2Editor::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"stage2_1");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC
		, 0 + iScrollX, 392 - iScrollY
		, SRCCOPY);

	CStage2EditorMgr::Get_Instance()->Render(hDC);

	cout << iScrollX << ", " << iScrollY << endl;
}

void CStage2Editor::Release()
{
	CStage2EditorMgr::Destroy_Instance();
}
