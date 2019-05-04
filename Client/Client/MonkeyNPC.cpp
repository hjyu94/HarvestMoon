#include "stdafx.h"
#include "MonkeyNPC.h"


CMonkeyNPC::CMonkeyNPC()
{
}


CMonkeyNPC::~CMonkeyNPC()
{
}

void CMonkeyNPC::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/NPC/MONKEY_YES.bmp", L"MONKEY_YES");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/NPC/MONKEY_NO.bmp", L"MONKEY_NO");

	m_pFrameKey = L"MONKEY_YES";
	m_tInfo.fCX = 110.f;
	m_tInfo.fCY = 190.f;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 7;
	m_tFrame.iFrameStart_Y = 0;

	m_eCurState = YES;
	m_eNextState = YES;
}

int CMonkeyNPC::Update()
{
	CObj::UpdateRect();
	FrameMove();
	StateChange();
	return 0;
}

void CMonkeyNPC::LateUpdate()
{
}

void CMonkeyNPC::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, // ���� ������� DC
		m_tRect.left, m_tRect.top, //��µ� ��ġ�� xy ��ǥ 
		m_tInfo.fCX, m_tInfo.fCY, // ����� ��Ʈ���� ���μ��� ������. 
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart_X,
		m_tInfo.fCY* m_tFrame.iFrameStart_Y, // ���� ��ġ 
		m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
		RGB(0, 0, 0)
	);
}

void CMonkeyNPC::Release()
{
}

void CMonkeyNPC::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::YES:
			m_pFrameKey = L"MONKEY_YES";
			m_tInfo.fCX = 110.f;
			m_tInfo.fCY = 190.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 7;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::NO:
			m_pFrameKey = L"MONKEY_NO";
			m_tInfo.fCX = 110.f;
			m_tInfo.fCY = 190.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 13;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}

		m_eCurState = m_eNextState;
	}
}

void CMonkeyNPC::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		--m_tFrame.iFrameStart_X;
	}
}
