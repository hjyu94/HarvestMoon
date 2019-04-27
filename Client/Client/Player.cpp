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
	m_tInfo.fCX = 80.f; 
	m_tInfo.fCY = 75.f; 

	m_tInfo.fX = 400.f; 
	m_tInfo.fY = 300.f; 
	m_fSpeed = 5.f;
	m_fAngle = 45.f; 

	m_bIsJump = false; 
	m_fJumpAccel = 0.f; 
	m_fJumpPower = 15.f; 
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_IDLE.bmp", L"PLAYER_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_IDLE_LEFT.bmp", L"PLAYER_IDLE_LEFT");
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_ROARING.bmp", L"PLAYER_ROARING");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_ROARING_LEFT.bmp", L"PLAYER_ROARING_LEFT");
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_DOWN.bmp", L"PLAYER_DOWN");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_DOWN_LEFT.bmp", L"PLAYER_DOWN_LEFT");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_UP.bmp", L"PLAYER_UP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_UP_LEFT.bmp", L"PLAYER_UP_LEFT");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_RUNNING.bmp", L"PLAYER_RUNNING");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_RUNNING_LEFT.bmp", L"PLAYER_RUNNING_LEFT");
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_ROLLING.bmp", L"PLAYER_ROLLING");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_ROLLING_LEFT.bmp", L"PLAYER_ROLLING_LEFT");

	m_bIsRightDir = true;

	m_pFrameKey = L"PLAYER_IDLE";
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount(); 
	m_tFrame.iFrameStart_X = 0; 
	m_tFrame.iFrameEnd_X = 9;
	m_tFrame.iFrameStart_Y = 0; 
}

int CPlayer::Update()
{
	/*if (m_bMotionEnd)
	{
		m_pFrameKey = L"PLAYER_IDLE";
		m_eNextState = IDLE;
	}*/

	KeyCheck();
	IsJumping();
	SceneChange();
	
	FrameMove();
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
		m_tInfo.fCX * m_tFrame.iFrameStart_X, 
		m_tInfo.fCY* m_tFrame.iFrameStart_Y, // ���� ��ġ 
		m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
		RGB(255, 255, 255)
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
		m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - 9.8 * m_fJumpAccel * m_fJumpAccel * 0.5f ;

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
	if (!m_bIsRolling)
	{
		if (CKeyMgr::Get_Instance()->KeyUP(VK_LEFT))
		{
			m_pFrameKey = L"PLAYER_IDLE_LEFT";
			m_eNextState = IDLE_LEFT;
			m_bIsRightDir = false;
		}

		if (CKeyMgr::Get_Instance()->KeyUP(VK_RIGHT))
		{
			m_pFrameKey = L"PLAYER_IDLE";
			m_eNextState = IDLE;
			m_bIsRightDir = true;
		}

		if (CKeyMgr::Get_Instance()->KeyDown(VK_LEFT))
		{
			m_pFrameKey = L"PLAYER_RUNNING_LEFT";
			m_eNextState = RUNNING_LEFT;
			m_bIsRightDir = false;

			if (CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
			{
				m_pFrameKey = L"PLAYER_ROLLING_LEFT";
				m_eNextState = ROLLING_LEFT;
				m_bIsRightDir = false;
				m_bIsRolling = true;
			}
		}
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RIGHT))
		{
			m_pFrameKey = L"PLAYER_RUNNING";
			m_eNextState = RUNNING;
			m_bIsRightDir = true;
		}

		/*if (m_eCurState == RUNNING)
		{
			if (CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
			{
				m_pFrameKey = L"PLAYER_ROLLING";
				m_eNextState = ROLLING;
				m_bIsRightDir = true;
				m_bIsRolling = true;
			}
		}

		if (m_eCurState == RUNNING_LEFT)
		{
			if (CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
			{
				m_pFrameKey = L"PLAYER_ROLLING_LEFT";
				m_eNextState = ROLLING_LEFT;
				m_bIsRightDir = false;
				m_bIsRolling = true;
			}
		}*/


		if (m_bIsRightDir) // �������� ���� ���� ��
		{
			if (GetAsyncKeyState(VK_CONTROL))
			{
				m_pFrameKey = L"PLAYER_ROARING";
				m_eNextState = ROARING;
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				m_pFrameKey = L"PLAYER_DOWN";
				m_eNextState = DOWN;
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				m_pFrameKey = L"PLAYER_UP";
				m_eNextState = UP;
			}
			/*else
			{
				m_pFrameKey = L"PLAYER_IDLE";
				m_eNextState = IDLE;
			}*/
		}
		else if (!m_bIsRightDir) // ������ ���� ���� ��
		{
			if (GetAsyncKeyState(VK_CONTROL))
			{
				m_pFrameKey = L"PLAYER_ROARING_LEFT";
				m_eNextState = ROARING_LEFT;
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				m_pFrameKey = L"PLAYER_DOWN_LEFT";
				m_eNextState = DOWN_LEFT;
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				m_pFrameKey = L"PLAYER_UP_LEFT";
				m_eNextState = UP_LEFT;
			}
			/*else
			{
				m_pFrameKey = L"PLAYER_IDLE_LEFT";
				m_eNextState = IDLE_LEFT;
			}*/
		}

		if (CKeyMgr::Get_Instance()->KeyUP(VK_SPACE))
			m_bIsJump = true;
	}
}

void CPlayer::SceneChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case CPlayer::IDLE:
		case CPlayer::IDLE_LEFT:
			m_tInfo.fCX = 80.f;
			m_tInfo.fCY = 75.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 10;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::ROARING:
		case CPlayer::ROARING_LEFT:
			m_tInfo.fCX = 135.f;
			m_tInfo.fCY = 90.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 9;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::DOWN:
		case CPlayer::DOWN_LEFT:
			m_tInfo.fCX = 120.f;
			m_tInfo.fCY = 75.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 14;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::UP:
		case CPlayer::UP_LEFT:
			m_tInfo.fCX = 96.f;
			m_tInfo.fCY = 90.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 3;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::RUNNING:
		case CPlayer::RUNNING_LEFT:
			m_tInfo.fCX = 130.f;
			m_tInfo.fCY = 75.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 13;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::ROLLING:
		case CPlayer::ROLLING_LEFT:
			m_tInfo.fCX = 106.f;
			m_tInfo.fCY = 76.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 13;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}
		m_eCurState = m_eNextState;
		m_bMotionEnd = false;
	}
}

void CPlayer::FrameMove()
{
	//if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount()
	//	&& m_tFrame.iFrameStart_X != m_tFrame.iFrameEnd_X)
	//{
	//	++m_tFrame.iFrameStart_X;
	//	m_tFrame.dwFrameTime = GetTickCount();
	//}

	//// IDLE �϶��� �ݺ�
	//if (m_eCurState == IDLE)
	//{
	//	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	//	{

	//		m_tFrame.iFrameStart_X = 0;
	//		m_bMotionEnd = true;
	//	}
	//}
	//else
	//{
	//	// ������ ȭ�鿡�� ����
	//	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	//	{

	//		m_tFrame.iFrameStart_X = m_tFrame.iFrameEnd_X;
	//		m_bMotionEnd = true;
	//	}
	//}

	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{

		m_tFrame.iFrameStart_X = 0;
		m_bMotionEnd = true;
	}

}
