// Rolling: 아무 키도 안 먹음
// Roaring: 아무 키도 안 먹음
// Hurting: 아무 키도 안 먹음
// Danging: 왼쪽, 오른쪽, 위쪽, 아래쪽
// Jump: 왼쪽, 오른쪽

#include "stdafx.h"
#include "Player.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BitmapMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

#include "HedgeHog.h"

#include "Monster.h"
#include "Item.h"
#include "Vertex.h"

CPlayer::CPlayer()
	: m_eNextState(IDLE)
	, m_eCurState(IDLE)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{

	m_iHp = 100;
	m_iMaxHp = 100;
	m_iMp = 100;
	m_iMaxMp = 100;
	
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

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_HURT.bmp", L"PLAYER_HURT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_HURT_LEFT.bmp", L"PLAYER_HURT_LEFT");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_STANDING_LAND.bmp", L"PLAYER_STANDING_LAND");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_STANDING_LAND_LEFT.bmp", L"PLAYER_STANDING_LAND_LEFT");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_STANDING_JUMP.bmp", L"PLAYER_STANDING_JUMP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_STANDING_JUMP_LEFT.bmp", L"PLAYER_STANDING_JUMP_LEFT");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_GRABBING_LEDGE_FIRST.bmp", L"PLAYER_GRABBING_LEDGE_FIRST");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_GRABBING_LEDGE_SECOND.bmp", L"PLAYER_GRABBING_LEDGE_SECOND");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_STANDING_JUMP_LEFT.bmp", L"PLAYER_STANDING_JUMP_LEFT");

	m_bIsRightDir = true;
	m_bIsRolling = false;
	m_bIsRoaring = false;
	m_bIsDangling = false;

	m_pFrameKey = L"PLAYER_IDLE";
	m_tInfo.fCX = 80.f; 
	m_tInfo.fCY = 75.f; 
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount(); 
	m_tFrame.iFrameStart_X = 0; 
	m_tFrame.iFrameEnd_X = 10;
	m_tFrame.iFrameStart_Y = 0;
	
	m_dwRecover = GetTickCount();
	m_dwNoCollision = GetTickCount();


	m_bIsJump = false;
	m_fSpeed = 5.f;
	m_fDeltaTime = 0.f;
	m_fVelY = 0.f;
	m_fJumpPower = -10.f;

	// m_fVelX = 0.f;

	//pCollisionObj = nullptr;

	m_bIsSaved = false;
	m_fSaving_X = 0.f;
	m_fSaving_Y = 0.f;
}

int CPlayer::Update()
{
	float fScrollX = CScrollMgr::Get_ScrollX();
	float fScrollY = CScrollMgr::Get_ScrollY();
	
	if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
	{
		cout << "iScrollX: " << fScrollX << " / iScrollY: " << fScrollY << endl;
	}
	
	CSceneMgr::SCENEID eStage = CSceneMgr::Get_Instance()->Get_SCENEID();
	//
	//float fScrollMaxX = CSceneMgr::Get_Instance()->Get_pScene()->Get_BackgroundWidth();

	//// 왼쪽을 보다가 딱! 오른쪽을 보면, 그때부터 왼쪽으로 적당한 거리만큼 플레이어를 이동.
	//if (m_eCurState == IDLE && m_tInfo.fX > 260.f)
	//{
	//	// 최대 130 이동
	//	if (eStage == CSceneMgr::SCENE_STAGE)
	//	{
	//		if (390 - 260 - 130 < fScrollX && fScrollX < fScrollMaxX - WINCX)
	//		{
	//			m_tInfo.fX -= 1.f;
	//			CScrollMgr::Sum_ScrollX(1);
	//			//cout << "fScrollX: " << fScrollX << endl;
	//		}
	//	}
	//}

	//// 오른쪽을 보다가 딱! 왼쪽을 보면, 그때부터 오른쪽으로 적당한 거리만큼 플레이어를 이동.
	//else if (m_eCurState == IDLE_LEFT && m_tInfo.fX < 390.f)
	//{
	//	if (eStage == CSceneMgr::SCENE_STAGE)
	//	{
	//		if (390 - 260 - 130 < fScrollX && fScrollX < fScrollMaxX - WINCX)
	//		{
	//			m_tInfo.fX += 1.f;
	//			CScrollMgr::Sum_ScrollX(-1);
	//			//cout << "fScrollX: " << fScrollX << endl;
	//		}
	//	}
	//}

	KeyCheck();
	IsJumping();
	IsRoaring();
	IsRolling();
	IsHurting();
	IsOffset();
	SceneChange();

	if (m_dwRecover + 1000 < GetTickCount())
	{
		if (m_iHp < m_iMaxHp)
			m_iHp++;
		if (m_iMp < m_iMaxMp)
			m_iMp++;
		m_dwRecover = GetTickCount();
	}

	FrameMove();

	return 0;
}

