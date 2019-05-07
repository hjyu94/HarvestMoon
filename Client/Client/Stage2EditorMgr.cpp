#include "stdafx.h"
#include "Stage2EditorMgr.h"

#include "Line.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CStage2EditorMgr)

CStage2EditorMgr::CStage2EditorMgr()
{
}

CStage2EditorMgr::~CStage2EditorMgr()
{
	Release();
}

void CStage2EditorMgr::Initialize()
{
	LoadData();
}

void CStage2EditorMgr::Render(HDC hDC)
{
	for (auto& pObj : m_listLine)
	{
		pObj->Render(hDC);
	}
}

void CStage2EditorMgr::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	
	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	pt.x += iScrollX;
	pt.y -= iScrollY;

	// ���� ��ư���� ���� �׾ ����Ʈ�� �߰�
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

	if (CKeyMgr::Get_Instance()->KeyDown('L'))
	{
		LoadData();
	}

	if (CKeyMgr::Get_Instance()->KeyDown('S'))
	{
		SaveData();
	}
}

void CStage2EditorMgr::Release()
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

void CStage2EditorMgr::LoadData()
{
	HANDLE hLineFile = CreateFile(L"../Data/Stage2/Line.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// ���⼭ 2, 5���� �ٲ�. ������ �б������ OPEN_EXISTING - �̹� �����ϴ� ������ ���ٴٶ�� �ǹ�. 

	if (INVALID_HANDLE_VALUE == hLineFile)
	{
		MessageBox(g_hWnd, L"���� ������ �о���� ���߽��ϴ�", L"�ε� ����", MB_OK);
		return;
	}
	LINEINFO tLineInfo = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hLineFile, &tLineInfo, sizeof(LINEINFO), &dwByte, nullptr);
		if (0 == dwByte) break;
		m_listLine.emplace_back(new CLine(tLineInfo));
	}

	CloseHandle(hLineFile);
	MessageBox(g_hWnd, L"�ε��߽��ϴ�", L"stage 2", MB_OK);
}

void CStage2EditorMgr::SaveData()
{
	HANDLE hLineFile = CreateFile(
		L"../Data/Stage2/Line.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hLineFile)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"���� ���� ����", MB_OK);
	}

	DWORD dwByte = 0;

	for (auto& pLine : m_listLine)
	{
		WriteFile(hLineFile, &pLine->Get_LineInfo(), sizeof(LINEINFO), &dwByte, nullptr);
	}
	CloseHandle(hLineFile);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);
}
