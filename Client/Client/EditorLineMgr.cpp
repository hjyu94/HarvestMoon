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
#include "Grass.h"
#include "SceneMgr.h"
#include "Giraffe.h"
#include "Monkey.h"

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

	if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT)
	{
		LoadData();
	}
	else if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT_2)
	{
		LoadData_for_stage_2();
	}
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

	// ## stage 2
	for (int i = 0; i < STAGE2::S2_END; ++i)
	{
		for (auto& pObj : m_listStage2[i])
		{
			pObj->Render(hDC);
		}
	}
}

void CEditorLineMgr::Update()
{
	// ## 공용
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

	// ## stage 1
	if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT)
	{
		// 오른쪽 버튼으로 벌택스를 추가
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			CVertex* pVertex = new CVertex();
			pVertex->Initialize();
			pVertex->Set_Pos(float(pt.x), float(pt.y));
			m_listVertex.emplace_back(pVertex);
		}

		// 엔터로 옵션 바꾸기
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
		{
			for (auto& pVertex : m_listVertex)
			{
				if (PtInRect(&pVertex->Get_Rect(), pt))
				{
					if (pVertex->Get_Dir() == CVertex::DIR::L)
					{
						pVertex->Set_Dir(CVertex::R);
					}
					else
					{
						pVertex->Set_Dir(CVertex::L);
					}
				}
			}
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

		// 'Z'로 lizard 추가
		if (CKeyMgr::Get_Instance()->KeyDown('Z'))
		{
			CLizard* pObj = CAbstractFactory<CLizard>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			m_listEnum[ID::LIZARD].emplace_back(pObj);
		}

		// 'F'로 Fly 추가
		if (CKeyMgr::Get_Instance()->KeyDown('F'))
		{
			CFly* pObj = CAbstractFactory<CFly>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			m_listEnum[ID::FLY].emplace_back(pObj);
		}

		// 'H'로 hedgehog 추가
		if (CKeyMgr::Get_Instance()->KeyDown('H'))
		{
			CHedgeHog* pObj = CAbstractFactory<CHedgeHog>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			m_listEnum[ID::HEDGEHOG].emplace_back(pObj);
		}

		// 'G'로 GRASS 추가
		if (CKeyMgr::Get_Instance()->KeyDown('G'))
		{
			CGrass* pObj = CAbstractFactory<CGrass>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			m_listEnum[ID::GRASS].emplace_back(pObj);
		}

		// F1~F4 로 Item 추가
		if (CKeyMgr::Get_Instance()->KeyDown(VK_F1))
		{
			CItem* pObj = CAbstractFactory<CItem>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			pObj->Set_ID(CItem::ID::HP);
			m_listEnum[ID::ITEM_HP].emplace_back(pObj);
		}

		if (CKeyMgr::Get_Instance()->KeyDown(VK_F2))
		{
			CItem* pObj = CAbstractFactory<CItem>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			pObj->Set_ID(CItem::ID::MP);
			m_listEnum[ID::ITEM_MP].emplace_back(pObj);
		}

		if (CKeyMgr::Get_Instance()->KeyDown(VK_F3))
		{
			CItem* pObj = CAbstractFactory<CItem>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			pObj->Set_ID(CItem::ID::LIFE);
			m_listEnum[ID::ITEM_LIFE].emplace_back(pObj);
		}

		if (CKeyMgr::Get_Instance()->KeyDown(VK_F4))
		{
			CItem* pObj = CAbstractFactory<CItem>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			pObj->Set_ID(CItem::ID::SAVE);
			m_listEnum[ID::ITEM_SAVE].emplace_back(pObj);
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

			for (int i = 0; i < ID::END; ++i)
			{
				for (auto& iter = m_listEnum[i].begin()
					; iter != m_listEnum[i].end()
					; )
				{
					if (PtInRect(&(*iter)->Get_Rect(), pt))
					{
						delete *iter;
						*iter = nullptr;
						iter = m_listEnum[i].erase(iter);
					}
					else
						iter++;
				}
			}
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
	
	// ## stage 2
	else if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT_2)
	{
		// G로 기린 추가
		if (CKeyMgr::Get_Instance()->KeyUP('G'))
		{
			CGiraffe* pGiraffe = new CGiraffe();
			pGiraffe->Initialize();
			pGiraffe->Set_Pos(float(pt.x), float(pt.y));
			m_listStage2[S2_GIRAFFE].emplace_back(pGiraffe);
		}

		// 'M' 으로 원숭이 추가
		if (CKeyMgr::Get_Instance()->KeyUP('M'))
		{
			CMonkey* pMonkey = new CMonkey();
			pMonkey->Initialize();
			pMonkey->Set_Pos(float(pt.x), float(pt.y));
			m_listStage2[S2_MONKEY].emplace_back(pMonkey);
		}

		// 'V'로 Vertical Block 추가
		if (CKeyMgr::Get_Instance()->KeyDown('V'))
		{
			CVerticalBlocck* pBlock = CAbstractFactory<CVerticalBlocck>::Create(float(pt.x), float(pt.y));
			pBlock->UpdateRect();
			m_listVerticalBlock.emplace_back(pBlock);
		}

		// 엔터로 기린 방향 바꾸기
		// 엔터로 원숭이 색 바꾸기
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
		{
			for (auto& pGiraffe : m_listStage2[S2_GIRAFFE])
			{
				if (PtInRect(&pGiraffe->Get_Rect(), pt))
				{
					pGiraffe->Set_Dir(!pGiraffe->Get_IsRightDir());
				}
			}

			for (auto& pMonkey : m_listStage2[S2_MONKEY])
			{
				if (PtInRect(&pMonkey->Get_Rect(), pt))
				{
					static_cast<CMonkey*>(pMonkey)->Change_Color();
				}
			}
		}

		// 우클릭으로 원숭이 방향 바꾸기
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			for (auto& pMonkey : m_listStage2[S2_MONKEY])
			{
				if (PtInRect(&pMonkey->Get_Rect(), pt))
				{
					static_cast<CMonkey*>(pMonkey)->Change_Dir();
				}
			}
		}

		// 기린 방향에 따라 다르게 그려지도록 UPDATE 수행
		for (int i = 0; i < STAGE2::S2_END; ++i)
		{
			for (auto& pObj : m_listStage2[i])
			{
				pObj->Update();
			}
		}

		// 지우기
		if (CKeyMgr::Get_Instance()->KeyDown(VK_DELETE))
		{
			for (int i = 0; i < STAGE2::S2_END; ++i)
			{
				for (auto& iter = m_listStage2[i].begin()
					; iter != m_listStage2[i].end()
					; )
				{
					if (PtInRect(&(*iter)->Get_Rect(), pt))
					{
						delete *iter;
						*iter = nullptr;
						iter = m_listStage2[i].erase(iter);
					}
					else
						iter++;
				}
			}
		}
	}

	
	// ## 공용

	if (CKeyMgr::Get_Instance()->KeyDown('R'))
	{
		Release();
	}

	if (CKeyMgr::Get_Instance()->KeyDown('L'))
	{
		if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT)
		{
			LoadData();
		}
		else if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT_2)
		{
			LoadData_for_stage_2();
		}
	}

	if (CKeyMgr::Get_Instance()->KeyDown('S'))
	{
		if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT)
		{
			SaveData();
		}
		else if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT_2)
		{
			SaveData_for_stage_2();
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

	// ## STAGE 2
	for (int i = 0; i < STAGE2::S2_END; ++i)
	{
		for (auto& iter = m_listStage2[i].begin()
			; iter != m_listStage2[i].end()
			; )
		{
			if (*iter)
			{
				delete *iter;
				*iter = nullptr;
				iter = m_listStage2[i].erase(iter);
			}
		}
		m_listStage2[i].clear();
	}
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
		WriteFile(hFile2, &pVertex->Get_Dir(), sizeof(CVertex::DIR), &dwByte2, nullptr);
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

	for (auto& pVerticalBlock : m_listVerticalBlock)
	{
		WriteFile(hFile3, &pVerticalBlock->Get_Info(), sizeof(INFO), &dwByte4, nullptr);
	}
	CloseHandle(hFile4);
	
	/********************************************************/
	
	HANDLE hFileLizard = CreateFile(
		L"../Data/Lizard.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileLizard)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}

	cout << m_listVerticalBlock.size() << endl;

	for (auto& pObj : m_listEnum[ID::LIZARD])
	{
		WriteFile(hFileLizard, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileLizard);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);

	/********************************************************/

	HANDLE hFileFly = CreateFile(
		L"../Data/Fly.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileFly)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}

	for (auto& pObj : m_listEnum[ID::FLY])
	{
		WriteFile(hFileFly, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileFly);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);

	/********************************************************/

	HANDLE hFileHedgehog = CreateFile(
		L"../Data/Hedgehog.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileHedgehog)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::HEDGEHOG])
	{
		WriteFile(hFileHedgehog, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileHedgehog);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);

	/********************************************************/

	HANDLE hFileGrass = CreateFile(
		L"../Data/Grass.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileGrass)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::GRASS])
	{
		WriteFile(hFileGrass, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileGrass);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);

	/********************************************************/

	HANDLE hFileItem_HP = CreateFile(
		L"../Data/Item_HP.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileItem_HP)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::ITEM_HP])
	{
		WriteFile(hFileItem_HP, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileItem_HP);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);
	/********************************************************/

	HANDLE hFileItem_MP = CreateFile(
		L"../Data/Item_MP.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileItem_MP)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::ITEM_MP])
	{
		WriteFile(hFileItem_MP, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileItem_MP);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);
	/********************************************************/

	HANDLE hFileItem_LIFE = CreateFile(
		L"../Data/Item_LIFE.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileItem_LIFE)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::ITEM_LIFE])
	{
		WriteFile(hFileItem_LIFE, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileItem_LIFE);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);
	/********************************************************/

	HANDLE hFileItem_SAVE = CreateFile(
		L"../Data/Item_SAVE.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileItem_SAVE)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::ITEM_SAVE])
	{
		WriteFile(hFileItem_SAVE, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileItem_SAVE);

	MessageBox(g_hWnd, L"저장했습니다", L"저장 성공", MB_OK);
}

void CEditorLineMgr::SaveData_for_stage_2()
{
	// 라인 저장
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

	// 기린 저장
	HANDLE hGiraffeFile = CreateFile(
		L"../Data/Stage2/Giraffe.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hGiraffeFile)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"기린 저장 실패", MB_OK);
	}
	
	for (auto& pGiraffe : m_listStage2[S2_GIRAFFE])
	{
		WriteFile(hLineFile, &pGiraffe->Get_Info(), sizeof(LINEINFO), &dwByte, nullptr);
		WriteFile(hLineFile, &pGiraffe->Get_IsRightDir(), sizeof(bool), &dwByte, nullptr);
	}
	CloseHandle(hGiraffeFile);

	// vertical block 저장

	HANDLE hVerticalBlockFile = CreateFile(
		L"../Data/Stage2/VerticalBlock.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hVerticalBlockFile)
	{
		MessageBox(g_hWnd, L"저장하지 못했습니다", L"Vertical 블록 저장 실패", MB_OK);
	}

	for (auto& pVerticalBlock : m_listVerticalBlock)
	{
		WriteFile(hVerticalBlockFile, &pVerticalBlock->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hVerticalBlockFile);

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

void CEditorLineMgr::LoadData_for_stage_2()
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