void CPlayer::LateUpdate()
{
	CObj::UpdateRect();

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	if (0 > m_tRect.left-iScrollX) m_tInfo.fX += m_fSpeed;
	if (WINCX < m_tRect.right - iScrollX) m_tInfo.fX -= m_fSpeed;
	if (0 > m_tRect.top+iScrollY) m_tInfo.fY += m_fSpeed;
	if (WINCY < m_tRect.bottom+iScrollY) m_tInfo.fY -= m_fSpeed;
}

void CPlayer::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);


	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left- iScrollX, m_tRect.top+ iScrollY, //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart_X, 
		m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
		m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);
}

void CPlayer::Release()
{
}

void CPlayer::IsJumping()
{
	float fy = 0.f; 
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fy);

	// 스페이스바를 누르면 true가 된다
	if (m_bIsJump && !m_bIsDangling)
	{
		m_fVelY = m_fDeltaTime + m_fJumpPower;
	 	m_tInfo.fY += m_fVelY;
		m_fDeltaTime += 0.5f;

		if (bIsColl && m_tInfo.fY > fy)
		{
			m_bIsJump = false;
			m_bIsHurting = false;
			m_fDeltaTime = 0.f;
			m_fJumpPower = -10.f;
			m_tInfo.fY = fy;
			BackToIdle();
		}
	}
	else if (bIsColl && !m_bIsDangling)
		// 매달릴때는 땅으로 떨어지면 안돼
	{
		//m_tInfo.fY = fy;
	}
}

void CPlayer::IsHurting()
{
	if (m_bIsHurting)
	{
		if (!m_bIsRightDir)	
		{
			m_tInfo.fX += m_fSpeed;
		}
		else
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}
}

void CPlayer::IsDanging()
{
}

void CPlayer::IsOffset()
{
	int iOffsetX = WINCX / 2;
	int iOffsetY = WINCY / 2;

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	if (iOffsetX + 200 < m_tInfo.fX - iScrollX)
		CScrollMgr::Sum_ScrollX(+m_fSpeed);
	if (iOffsetX - 200 > m_tInfo.fX - iScrollX)
		CScrollMgr::Sum_ScrollX(-m_fSpeed);
	
	if (iOffsetY - 100 > m_tInfo.fY + iScrollY)
		CScrollMgr::Sum_ScrollY(m_fSpeed);
	if (iOffsetY + 100 < m_tInfo.fY + iScrollY)
		CScrollMgr::Sum_ScrollY(-m_fSpeed);
}

void CPlayer::IsRoaring()
{
	if (m_eCurState == ROARING || m_eCurState == ROARING_LEFT)
	{
		if (m_iMp > 30)
		{
			OBJLIST listMonster = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::MONSTER);
			for (auto& pMonster : listMonster)
			{
				// 일정 반경 내에 있는 고슴도치만 뒤집힌다.
				if (pMonster->Is_Inside(m_tRect.left - 150, m_tRect.top - 10, m_tRect.right + 150, m_tRect.bottom + 10))
				{
					if (! static_cast<CHedgeHog*>(pMonster)->Get_UpsideState())
					{
						static_cast<CHedgeHog*>(pMonster)->Upside_Down();
					}
				}
			}
		}
	}
}

