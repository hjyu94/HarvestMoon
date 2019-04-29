#include "stdafx.h"
#include "LineEditorTest.h"
#include "LineMgr.h"
#include "TestPlayer.h"

CLineEditorTest::CLineEditorTest()
{
}


CLineEditorTest::~CLineEditorTest()
{
}	

void CLineEditorTest::Initialize()
{
	CObjMgr::Get_Instance()->AddObject(OBJID::PLAYER, CAbstractFactory<CTestPlayer>::Create(130, 370));
	CLineMgr::Get_Instance()->Initialize();
}

void CLineEditorTest::Update()
{
	CObjMgr::Get_Instance()->Update();

	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();

	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
	{
		CScrollMgr::Sum_ScrollX(-4.f);
		cout << iScrollX << ", " << iScrollY << endl;
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
	{
		CScrollMgr::Sum_ScrollX(+4.f);
		cout << iScrollX << ", " << iScrollY << endl;
	}
}

void CLineEditorTest::LateUpdate()
{
	CObjMgr::Get_Instance()->LateUpdate();
}

void CLineEditorTest::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CLineEditorTest::Release()
{
}
