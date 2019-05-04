#include "stdafx.h"
#include "EditorLineMgr.h"
#include "Line.h"
#include "Vertex.h"
#include "Block.h"
#include "AbstractFactory.h"
#include "VerticalBlocck.h"
#include "Fly.h"
#include "Lizard.h"
#include "HedgeHog.h"
#include "Item.h"
#include "Obj.h"

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
	LoadData();
}

void CEditorLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_listLine)
	{
		pLine->Render(hDC);
	}
	for (auto& pVertex : m_listVertex)
	{
		pVertex->Render(hDC);
	}
	for (auto& pBlock : m_listBlock)
	{
		pBlock->Render(hDC);
	}
	for (auto& pVBlock : m_listVerticalBlock)
	{
		pVBlock->Render(hDC);
	}
	for (int i = 0; i < ID::END; ++i)
	{
		for (auto& pObj : m_listEnum[i])
		{
			pObj->Render(hDC);
		}
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
	pt.y -= iScrollY;

	//if (m_dwPosRenderTime + 1000 < GetTickCount())
	//{
	//	cout << pt.x << ", " << pt.y << endl;
	//	m_dwPosRenderTime = GetTickCount();
	//}


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

	// 오른쪽 버튼으로 벌택스를 추가
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
	{
		CVertex* pVertex = new CVertex();
		pVertex->Initialize();
		pVertex->Set_Pos(float(pt.x), float(pt.y));
		m_listVertex.emplace_back(pVertex);
	}

	// 'B' 누르면 마우스 위치에 block 추가
	if (CKeyMgr::Get_Instance()->KeyDown('B'))
	{
		CBlock* pBlock = CAbstractFactory<CBlock>::Create(float(pt.x), float(pt.y));
		m_listBlock.emplace_back(pBlock);
	}

	// 'V'로 Vertical Block 추가
	if (CKeyMgr::Get_Instance()->KeyDown('V'))
	{
		CVerticalBlocck* pBlock = CAbstractFactory<CVerticalBlocck>::Create(float(pt.x), float(pt.y));
		pBlock->UpdateRect();
		m_listVerticalBlock.emplace_back(pBlock);
	}

	//### 지우기
	if (CKeyMgr::Get_Instance()->KeyDown(VK_DELETE))
	{
		for (auto& iter = m_listBlock.begin()
			; iter != m_listBlock.end()
			; )
		{
			if (PtInRect(&(*iter)->Get_Rect(), pt))
			{
				delete *iter;
				*iter = nullptr;
				iter = m_listBlock.erase(iter);
			}
			else
				iter++;
		}

		for (auto& iter = m_listVertex.begin()
			; iter != m_listVertex.end()
			; )
		{
			if (PtInRect(&(*iter)->Get_Rect(), pt))
			{
				delete *iter;
				*iter = nullptr;
				iter = m_listVertex.erase(iter);
			}
			else
				iter++;
		}

		for (auto& iter = m_listVerticalBlock.begin()
			; iter != m_listVerticalBlock.end()
			; )
		{
			if (PtInRect(&(*iter)->Get_Rect(), pt))
			{
				delete *iter;
				*iter = nullptr;
				iter = m_listVerticalBlock.erase(iter);
			}
			else
				iter++;
		}
	}

	if (CKeyMgr::Get_Instance()->KeyDown('R'))
	{
		Release();
	}

	if (CKeyMgr::Get_Instance()->KeyDown('L'))
	{
		LoadData();
	}

	if (CKeyMgr::Get_Instance()->KeyDown('S'))
	{
		SaveData();
	}

	for (auto& pVertex : m_listVertex)
	{
		pVertex->Update();
	}

	for (int i = 0; i < ID::END; ++i)
	{
		for (auto& pObj : m_listEnum[i])
		{
			pObj->Update();
		}
	}
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

	for (auto& pVertex : m_listVertex)
	{
		if (pVertex)
		{
			delete pVertex;
			pVertex = nullptr;
		}
	}

	for (auto& pBlock : m_listBlock)
	{
		if (pBlock)
		{
			delete pBlock;
			pBlock = nullptr;
		}
	}
	for (auto& pVBlock : m_listVerticalBlock)
	{
		if (pVBlock)
		{
			delete pVBlock;
			pVBlock = nullptr;
		}
	}

	for (int i = 0; i < ID::END; ++i)
	{
		for (auto& iter = m_listEnum[i].begin()
			; iter != m_listEnum[i].end()
			; )
		{
			if (*iter)
			{
				delete *iter;
				*iter = nullptr;
				iter = m_listEnum[i].erase(iter);
			}
		}
		m_listEnum[i].clear();
	}
	m_listLine.clear();
	m_listVertex.clear();
	m_listBlock.clear();
	m_listVerticalBlock.clear();
}


