#include "stdafx.h"
#include "LineEditor.h"
#include "EditorLineMgr.h"

CLineEditor::CLineEditor()
{
}


CLineEditor::~CLineEditor()
{
}

void CLineEditor::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Pridelands.bmp", L"Pridelands");
	
}

void CLineEditor::Update()
{
	/*if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		CScrollMgr::Sum_ScrollX(-5.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		CScrollMgr::Sum_ScrollX(+5.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		CScrollMgr::Sum_ScrollY(-5.0f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		CScrollMgr::Sum_ScrollY(+5.0f);*/
	CEditorLineMgr::Get_Instance()->Update();
}

void CLineEditor::LateUpdate()
{
}

void CLineEditor::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Pridelands");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, iScrollX, 2050+ iScrollY, SRCCOPY);
	
	CEditorLineMgr::Get_Instance()->Render(hDC);
}

void CLineEditor::Release()
{
	CEditorLineMgr::Destroy_Instance();
}
