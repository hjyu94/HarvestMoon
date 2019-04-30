#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"
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
}

bool CLineMgr::LineCollision(float fInX, float fInY, float * pOutY)
{
	if (m_listLine.empty())
		return false;

	CLine* pTarget = nullptr; 
	float fMinDistY = 9999.f;
	float fY_On_Target =0.f;

	for (auto& pLine : m_listLine)
	{
		if (fInX >= pLine->Get_LineInfo().tLeftPoint.fx &&
			fInX <= pLine->Get_LineInfo().tRightPoint.fx)
		{
			
			// �ش� x �� ���� line�� �ִ� ���
			// �ٷ� ���� line �� Ÿ��������.
			float x1 = pLine->Get_LineInfo().tLeftPoint.fx;
			float x2 = pLine->Get_LineInfo().tRightPoint.fx;
			float y1 = pLine->Get_LineInfo().tLeftPoint.fy;
			float y2 = pLine->Get_LineInfo().tRightPoint.fy;

			float fY_On_Line = ((y2 - y1) / (x2 - x1)) * (fInX - x1) + y1;
			float fDistY = fabs(fY_On_Line - fInY);

			if (fDistY < 20.f)
			{
				if (fMinDistY >= fDistY)
				{
					pTarget = pLine;
					fMinDistY = fY_On_Line - fInY;
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
	// ���⼭ 2, 5���� �ٲ�. ������ �б������ OPEN_EXISTING - �̹� �����ϴ� ������ ���ٴٶ�� �ǹ�. 

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"���� ������ �о���� ���߽��ϴ�", L"�ε� ����", MB_OK);
		return;
	}
	LINEINFO tInfo = {}; 
	DWORD dwByte = 0; 

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);
		if (0 == dwByte)
		{
			break;
		}
		m_listLine.emplace_back(new CLine(tInfo)); 
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"���� ������ �о�Խ��ϴ�", L"�ε� ����", MB_OK);
}
