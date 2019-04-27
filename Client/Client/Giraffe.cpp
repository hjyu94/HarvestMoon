#include "stdafx.h"
#include "Giraffe.h"


CGiraffe::CGiraffe()
	: m_pFrameKey(L"")
	, m_eNextState(IDLE)
	, m_eCurState(IDLE)
{
}


CGiraffe::~CGiraffe()
{
}

void CGiraffe::Initialize()
{
	m_tInfo.fCX = 126.f;
	m_tInfo.fCY = 226.f;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_fSpeed = 5.f;
	m_fAngle = 45.f;

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/GIRAFFE_IDLE.bmp", L"GIRAFFE_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/GIRAFFE_NECK.bmp", L"GIRAFFE_NECK");

	m_pFrameKey = L"GIRAFFE_IDLE";

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 4;
	m_tFrame.iFrameStart_Y = 0;
}

int CGiraffe::Update()
{
	KeyCheck();
	SceneChange();
	CObj::FrameMove();
	return 0;
}

void CGiraffe::LateUpdate()
{
}

void CGiraffe::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left + iScrollX, m_tRect.top, //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart_X,
		m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
		m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);
}

void CGiraffe::Release()
{
}

void CGiraffe::KeyCheck()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_LEFT))
	{
		m_pFrameKey = L"GIRAFFE_NECK";
		m_eNextState = NECK;
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RIGHT))
	{
		m_pFrameKey = L"GIRAFFE_IDLE";
		m_eNextState = IDLE;
	}
}

void CGiraffe::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CGiraffe::IDLE:
			m_tInfo.fCX = 126.f;
			m_tInfo.fCY = 226.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 4;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CGiraffe::NECK:
			m_tInfo.fCX = 117.f;
			m_tInfo.fCY = 252.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 3;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}

		m_eCurState = m_eNextState;
	}
}
