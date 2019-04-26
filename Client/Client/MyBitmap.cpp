#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::LoadBmp(const TCHAR * pPath)
{
	HDC hDC = GetDC(g_hWnd);//
	m_hMemDC = CreateCompatibleDC(hDC); // ���ڸ� �Ѱ��ָ� ���� ����ϰ� �ִ� DC�� ȣȯ�� �Ǵ� �޸� DC�� �Ҵ����ִ� �Լ�. 
	ReleaseDC(g_hWnd, hDC);
	
	m_hBitmap = (HBITMAP)LoadImage(NULL,//���α׷� �ν��Ͻ� �ڵ�. �츮�� ������ ������� ���ð��̱⶧���� ���� �ʿ� ����. 
		pPath,// ������ ��� 
		IMAGE_BITMAP,//��Ʈ������ Ŀ������ ����������
		0,0,//�̰� x,y �׸��� ũ���ε� �츮�� �־��� �ʿ� ����. ���Ͽ� �� ����Ÿ�� ������. 0�־��ָ� �˾Ƽ� ������ �޾ƿ�. 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION// �׸��� �о���� ��� 
	);
	
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
