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
	m_hMemDC = CreateCompatibleDC(hDC); // 인자를 넘겨주면 현재 출력하고 있는 DC와 호환이 되는 메모리 DC를 할당해주는 함수. 
	ReleaseDC(g_hWnd, hDC);
	
	m_hBitmap = (HBITMAP)LoadImage(NULL,//프로그램 인스턴스 핸들. 우리는 파일을 대상으로 얻어올것이기때문에 딱히 필요 없다. 
		pPath,// 파일의 경로 
		IMAGE_BITMAP,//비트맵인지 커서인지 아이콘인지
		0,0,//이건 x,y 그림의 크기인데 우리가 넣어줄 필요 없다. 파일에 다 데이타가 있으니. 0넣어주면 알아서 사이즈 받아옴. 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION// 그림을 읽어오는 방식 
	);
	
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
