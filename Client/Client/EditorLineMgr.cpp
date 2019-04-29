#include "stdafx.h"
#include "EditorLineMgr.h"
#include "Line.h"

CEditorLineMgr* CEditorLineMgr::m_pInstance = nullptr;

CEditorLineMgr::CEditorLineMgr()
{
}

CEditorLineMgr::~CEditorLineMgr()
{
	Release();
}

void CEditorLineMgr::Initialize()
{
	m_dwPosRenderTime = GetTickCount();
}

void CEditorLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_listLine)
	{
		pLine->Render(hDC);
	}
}

void CEditorLineMgr::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();
	
	pt.x += iScrollX;
	pt.y += iScrollY;

	if (m_dwPosRenderTime + 1000 < GetTickCount())
	{
		cout << pt.x << ", " << pt.y << endl;
		m_dwPosRenderTime = GetTickCount();
	}

	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		CScrollMgr::Sum_ScrollX(-5.f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		CScrollMgr::Sum_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
		CScrollMgr::Sum_ScrollY(-5.f);
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		CScrollMgr::Sum_ScrollY(5.f);

	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
	{
		LINEINFO tStartInfo =
		{
			LINEPOS(float(pt.x), float(pt.y)),
			LINEPOS(float(pt.x), float(pt.y))
		};
		m_listLine.emplace_back(new CLine(tStartInfo));
	}
	if (CKeyMgr::Get_Instance()->KeyUP(VK_LBUTTON))
	{
		m_listLine.back()->Set_LineInfo(LINEPOS(float(pt.x), float(pt.y)));
	}
	if (CKeyMgr::Get_Instance()->KeyUP('S'))
		SaveData();
}

void CEditorLineMgr::Release()
{
	for (auto& pLine : m_listLine)
	{
		if (pLine)
		{
			delete pLine;
			pLine = nullptr;
		}
	}

	m_listLine.clear();
}


void CEditorLineMgr::SaveData()
{
	HANDLE hFile = CreateFile(
		L"../Data/Line.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"저장 실패", MB_OK);
	}

	DWORD dwByte = 0;

	for (auto& pLine : m_listLine)
	{
		WriteFile(hFile, &pLine->Get_LineInfo(), sizeof(LINEINFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);
}