void CPlayer::IsRolling()
{
	if (m_bIsRolling)
	{
		if (m_bIsRightDir)
			m_tInfo.fX += m_fSpeed;
		else
			m_tInfo.fX -= m_fSpeed;
	}
}

void CPlayer::KeyCheck()
{
	if (m_eNextState == STANDING_JUMP
		|| m_eNextState == STANDING_JUMP_LEFT)
	{
		// 뛰는 중인 경우 왼쪽이나 오른쪽 키만 먹는다.
		// 모션이 달리기가 아니라 점프 상태를 유지하며 방향만 바뀐다.
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		{
			m_pFrameKey = L"PLAYER_STANDING_JUMP_LEFT";
			m_eNextState = STANDING_JUMP_LEFT;
			m_bIsRightDir = false;
			m_tInfo.fX -= m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		{
			m_pFrameKey = L"PLAYER_STANDING_JUMP";
			m_eNextState = STANDING_JUMP;
			m_bIsRightDir = true;
			m_tInfo.fX += m_fSpeed;
		}
	}
	else if (m_bIsDangling)
	{
	}
	else if (m_bIsRolling || m_bIsRoaring || m_bIsHurting)
	{
	}
	else
	{
	

		// 아래나 위를 보고 있다가 키를 떼면 IDLE로 돌아온다.
		if (CKeyMgr::Get_Instance()->KeyUP(VK_DOWN)
			|| CKeyMgr::Get_Instance()->KeyUP(VK_UP))
		{
			if (m_bIsRightDir)
			{
				m_pFrameKey = L"PLAYER_IDLE";
				m_eNextState = IDLE_LEFT;
				m_bIsRightDir = true;
			}
			else
			{
				m_pFrameKey = L"PLAYER_IDLE_LEFT";
				m_eNextState = IDLE;
				m_bIsRightDir = false;
			}
		}

		// 왼쪽을 꾹 누르면 달린다.
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		{
			m_pFrameKey = L"PLAYER_RUNNING_LEFT";
			m_eNextState = RUNNING_LEFT;
			m_bIsRightDir = false;
			m_tInfo.fX -= m_fSpeed;
		}

		// 오른쪽을 꾹 누르면 달린다.
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		{
			m_pFrameKey = L"PLAYER_RUNNING";
			m_eNextState = RUNNING;
			m_bIsRightDir = true;
			m_tInfo.fX += m_fSpeed;
		}

		if (m_bIsRightDir) // 오른쪽을 보고 있을 때
		{
			// 짖는 중이 아닐때만 짖을 수 있다
			// 짖는 중에 또 짖을 수 없음.
			// MP 10 소모
			if (CKeyMgr::Get_Instance()->KeyDown(VK_CONTROL)
				&& m_eCurState != ROARING)
			{
				if (m_iMp >= 10)
				{
					m_pFrameKey = L"PLAYER_ROARING";
					m_eNextState = ROARING;
					m_iMp -= 10;
					m_bIsRoaring = true;
				}
			}
			else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
			{
				m_pFrameKey = L"PLAYER_DOWN";
				m_eNextState = DOWN;
			}
			else if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
			{
				m_pFrameKey = L"PLAYER_UP";
				m_eNextState = UP;
			}
		}

		else if (!m_bIsRightDir) // 왼쪽을 보고 있을 때
		{
			if (CKeyMgr::Get_Instance()->KeyDown(VK_CONTROL)
				&& m_eCurState != ROARING)
			{
				if (m_iMp >= 10)
				{
					m_pFrameKey = L"PLAYER_ROARING_LEFT";
					m_eNextState = ROARING_LEFT;
					m_iMp -= 10;
					m_bIsRoaring = true;
				}
			}
			else if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
			{
				m_pFrameKey = L"PLAYER_DOWN_LEFT";
				m_eNextState = DOWN_LEFT;
			}
			else if (CKeyMgr::Get_Instance()->KeyPressing(VK_UP))
			{
				m_pFrameKey = L"PLAYER_UP_LEFT";
				m_eNextState = UP_LEFT;
			}
		}

		// 왼+아래 -> 왼쪽으로 구르기
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT) && CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
		{
			m_pFrameKey = L"PLAYER_ROLLING_LEFT";
			m_eNextState = ROLLING_LEFT;
			m_bIsRightDir = false;
			m_bIsRolling = true;
		}

		// 오+아래 -> 오른쪽으로 구르기
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT) && CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
		{
			m_pFrameKey = L"PLAYER_ROLLING";
			m_eNextState = ROLLING;
			m_bIsRightDir = true;
			m_bIsRolling = true;
		}

		//## 왼쪽이나 오른쪽에 관련된 키 처리
		// 왼쪽 누르고 뗄 때 IDLE
		if (CKeyMgr::Get_Instance()->KeyUP(VK_LEFT))
		{
			m_pFrameKey = L"PLAYER_IDLE_LEFT";
			m_eNextState = IDLE_LEFT;
			m_bIsRightDir = false;
		}

		// 오른쪽 누르고 뗄 때 IDLE
		if (CKeyMgr::Get_Instance()->KeyUP(VK_RIGHT))
		{
			m_pFrameKey = L"PLAYER_IDLE";
			m_eNextState = IDLE;
			m_bIsRightDir = true;
		}
	}

	// 스페이스바를 꾸욱 누르면 더 높게 뛴다.
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_SPACE)) 
	{
		m_bIsJump = true;
	
		if(m_fJumpPower > -11)
			m_fJumpPower -= 0.3f;
		
		if (m_bIsRightDir)
		{
			m_pFrameKey = L"PLAYER_STANDING_JUMP";
			m_eNextState = STANDING_JUMP;
		}
		else
		{
			m_pFrameKey = L"PLAYER_STANDING_JUMP_LEFT";
			m_eNextState = STANDING_JUMP_LEFT;
		}
	}

	if (CKeyMgr::Get_Instance()->KeyPressing('Q'))
	{
		m_tInfo.fY -= m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		m_tInfo.fY += m_fSpeed;
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
			m_tFrame.iFrameEnd_X = 8;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::LEDGE_DOWN:
		case CPlayer::LEDGE_DOWN_LEFT:
			m_tInfo.fCX = 130.f;
			m_tInfo.fCY = 116.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 3;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::STANDING_LAND:
		case CPlayer::STANDING_LAND_LEFT:
			m_tInfo.fCX = 88.f;
			m_tInfo.fCY = 106.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 5;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::STANDING_JUMP:
		case CPlayer::STANDING_JUMP_LEFT:
			m_tInfo.fCX = 102.f;
			m_tInfo.fCY = 138.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 9;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::HURT:
		case CPlayer::HURT_LEFT:
			m_tInfo.fCX = 106.f;
			m_tInfo.fCY = 108.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 6;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::GRABBING_LEDGE_FIRST:
		case CPlayer::GRABBING_LEDGE_FIRST_LEFT:
			m_tInfo.fCX = 228.f;
			m_tInfo.fCY = 300.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 10;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::GRABBING_LEDGE_SECOND:
		case CPlayer::GRABBING_LEDGE_SECOND_LEFT:
			m_tInfo.fCX = 228.f;
			m_tInfo.fCY = 300.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 8;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}
		m_eCurState = m_eNextState;
		m_bMotionEnd = false;
	}
}

