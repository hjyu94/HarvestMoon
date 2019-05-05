#include "stdafx.h"
#include "LineMgr.h"
#include "AbstractFactory.h"

#include "Line.h"
#include "Vertex.h"
#include "Block.h"
#include "VerticalBlocck.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Fly.h"
#include "Lizard.h"
#include "HedgeHog.h"
#include "Item.h"
#include "Obj.h"
#include "Grass.h"

CLineMgr* CLineMgr::m_pInstance = nullptr; 

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release(); 
}

void CLineMgr::Initialize()
{
	LoadData();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_listLine)
		pLine->Render(hDC);


	for (auto& pVertex : m_listVertex)
	{
		pVertex->Update();
		pVertex->Render(hDC);
	}
}

void CLineMgr::Release()
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

	for (auto& pVertex : m_listVertex)
	{
		if (pVertex)
		{
			delete pVertex;
			pVertex = nullptr;
		}
	}
	m_listVertex.clear();
}

bool CLineMgr::LineCollision(float fInX, float fInY, float * pOutY)
{
	if (m_listLine.empty())
		return false;

	CLine* pTarget = nullptr; 
	float fMinDistY = 9999.f; // 맵의 Height 보다 커야 함.
	float fY_On_Target = 0.f;

	//float fPlayerCY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fCY;

	for (auto& pLine : m_listLine)
	{
		if (fInX >= pLine->Get_LineInfo().tLeftPoint.fx &&
			fInX <= pLine->Get_LineInfo().tRightPoint.fx)
		{
			
			// 해당 x 에 여러 line이 있는 경우
			// 바로 밑의 line 을 타겟팅하자.
			float x1 = pLine->Get_LineInfo().tLeftPoint.fx;
			float x2 = pLine->Get_LineInfo().tRightPoint.fx;
			float y1 = pLine->Get_LineInfo().tLeftPoint.fy;
			float y2 = pLine->Get_LineInfo().tRightPoint.fy;

			
			float fY_On_Line = ((y2 - y1) / (x2 - x1)) * (fInX - x1) + y1/* - fPlayerCY/2*/;
			float fDistY = fabs(fY_On_Line - fInY);

			if (fDistY < 40.f)
			{
			//if(fY_On_Line >= fInY)
				if (fMinDistY >= fDistY)
				{
					pTarget = pLine;
					fMinDistY = fDistY;
					fY_On_Target = fY_On_Line;
				}
			}
		}
	}

	if (nullptr == pTarget)
		return false;

	*pOutY = fY_On_Target;
	return true; 
}

void CLineMgr::LoadData()
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
	CVertex::DIR eDir;
	DWORD dwByte2 = 0;

	while (true)
	{
		ReadFile(hFile2, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile2, &eDir, sizeof(CVertex::DIR), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}
		CVertex* pVertex = CAbstractFactory<CVertex>::Create(tInfo.fX, tInfo.fY);
		pVertex->Set_Dir(eDir);
		CObjMgr::Get_Instance()->AddObject(OBJID::MAP, pVertex);
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
		CObjMgr::Get_Instance()->AddObject(OBJID::BLOCK, CAbstractFactory<CBlock>::Create(tInfo2.fX, tInfo2.fY));
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
		CObjMgr::Get_Instance()->AddObject(OBJID::VERTICAL_BLOCK, CAbstractFactory<CVerticalBlocck>::Create(tInfo3.fX, tInfo3.fY));
	}
	CloseHandle(hFile4);

	/********************************************************/

	HANDLE hFileLIZARD = CreateFile(L"../Data/Lizard.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFileLIZARD)
	{
		MessageBox(g_hWnd, L"LIZARD 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	while (true)
	{
		ReadFile(hFileLIZARD, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CLizard>::Create(tInfo3.fX, tInfo3.fY));
	}
	CloseHandle(hFileLIZARD);
	/********************************************************/

	HANDLE hFileFLY = CreateFile(L"../Data/Fly.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFileFLY)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	while (true)
	{
		ReadFile(hFileFLY, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CFly>::Create(tInfo3.fX, tInfo3.fY));
	}
	CloseHandle(hFileFLY);
	/********************************************************/

	HANDLE hFileHedgehog = CreateFile(L"../Data/Hedgehog.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFileHedgehog)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	while (true)
	{
		ReadFile(hFileHedgehog, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		CObjMgr::Get_Instance()->AddObject(OBJID::MONSTER, CAbstractFactory<CHedgeHog>::Create(tInfo3.fX, tInfo3.fY));
	}
	CloseHandle(hFileHedgehog);
	/********************************************************/

	HANDLE hFileGrass = CreateFile(L"../Data/Grass.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFileGrass)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	while (true)
	{
		ReadFile(hFileGrass, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		CObjMgr::Get_Instance()->AddObject(OBJID::ETC, CAbstractFactory<CGrass>::Create(tInfo3.fX, tInfo3.fY));
	}
	CloseHandle(hFileGrass);
	/********************************************************/

	HANDLE hFileItem_HP = CreateFile(L"../Data/Item_HP.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFileItem_HP)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	while (true)
	{
		ReadFile(hFileItem_HP, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		CItem* pItem = CAbstractFactory<CItem>::Create(tInfo3.fX, tInfo3.fY);
		pItem->Set_ID(CItem::HP);
		CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);
	}
	CloseHandle(hFileItem_HP);
	/********************************************************/
	HANDLE hFileItem_MP = CreateFile(L"../Data/Item_MP.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFileItem_MP)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	while (true)
	{
		ReadFile(hFileItem_MP, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		CItem* pItem = CAbstractFactory<CItem>::Create(tInfo3.fX, tInfo3.fY);
		pItem->Set_ID(CItem::MP);
		CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);
	}
	CloseHandle(hFileItem_MP);
	/********************************************************/
	HANDLE hFileItem_LIFE = CreateFile(L"../Data/Item_LIFE.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFileItem_LIFE)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	while (true)
	{
		ReadFile(hFileItem_LIFE, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		CItem* pItem = CAbstractFactory<CItem>::Create(tInfo3.fX, tInfo3.fY);
		pItem->Set_ID(CItem::LIFE);
		CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);
	}
	CloseHandle(hFileItem_LIFE);
	/********************************************************/

	HANDLE hFileItem_SAVE = CreateFile(L"../Data/Item_SAVE.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// 여기서 2, 5번만 바뀜. 파일을 읽기용으로 OPEN_EXISTING - 이미 존재하는 파일을 열겟다라는 의미. 

	if (INVALID_HANDLE_VALUE == hFileItem_SAVE)
	{
		MessageBox(g_hWnd, L"block 정보를 읽어오지 못했습니다", L"로드 실패", MB_OK);
		return;
	}

	while (true)
	{
		ReadFile(hFileItem_SAVE, &tInfo3, sizeof(INFO), &dwByte4, nullptr);
		if (0 == dwByte4)
		{
			break;
		}
		CItem* pItem = CAbstractFactory<CItem>::Create(tInfo3.fX, tInfo3.fY);
		pItem->Set_ID(CItem::SAVE);
		CObjMgr::Get_Instance()->AddObject(OBJID::ITEM, pItem);
	}
	CloseHandle(hFileItem_SAVE);

	/********************************************************/
	cout << CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::VERTICAL_BLOCK).size() << endl;
	cout << CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::BLOCK).size() << endl;
	cout << CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::MAP).size() << endl;
	cout << CLineMgr::Get_Instance()->m_listLine.size() << endl;
	/********************************************************/
	MessageBox(g_hWnd, L"라인 정보를 읽어왔습니다", L"로드 성공", MB_OK);
}
