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

	// 왼쪽 버튼으로 선을 그어서 리스트에 추가
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
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hLineFile)
	{
		MessageBox(g_hWnd, L"라인 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
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
	MessageBox(g_hWnd, L"로드했습니다", L"stage 2", MB_OK);
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
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"라인 저장 실패", MB_OK);
	}

	DWORD dwByte = 0;

	for (auto& pLine : m_listLine)
	{
		WriteFile(hLineFile, &pLine->Get_LineInfo(), sizeof(LINEINFO), &dwByte, nullptr);
	}
	CloseHandle(hLineFile);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);
}