void CPlayer::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		int i = 0; 

		// 위나 아래를 보는 경우 마지막에서 프레임 유지
		if (m_eCurState == DOWN
			|| m_eCurState == DOWN_LEFT
			|| m_eCurState == UP
			|| m_eCurState == UP_LEFT)
		{
			m_tFrame.iFrameStart_X = m_tFrame.iFrameEnd_X-1;
		}
		// 구르는 경우나, 짖는 경우, 몬스터와 부딪힌 경우, 마지막에 IDLE로 교체
		else if (m_eCurState == ROLLING
			|| m_eCurState == ROLLING_LEFT)
		{
			BackToIdle();
			m_bIsRolling = false;
		}
		else if (m_eCurState == ROARING
			|| m_eCurState == ROARING_LEFT)
		{
			BackToIdle();
			m_bIsRoaring = false;
		}
		else if (m_bIsHurting)
		{
			BackToIdle();
			m_bIsHurting = false;
		}
		else if (m_bIsDangling)
		{
			m_pFrameKey = L"PLAYER_GRABBING_LEDGE_SECOND";
			m_eNextState = GRABBING_LEDGE_SECOND;
			m_tFrame.iFrameStart_X = 0;
		}
		else
		{
			m_tFrame.iFrameStart_X = 0;
		}
	}

}


