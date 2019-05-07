#include "stdafx.h"
#include "LineEditor.h"
#include "EditorLineMgr.h"

CLineEditor::CLineEditor()
{
	iBackgroundWidth = 3000;
	iBackgroundHeight = 2500;
}


CLineEditor::~CLineEditor()
{
	Release();
}

void CLineEditor::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Stage/stage1.bmp", L"stage1");
	CEditorLineMgr::Get_Instance()->Initialize();
}

void CLineEditor::Update()
{
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		CScrollMgr::Sum_ScrollX(-10.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		CScrollMgr::Sum_ScrollX(+10.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		CScrollMgr::Sum_ScrollY(+10.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		CScrollMgr::Sum_ScrollY(-10.0f);

	CEditorLineMgr::Get_Instance()->Update();
}

void CLineEditor::LateUpdate()
{
	CScrollMgr::ScrollLock();
}

void CLineEditor::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"stage1");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC
		, 0 + iScrollX, 2050 - iScrollY
		, SRCCOPY);

	CEditorLineMgr::Get_Instance()->Render(hDC);
}

void CLineEditor::Release()
{
	CEditorLineMgr::Destroy_Instance();
}