void CEditorLineMgr::SaveData()
{
	/********************************************************/
	HANDLE hFile = CreateFile(
		L"../Data/Line.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"라인 저장 실패", MB_OK);
	}

	DWORD dwByte = 0;

	for (auto& pLine : m_listLine)
	{
		WriteFile(hFile, &pLine->Get_LineInfo(), sizeof(LINEINFO), &dwByte, nullptr);
	}
	CloseHandle(hFile);

	/********************************************************/
	
	HANDLE hFile2 = CreateFile(
		L"../Data/Vertex.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFile2)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertex 저장 실패", MB_OK);
	}

	DWORD dwByte2 = 0;

	for (auto& pVertex : m_listVertex)
	{
		WriteFile(hFile2, &pVertex->Get_Info(), sizeof(INFO), &dwByte2, nullptr);
	}
	CloseHandle(hFile2);

	/********************************************************/

	HANDLE hFile3 = CreateFile(
		L"../Data/Block.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFile3)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"블록 저장 실패", MB_OK);
	}

	DWORD dwByte3 = 0;

	for (auto& pBlock : m_listBlock)
	{
		WriteFile(hFile3, &pBlock->Get_Info(), sizeof(INFO), &dwByte3, nullptr);
	}
	CloseHandle(hFile3);

	/********************************************************/

	HANDLE hFile4 = CreateFile(
		L"../Data/VerticalBlock.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFile4)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}

	DWORD dwByte4 = 0;

	cout << m_listVerticalBlock.size() << endl;

	for (auto& pVerticalBlock : m_listVerticalBlock)
	{
		WriteFile(hFile3, &pVerticalBlock->Get_Info(), sizeof(INFO), &dwByte4, nullptr);
	}
	CloseHandle(hFile4);
	
	/********************************************************/
	
	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);
}

void CEditorLineMgr::LoadData()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"라인 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}
	LINEINFO tLineInfo = {};
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tLineInfo, sizeof(LINEINFO), &dwByte, nullptr);
		if (0 == dwByte)
		{
			break;
		}
		m_listLine.emplace_back(new CLine(tLineInfo));
	}
	CloseHandle(hFile);

	/********************************************************/

	HANDLE hFile2 = CreateFile(L"../Data/Vertex.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFile2)
	{
		MessageBox(g_hWnd, L"라인 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}
	INFO tInfo = {};
	DWORD dwByte2 = 0;

	while (true)
	{
		ReadFile(hFile2, &tInfo, sizeof(INFO), &dwByte2, nullptr);
		if (0 == dwByte2)
		{
			break;
		}
		m_listVertex.emplace_back(CAbstractFactory<CVertex>::Create(tInfo.fX, tInfo.fY));
	}
	CloseHandle(hFile2);

	/********************************************************/

	HANDLE hFile3 = CreateFile(L"../Data/Block.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFile3)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	INFO tInfo2 = {};
	DWORD dwByte3 = 0;

	while (true)
	{
		ReadFile(hFile3, &tInfo2, sizeof(INFO), &dwByte3, nullptr);
		if (0 == dwByte3)
		{
			break;
		}
		m_listBlock.emplace_back(CAbstractFactory<CBlock>::Create(tInfo2.fX, tInfo2.fY));
	}
	CloseHandle(hFile3);

	/********************************************************/

	HANDLE hFile4 = CreateFile(L"../Data/VerticalBlock.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFile4)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	INFO tInfo3 = {};
	DWORD dwByte4 = 0;

	while (true)
	{
		ReadFile(hFile4, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		m_listVerticalBlock.emplace_back(CAbstractFactory<CVerticalBlocck>::Create(tInfo3.fX, tInfo3.fY));
	}
	CloseHandle(hFile4);

	/********************************************************/
	MessageBox(g_hWnd, L"라인 정보를 읽어왔습니다", L"로드 성공", MB_OK);
}