void CPlayer::Collision_Proc(CObj * pCounterObj)
{
	if (Is_Counter_One_Of(CMonster))
	{
		if (m_eCurState == STANDING_JUMP
			|| m_eCurState == STANDING_JUMP_LEFT)
		{}
		else
		{
			if (m_dwNoCollision + 2000 < GetTickCount())
			{
				m_iHp -= 10;
				m_dwNoCollision = GetTickCount();

				m_bIsJump = true;
				m_fJumpPower = -10.f;

				if (m_bIsRightDir) // 오른쪽을 보고 있는 경우
				{
					m_pFrameKey = L"PLAYER_HURT";
					m_eNextState = HURT;
				}
				else // 왼쪽을 보고 있는 경우
				{
					m_pFrameKey = L"PLAYER_HURT_LEFT";
					m_eNextState = HURT_LEFT;
				}

				//pCollisionObj = pCounterObj;
				m_fVelY = -10.f;
				m_bIsHurting = true;
			}
		}
	}
	if (Is_Counter_One_Of(CItem))
	{
		CItem::ID eID = static_cast<CItem*>(pCounterObj)->Get_ID();
		switch (eID)
		{
		case CItem::HP:
			m_iHp += 10;
			if (m_iHp > m_iMaxHp)
				m_iHp = m_iMaxHp;
			break;

		case CItem::MP:
			m_iMp += 10;
			if (m_iMp > m_iMaxMp)
				m_iMp = m_iMaxMp;
			break;

		case CItem::LIFE:
			iLife++;
			break;

		case CItem::SAVE:
			m_bIsSaved = true;
			m_fSaving_X = pCounterObj->Get_Info().fCX;
			m_fSaving_Y = pCounterObj->Get_Info().fCY;
			break;
		}
	}

	if (Is_Counter_One_Of(CVertex))
	{
		if (!m_bIsDangling)
		{
			// 절벽 끝에 매달리 경우 아래키, 위쪽키, 왼쪽, 오른쪽키만 사용 가능
			float fTargetX = pCounterObj->Get_Info().fX;
			float fTargetY = pCounterObj->Get_Info().fY;

			if (fTargetX - 10 <= m_tInfo.fX && m_tInfo.fX <= fTargetX + 10
				&& fTargetY - 10 <= m_tInfo.fY && m_tInfo.fY <= fTargetY + 10)
			{
				m_pFrameKey = L"PLAYER_GRABBING_LEDGE_FIRST";
				m_eNextState = GRABBING_LEDGE_FIRST;
				m_bIsDangling = true;
				m_bIsJump = false;
				m_tInfo.fY = fTargetY;
				m_tInfo.fX = fTargetX;
			}
		}
	}
}

void CPlayer::BackToIdle()
{
	if (m_bIsRightDir)
	{
		m_pFrameKey = L"PLAYER_IDLE";
		m_eNextState = IDLE;
	}
	else
	{
		m_pFrameKey = L"PLAYER_IDLE_LEFT";
		m_eNextState = IDLE_LEFT;
	}

	m_bIsHurting = false;
	m_bIsRolling = false;
	m_bIsJump = false;
	m_bIsRoaring = false;
}
