#include "stdafx.h"
#include "MyMenu.h"
#include "BitmapMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Exit.bmp", L"Exit");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Start.bmp", L"Start");

	CObj* pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f);
	dynamic_cast<CMyButton*>(pObj)->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENUBUTTON, pObj);

	 pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f);
	dynamic_cast<CMyButton*>(pObj)->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENUBUTTON, pObj);

	 pObj = CAbstractFactory<CMyButton>::Create(600.f, 400.f);
	dynamic_cast<CMyButton*>(pObj)->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->AddObject(OBJID::MENUBUTTON, pObj);
}

void CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CMyMenu::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->DeleteID(OBJID::MENUBUTTON);
}
