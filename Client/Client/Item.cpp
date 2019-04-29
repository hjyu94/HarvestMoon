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
		m_bIsDead = true;
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
		m_tInfo.fCX = 67.f;
		m_tInfo.fCY = 64.f;
		break;
	}
}

void CItem::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_HP.bmp", L"ITEM_HP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_MP.bmp", L"ITEM_MP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_LIFE.bmp", L"ITEM_LIFE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Item/ITEM_SAVE.bmp", L"ITEM_SAVE");
}

int CItem::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	return 0;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC hDC)
{
	CObj::UpdateRect();

	//int iScrollX = CScrollMgr::Get_ScrollX();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left/* + iScrollX*/, m_tRect.top, //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		0, 0, // 시작 위치 
		m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);
}

void CItem::Release()
{
}
