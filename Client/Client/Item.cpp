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

	GdiTransparentBlt(hDC, // ���� ������� DC
		m_tRect.left/* + iScrollX*/, m_tRect.top, //��µ� ��ġ�� xy ��ǥ 
		m_tInfo.fCX, m_tInfo.fCY, // ����� ��Ʈ���� ���μ��� ������. 
		hMemDC,
		0, 0, // ���� ��ġ 
		m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
		RGB(255, 255, 255)
	);
}

void CItem::Release()
{
}
