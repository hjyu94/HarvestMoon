#include "stdafx.h"
#include "Item.h"

#include "Player.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

void CItem::Collision_Proc(CObj * pCounterObj)
{
	if (Is_Counter_One_Of(CPlayer))
	{
		if(m_eID != SAVE)
			m_bIsDead = true;
		
		else if (m_eID == SAVE)
		{
			m_eNextState = BLINK;
		}
	}
}

void CItem::Set_ID(ID eID)
{
	m_eID = eID;
	
	switch (eID)
	{
	case CItem::HP:
		m_pFrameKey = L"ITEM_HP";
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 40.f;
		break;

	case CItem::MP:
		m_pFrameKey = L"ITEM_MP";
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 40.f;
		break;

	case CItem::LIFE:
		m_pFrameKey = L"ITEM_LIFE";
		m_tInfo.fCX = 42.f;
		m_tInfo.fCY = 32.f;
		break;

	case CItem::SAVE:
		m_pFrameKey = L"ITEM_SAVE";
		m_tInfo.fCX = 66.f;
		m_tInfo.fCY = 62.f;
		break;
	}
}

void CItem::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_HP.bmp", L"ITEM_HP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_MP.bmp", L"ITEM_MP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_LIFE.bmp", L"ITEM_LIFE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_SAVE.bmp", L"ITEM_SAVE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_SAVE_BLINK.bmp", L"ITEM_SAVE_BLINK");

	m_eCurState = IDLE;
	m_eNextState = IDLE;
}

int CItem::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (m_eID == SAVE)
	{
		StateChange();
		FrameMove();
	}

	return 0;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC hDC)
{
	CObj::UpdateRect();

	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (m_eID == SAVE)
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
			m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			m_tInfo.fCX*m_tFrame.iFrameStart_X, 0, // 시작 위치 
			m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}
	else
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
			m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			0, 0, // 시작 위치 
			m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}
}

void CItem::Release()
{
}

void CItem::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		if (m_eID == SAVE && m_eCurState == BLINK)
		{
			m_eNextState = IDLE;
		}
		else
		{
			m_tFrame.iFrameStart_X = 0;
		}
	}
}

void CItem::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::IDLE:
			m_pFrameKey = L"ITEM_SAVE";
			m_tInfo.fCX = 66.f;
			m_tInfo.fCY = 62.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 1;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::BLINK:
			m_pFrameKey = L"ITEM_SAVE_BLINK";
			m_tInfo.fCX = 66.f;
			m_tInfo.fCY = 62.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 5;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}

		m_eCurState = m_eNextState;
	}
}
