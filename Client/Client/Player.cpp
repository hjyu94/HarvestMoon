#include "stdafx.h"
#include "Player.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BitmapMgr.h"

CPlayer::CPlayer()
	: m_pFrameKey(L"")
	, m_eNextState(IDLE)
	, m_eCurState(IDLE)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	m_tInfo.fCX = 200.f; 
	m_tInfo.fCY = 200.f; 

	m_tInfo.fX = 400.f; 
	m_tInfo.fY = 300.f; 
	m_fSpeed = 5.f;
	m_fAngle = 45.f; 

	m_bIsJump = false; 
	m_fJumpAccel = 0.f; 
	m_fJumpPower = 15.f; 
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	m_pFrameKey = L"Player_DOWN";

	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount(); 
	m_tFrame.iFrameStart = 0; 
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0; 
}

int CPlayer::Update()
{
	KeyCheck();
	IsJumping();
	SceneChange();
	CObj::FrameMove();
	return 0;
}

void CPlayer::LateUpdate()
{
}

void CPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();
	int iScrollX = CScrollMgr::Get_ScrollX();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, // ���� ������� DC
		m_tRect.left + iScrollX, m_tRect.top, //��µ� ��ġ�� xy ��ǥ 
		m_tInfo.fCX, m_tInfo.fCY, // ����� ��Ʈ���� ���μ��� ������. 
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart, 
		m_tInfo.fCY* m_tFrame.iFrameScene, // ���� ��ġ 
		m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
		RGB(0, 0, 0)
	);
}

void CPlayer::Release()
{
}

void CPlayer::IsJumping()
{
	float fy = 0.f; 
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, &fy);

	// ����ڰ� ������ ��������!
	if (m_bIsJump)
	{
		// �������� ���� ��� 
		// y= �� * sin@(1�̶� ����) * �ð� - 1/2 * �߷� * �ð� * �ð�;
		m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f ;

		m_fJumpAccel += 0.21f;

		if (bIsColl && m_tInfo.fY > fy)
		{
			m_bIsJump = false;
			m_fJumpAccel = 0.f;
			m_tInfo.fY = fy;
		}
// 		system("cls");
// 		cout << m_tInfo.fY << endl; 
// 		int i = 0; 
	}
	else if (bIsColl)
		m_tInfo.fY = fy;


}

void CPlayer::KeyCheck()
{
		if (GetAsyncKeyState(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			m_pFrameKey = L"Player_LEFT";
			m_eNextState = WALK;
			CScrollMgr::Set_ScrollX(m_fSpeed);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			m_pFrameKey = L"Player_RIGHT";
			m_eNextState = WALK;
			CScrollMgr::Set_ScrollX(-m_fSpeed);
		}

	if (CKeyMgr::Get_Instance()->KeyUP(VK_SPACE))
		m_bIsJump = true;

}
void CPlayer::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CPlayer::IDLE:
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			break;
		case CPlayer::WALK:
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 1;
			break;
		case CPlayer::ATT:
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			break;
		case CPlayer::HIT:
			break;
		case CPlayer::DIE:
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}