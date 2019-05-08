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
	// ## ����
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

	// ## stage 1
	if (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENEID::SCENE_LINE_EDIT)
	{
		// ������ ��ư���� ���ý��� �߰�
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			CVertex* pVertex = new CVertex();
			pVertex->Initialize();
			pVertex->Set_Pos(float(pt.x), float(pt.y));
			m_listVertex.emplace_back(pVertex);
		}

		// ���ͷ� �ɼ� �ٲٱ�
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

		// 'B' ������ ���콺 ��ġ�� block �߰�
		if (CKeyMgr::Get_Instance()->KeyDown('B'))
		{
			CBlock* pBlock = CAbstractFactory<CBlock>::Create(float(pt.x), float(pt.y));
			m_listBlock.emplace_back(pBlock);
		}

		// 'V'�� Vertical Block �߰�
		if (CKeyMgr::Get_Instance()->KeyDown('V'))
		{
			CVerticalBlocck* pBlock = CAbstractFactory<CVerticalBlocck>::Create(float(pt.x), float(pt.y));
			pBlock->UpdateRect();
			m_listVerticalBlock.emplace_back(pBlock);
		}

		// 'Z'�� lizard �߰�
		if (CKeyMgr::Get_Instance()->KeyDown('Z'))
		{
			CLizard* pObj = CAbstractFactory<CLizard>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			m_listEnum[ID::LIZARD].emplace_back(pObj);
		}

		// 'F'�� Fly �߰�
		if (CKeyMgr::Get_Instance()->KeyDown('F'))
		{
			CFly* pObj = CAbstractFactory<CFly>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			m_listEnum[ID::FLY].emplace_back(pObj);
		}

		// 'H'�� hedgehog �߰�
		if (CKeyMgr::Get_Instance()->KeyDown('H'))
		{
			CHedgeHog* pObj = CAbstractFactory<CHedgeHog>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			m_listEnum[ID::HEDGEHOG].emplace_back(pObj);
		}

		// 'G'�� GRASS �߰�
		if (CKeyMgr::Get_Instance()->KeyDown('G'))
		{
			CGrass* pObj = CAbstractFactory<CGrass>::Create(float(pt.x), float(pt.y));
			pObj->UpdateRect();
			m_listEnum[ID::GRASS].emplace_back(pObj);
		}

		// F1~F4 �� Item �߰�
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

		//### �����
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
		// G�� �⸰ �߰�
		if (CKeyMgr::Get_Instance()->KeyUP('G'))
		{
			CGiraffe* pGiraffe = new CGiraffe();
			pGiraffe->Initialize();
			pGiraffe->Set_Pos(float(pt.x), float(pt.y));
			m_listStage2[S2_GIRAFFE].emplace_back(pGiraffe);
		}

		// 'M' ���� ������ �߰�
		if (CKeyMgr::Get_Instance()->KeyUP('M'))
		{
			CMonkey* pMonkey = new CMonkey();
			pMonkey->Initialize();
			pMonkey->Set_Pos(float(pt.x), float(pt.y));
			m_listStage2[S2_MONKEY].emplace_back(pMonkey);
		}

		// 'V'�� Vertical Block �߰�
		if (CKeyMgr::Get_Instance()->KeyDown('V'))
		{
			CVerticalBlocck* pBlock = CAbstractFactory<CVerticalBlocck>::Create(float(pt.x), float(pt.y));
			pBlock->UpdateRect();
			m_listVerticalBlock.emplace_back(pBlock);
		}

		// ���ͷ� �⸰ ���� �ٲٱ�
		// ���ͷ� ������ �� �ٲٱ�
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

		// ��Ŭ������ ������ ���� �ٲٱ�
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

		// �⸰ ���⿡ ���� �ٸ��� �׷������� UPDATE ����
		for (int i = 0; i < STAGE2::S2_END; ++i)
		{
			for (auto& pObj : m_listStage2[i])
			{
				pObj->Update();
			}
		}

		// �����
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

	
	// ## ����

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
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"���� ���� ����", MB_OK);
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
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertex ���� ����", MB_OK);
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
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"��� ���� ����", MB_OK);
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
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
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
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}

	cout << m_listVerticalBlock.size() << endl;

	for (auto& pObj : m_listEnum[ID::LIZARD])
	{
		WriteFile(hFileLizard, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileLizard);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);

	/********************************************************/

	HANDLE hFileFly = CreateFile(
		L"../Data/Fly.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileFly)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}

	for (auto& pObj : m_listEnum[ID::FLY])
	{
		WriteFile(hFileFly, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileFly);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);

	/********************************************************/

	HANDLE hFileHedgehog = CreateFile(
		L"../Data/Hedgehog.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileHedgehog)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::HEDGEHOG])
	{
		WriteFile(hFileHedgehog, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileHedgehog);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);

	/********************************************************/

	HANDLE hFileGrass = CreateFile(
		L"../Data/Grass.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileGrass)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::GRASS])
	{
		WriteFile(hFileGrass, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileGrass);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);

	/********************************************************/

	HANDLE hFileItem_HP = CreateFile(
		L"../Data/Item_HP.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileItem_HP)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::ITEM_HP])
	{
		WriteFile(hFileItem_HP, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileItem_HP);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);
	/********************************************************/

	HANDLE hFileItem_MP = CreateFile(
		L"../Data/Item_MP.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileItem_MP)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::ITEM_MP])
	{
		WriteFile(hFileItem_MP, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileItem_MP);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);
	/********************************************************/

	HANDLE hFileItem_LIFE = CreateFile(
		L"../Data/Item_LIFE.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileItem_LIFE)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::ITEM_LIFE])
	{
		WriteFile(hFileItem_LIFE, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileItem_LIFE);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);
	/********************************************************/

	HANDLE hFileItem_SAVE = CreateFile(
		L"../Data/Item_SAVE.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hFileItem_SAVE)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}


	for (auto& pObj : m_listEnum[ID::ITEM_SAVE])
	{
		WriteFile(hFileItem_SAVE, &pObj->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFileItem_SAVE);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);
}

void CEditorLineMgr::SaveData_for_stage_2()
{
	// ���� ����
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

	// �⸰ ����
	HANDLE hGiraffeFile = CreateFile(
		L"../Data/Stage2/Giraffe.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hGiraffeFile)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"�⸰ ���� ����", MB_OK);
	}
	
	for (auto& pGiraffe : m_listStage2[S2_GIRAFFE])
	{
		WriteFile(hLineFile, &pGiraffe->Get_Info(), sizeof(LINEINFO), &dwByte, nullptr);
		WriteFile(hLineFile, &pGiraffe->Get_IsRightDir(), sizeof(bool), &dwByte, nullptr);
	}
	CloseHandle(hGiraffeFile);

	// vertical block ����

	HANDLE hVerticalBlockFile = CreateFile(
		L"../Data/Stage2/VerticalBlock.dat"
		, GENERIC_WRITE, 0, NULL
		, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
	);

	if (INVALID_HANDLE_VALUE == hVerticalBlockFile)
	{
		MessageBox(g_hWnd, L"�������� ���߽��ϴ�", L"Vertical ��� ���� ����", MB_OK);
	}

	for (auto& pVerticalBlock : m_listVerticalBlock)
	{
		WriteFile(hVerticalBlockFile, &pVerticalBlock->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hVerticalBlockFile);

	MessageBox(g_hWnd, L"�����߽��ϴ�", L"���� ����", MB_OK);
}

void CEditorLineMgr::LoadData()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	// ���⼭ 2, 5���� �ٲ�. ������ �б������ OPEN_EXISTING - �̹� �����ϴ� ������ ���ٴٶ�� �ǹ�. 

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"���� ������ �о���� ���߽��ϴ�", L"�ε� ����", MB_OK);
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
	// ���⼭ 2, 5���� �ٲ�. ������ �б������ OPEN_EXISTING - �̹� �����ϴ� ������ ���ٴٶ�� �ǹ�. 

	if (INVALID_HANDLE_VALUE == hFile2)
	{
		MessageBox(g_hWnd, L"���� ������ �о���� ���߽��ϴ�", L"�ε� ����", MB_OK);
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
	// ���⼭ 2, 5���� �ٲ�. ������ �б������ OPEN_EXISTING - �̹� �����ϴ� ������ ���ٴٶ�� �ǹ�. 

	if (INVALID_HANDLE_VALUE == hFile3)
	{
		MessageBox(g_hWnd, L"block ������ �о���� ���߽��ϴ�", L"�ε� ����", MB_OK);
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
	// ���⼭ 2, 5���� �ٲ�. ������ �б������ OPEN_EXISTING - �̹� �����ϴ� ������ ���ٴٶ�� �ǹ�. 

	if (INVALID_HANDLE_VALUE == hFile4)
	{
		MessageBox(g_hWnd, L"block ������ �о���� ���߽��ϴ�", L"�ε� ����", MB_OK);
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
	MessageBox(g_hWnd, L"���� ������ �о�Խ��ϴ�", L"�ε� ����", MB_OK);
}

void CEditorLineMgr::LoadData_for_stage_2()
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

