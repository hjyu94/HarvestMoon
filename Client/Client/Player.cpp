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

#include "Monster.h"
#include "HedgeHog.h"
#include "Fly.h"
#include "Hyena.h"
#include "Lizard.h"

#include "Item.h"
#include "Vertex.h"
#include "Block.h"
#include "VerticalBlocck.h"

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

	m_iHp = 90;
	m_iMaxHp = 90;
	m_iMp = 90;
	m_iMaxMp = 90;


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

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_GRABBING_LEDGE_FIRST_LEFT.bmp", L"PLAYER_GRABBING_LEDGE_FIRST_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_GRABBING_LEDGE_SECOND_LEFT.bmp", L"PLAYER_GRABBING_LEDGE_SECOND_LEFT");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_CLIMBING_LEDGE.bmp", L"PLAYER_CLIMBING_LEDGE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_CLIMBING_LEDGE_LEFT.bmp", L"PLAYER_CLIMBING_LEDGE_LEFT");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_DEAD.bmp", L"PLAYER_DEAD");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_DEAD_LEFT.bmp", L"PLAYER_DEAD_LEFT");

	m_bIsRightDir = true;
	m_bIsRolling = false;
	m_bIsRoaring = false;
	m_bIsDangling = false;


	m_pFrameKey = L"PLAYER_STANDING_LAND";
	m_eCurState = STANDING_LAND;
	m_tInfo.fCX = 88.f;
	m_tInfo.fCY = 106.f;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 5;
	m_tFrame.iFrameStart_Y = 0;


	m_dwRecover = GetTickCount();
	m_dwNoCollision = GetTickCount();


	m_bIsJump = false;
	m_fSpeed = 5.f;
	m_fDeltaTime = 0.f;
	m_fVelY = 0.f;
	m_fJumpPower = 0.f;

	m_bIsSaved = false;

	m_bIsSeeingDown = false;
	m_bIsSeeingUp = false;
	m_bIsScrollEffect = false;
	m_bIsBlockCollision = false;
	m_bIs_On_Another_Scene = false;

	m_bIsTransparent = false;
	m_iTransparentCount = 0;

	m_dwUp = GetTickCount();
	m_dwDown = GetTickCount();

	m_eNextState = STANDING_LAND;
	m_pFrameKey = L"PLAYER_STANDING_LAND";

	m_dwKill = GetTickCount();
}

int CPlayer::Update()
{
	if (!m_bIs_On_Another_Scene)
	{
		KeyCheck();
		IsJumping();
		IsRoaring();
		IsRolling();
		IsHurting();
		IsOffset();
		IsRecovering();
	}

	if (m_bIs_On_Another_Scene)
	{
		Is_On_Another_Scene();
	}

	SceneChange();
	FrameMove();

	// 치트키: 뭔가 막혔을때 상태 처음으로 되돌림
	if (CKeyMgr::Get_Instance()->KeyDown(VK_F1))
	{
		m_bIsDangling = false;
		m_bIsHurting = false;
		m_bIsRoaring = false;
		m_bIsRolling = false;
		m_bIsJump = false;
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_F5))
	{
		m_tInfo.fX = 2200.f;
		m_tInfo.fY = -2000.f;
		CScrollMgr::Reset_Scroll();
		CScrollMgr::Sum_ScrollX(1900.f);
		CScrollMgr::Sum_ScrollY(2200.f);
	}
	
	return 0;
}

void CPlayer::LateUpdate()
{
	CObj::UpdateRect();

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	if (!m_bIs_On_Another_Scene)
	{
		if (0 > m_tRect.left - iScrollX) m_tInfo.fX += m_fSpeed;
		if (WINCX < m_tRect.right - iScrollX) m_tInfo.fX -= m_fSpeed;
		if (0 > m_tRect.top + iScrollY) m_tInfo.fY += m_fSpeed;
		if (WINCY < m_tRect.bottom + iScrollY) m_tInfo.fY -= m_fSpeed;
	}

	if (m_iHp <= 0 && !m_bIs_On_Another_Scene)
	{
		iLife--;

		m_bIs_On_Another_Scene = true;
		m_bIsDangling = false;
		m_bIsHurting = false;
		m_bIsRoaring = false;
		m_bIsRolling = false;
		m_bIsJump = false;

		int iScrollX = CScrollMgr::Get_ScrollX();
		int iScrollY = CScrollMgr::Get_ScrollY();

		m_tInfo.fX -= iScrollX;
		m_tInfo.fY += iScrollY;

		CScrollMgr::Reset_Scroll();
		CObj::UpdateRect();

		if (m_bIsRightDir)
		{
			m_eNextState = DIE;
			m_pFrameKey = L"PLAYER_DEAD";
		}

		else
		{
			m_eNextState = DIE_LEFT;
			m_pFrameKey = L"PLAYER_DEAD_LEFT";
		}

		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_DEAD);
	}
}

void CPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();

	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();


	// 치트키 : 충돌하는 Rect 출력
	if (CKeyMgr::Get_Instance()->KeyPressing('P'))
	{
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_F3))
	{
		m_iHp = 1;
	}



	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);


	if (m_bIs_On_Another_Scene)
	{
		if (m_bIsRightDir)
		{
			GdiTransparentBlt(hDC, // 실제 복사받을 DC
				m_tRect.left, m_tRect.top, //출력될 위치의 xy 좌표 
				m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
				hMemDC,
				m_tInfo.fCX * m_tFrame.iFrameStart_X,
				m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
				m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
				RGB(0, 0, 0)
			);
		}
		else
		{
			GdiTransparentBlt(hDC, // 실제 복사받을 DC
				m_tRect.left, m_tRect.top, //출력될 위치의 xy 좌표 
				m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
				hMemDC,
				m_tInfo.fCX * (m_tFrame.iFrameEnd_X - m_tFrame.iFrameStart_X - 1),
				m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
				m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
				RGB(0, 0, 0)
			);
		}


	}
	// 반짝이느 효과
	else if (m_bIsHurting)
	{
		if (m_iTransparentCount % 4 == 0)
		{
			GdiTransparentBlt(hDC, // 실제 복사받을 DC
				m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
				m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
				hMemDC,
				m_tInfo.fCX * m_tFrame.iFrameStart_X,
				m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
				m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
				RGB(255, 255, 255)
			);
		}
	}
	else
	{
		GdiTransparentBlt(hDC, // 실제 복사받을 DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
			m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
			hMemDC,
			m_tInfo.fCX * m_tFrame.iFrameStart_X,
			m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
			m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
			RGB(255, 255, 255)
		);
	}

	// 치트키 : 충돌하는 Rect 출력
	if (CKeyMgr::Get_Instance()->KeyPressing('P'))
	{
		Ellipse(hDC, m_tInfo.fX - 5 - iScrollX, m_tInfo.fY - 5 + iScrollY, m_tInfo.fX + 5 - iScrollX, m_tInfo.fY + 5 + iScrollY);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Ellipse(hDC, m_tInfo.fX - 5 - iScrollX, m_tInfo.fY - 5 + iScrollY, m_tInfo.fX + 5 - iScrollX, m_tInfo.fY + 5 + iScrollY);
	}
}

void CPlayer::Release()
{
}

void CPlayer::IsJumping()
{
	float fy = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fy);

	if(!m_bIsDangling)
		if (fabs(m_tInfo.fY - fy) > 30.f) 
			m_bIsJump = true;

	if (!m_bIsDangling)
	{
		if (m_bIsJump)
		{
			m_fVelY = m_fDeltaTime + m_fJumpPower;
			m_tInfo.fY += m_fVelY;
			m_fDeltaTime += 0.5f;

			if (bIsColl && m_tInfo.fY >= fy)
			{
				m_bIsJump = false;
				m_bIsHurting = false;
				m_fDeltaTime = 0.f;
				m_fJumpPower = 0.f;
				m_tInfo.fY = fy;

				m_bIsBlockCollision = false;

				/*BackToIdle();*/
				if (m_bIsRightDir)
				{
					m_pFrameKey = L"PLAYER_STANDING_LAND";
					m_eNextState = STANDING_LAND;
				}
				else
				{
					m_pFrameKey = L"PLAYER_STANDING_LAND_LEFT";
					m_eNextState = STANDING_LAND_LEFT;
				}
			}
		}
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

		m_iTransparentCount++;
	}
}

void CPlayer::IsDanging()
{
	if (m_bIsDangling)
	{

	}
}

void CPlayer::IsOffset()
{
	int iOffsetX = WINCX / 2;
	int iOffsetY = WINCY / 2;

	int iScrollX = CScrollMgr::Get_ScrollX();
	int iScrollY = CScrollMgr::Get_ScrollY();

	if (iOffsetX + 60 < m_tInfo.fX - iScrollX)
		CScrollMgr::Sum_ScrollX(+m_fSpeed);
	if (iOffsetX - 60 > m_tInfo.fX - iScrollX)
		CScrollMgr::Sum_ScrollX(-m_fSpeed);

	if (iOffsetY - 100 > m_tInfo.fY + iScrollY)
		CScrollMgr::Sum_ScrollY(m_fSpeed);
	if (iOffsetY + 100 < m_tInfo.fY + iScrollY)
		CScrollMgr::Sum_ScrollY(-m_fSpeed);

	/*if (iOffsetY - 100 > m_tInfo.fY + iScrollY)
	{
	if (m_bIsJump)
	CScrollMgr::Sum_ScrollY(+m_fVelY);
	else
	CScrollMgr::Sum_ScrollY(+m_fSpeed);
	}
	if (iOffsetY + 100 < m_tInfo.fY + iScrollY)
	{
	CScrollMgr::Sum_ScrollY(-m_fSpeed);
	}*/
}

void CPlayer::IsRecovering()
{
	if (m_dwRecover + 1000 < GetTickCount())
	{
		if (m_iHp < m_iMaxHp)
			m_iHp++;
		if (m_iMp < m_iMaxMp)
			m_iMp++;
		m_dwRecover = GetTickCount();
	}
}

void CPlayer::Is_On_Another_Scene()
{
	POINT pt = { m_tInfo.fX, m_tInfo.fY };
	RECT rect = { WINCX / 2 - 10, WINCY / 2 - 10, WINCX / 2 + 10, WINCY / 2 + 10 };

	if (!PtInRect(&rect, pt))
	{
		int iTargetX = WINCX / 2;
		int iTargetY = WINCY / 2;

		float fDeltaX = m_tInfo.fX - iTargetX;
		float fDeltaY = m_tInfo.fY - iTargetY;

		float fTheta = atan2(fDeltaY, fDeltaX); // 호도법

		m_tInfo.fX -= 5.f * cosf(fTheta);
		m_tInfo.fY -= 5.f * sinf(fTheta);
	}
	else
	{
		m_tInfo.fX = WINCX / 2;
		m_tInfo.fY = WINCY / 2;
	}

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
				// 일정 반경 내에 있는 몬스터중
				if (pMonster->Is_Inside(m_tRect.left - 150, m_tRect.top - 10, m_tRect.right + 150, m_tRect.bottom + 10))
				{
					// 고슴도치만 뒤집힌다.
					// 정상인 얘들이 보이면 뒤집음. 이미 뒤집힌 얘는 뒤집지 않음.
					if (!static_cast<CHedgeHog*>(pMonster)->Get_UpsideState())
					{
						static_cast<CHedgeHog*>(pMonster)->Upside_Down();
					}
					else
					{
						pMonster->Set_Stun();
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

	if (m_bIsDangling)
	{
		if (m_bIsRightDir) // 오른쪽을 보고 있는 경우, 아래키랑 오른쪽 키만 먹는다
		{
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RIGHT))
			{
				//m_tInfo.fX += 40.f;
				m_pFrameKey = L"PLAYER_CLIMBING_LEDGE";
				m_eNextState = CPlayer::CLIMBING_LEDGE;
				m_tInfo.fY += 50.f; // 애니메이션 효과때문에 좀 아래로 그림을 내림
									// m_bIsDangling = false; // 모션 끝에서 false로 바꿔줌 여기서 안함
				m_tInfo.fX += 10.f;
			}
		}

		else if (!m_bIsRightDir) // 왼쪽을 보고 있는 경우, 아래키랑 왼쪽 키만 먹는다
		{
			if (CKeyMgr::Get_Instance()->KeyDown(VK_LEFT))
			{
				m_pFrameKey = L"PLAYER_CLIMBING_LEDGE_LEFT";
				m_eNextState = CPlayer::CLIMBING_LEDGE_LEFT;
				m_tInfo.fY += 50.f; // 애니메이션 효과때문에 좀 아래로 그림을 내림
									// m_bIsDangling = false; // 모션 끝에서 false로 바꿔줌 여기서 안함
				m_tInfo.fX -= 10.f;
			}
		}

		if (CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
		{
			m_tInfo.fY += 40.f;
			m_bIsDangling = false;
			if (m_bIsRightDir)
			{
				m_pFrameKey = L"PLAYER_STANDING_JUMP";
				m_eNextState = CPlayer::STANDING_JUMP;
			}
			else
			{
				m_pFrameKey = L"PLAYER_STANDING_JUMP_LEFT";
				m_eNextState = CPlayer::STANDING_JUMP_LEFT;
			}
		}
	}
	else if (m_bIsHurting)
	{
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed*0.7;
		}
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed*0.7;
		}

	}
	else if (m_bIsRolling || m_bIsRoaring)
	{
	}

	else
	{
		// 아래나 위를 보고 있다가 키를 떼면 IDLE로 돌아온다.
		// 스크롤 값을 바꾼 경우는 다시 돌려놓는다.                            
		if (CKeyMgr::Get_Instance()->KeyUP(VK_DOWN))
		{
			BackToIdle();
			m_bIsSeeingDown = false;
			if (m_bIsScrollEffect)
			{
				CScrollMgr::Sum_ScrollY(+30.f);
				m_bIsScrollEffect = false;
			}
		}

		if (CKeyMgr::Get_Instance()->KeyUP(VK_UP))
		{
			BackToIdle();
			m_bIsSeeingUp = false;

			if (m_bIsScrollEffect)
			{
				CScrollMgr::Sum_ScrollY(-30.f);
				m_bIsScrollEffect = false;
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

				if (m_bIsSeeingDown)
				{
					if (m_dwDown + 1000 < GetTickCount())
					{
						if (!m_bIsScrollEffect)
						{
							CScrollMgr::Sum_ScrollY(-30.f);
							m_bIsScrollEffect = true;
						}
					}
				}
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

				if (m_bIsSeeingDown)
				{
					if (m_dwDown + 1000 < GetTickCount())
					{
						if (!m_bIsScrollEffect)
						{
							CScrollMgr::Sum_ScrollY(-30.f);
							m_bIsScrollEffect = true;
						}
					}
				}
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

		// 스페이스바를 꾸욱 누르면 더 높게 뛴다.
		// 대롱대롱 매달려 있을땐 뛰면 안됨
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_SPACE))
		{
			// 처음 속도는 -12.f
			if (!m_bIsJump)
			{
				m_fJumpPower = -12.f;

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

				m_bIsJump = true;
			}

			if (m_fJumpPower > -13) m_fJumpPower -= 0.1f;
		}
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
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 9;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::DOWN:
		case CPlayer::DOWN_LEFT:
			m_tInfo.fCX = 120.f;
			m_tInfo.fCY = 75.f;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 4;
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
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 5;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::STANDING_JUMP:
		case CPlayer::STANDING_JUMP_LEFT:
			m_tInfo.fCX = 102.f;
			m_tInfo.fCY = 138.f;
			m_tFrame.dwFrameSpeed = 200;
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
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 10;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::GRABBING_LEDGE_SECOND:
		case CPlayer::GRABBING_LEDGE_SECOND_LEFT:
			m_tInfo.fCX = 228.f;
			m_tInfo.fCY = 300.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 8;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::CLIMBING_LEDGE:
		case CPlayer::CLIMBING_LEDGE_LEFT:
			m_tInfo.fCX = 99.f;
			m_tInfo.fCY = 221.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 8;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::DIE:
		case CPlayer::DIE_LEFT:
			m_tInfo.fCX = 150.f;
			m_tInfo.fCY = 150.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 23;
			m_tFrame.iFrameStart_Y = 0;

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
		if (m_bIs_On_Another_Scene)
		{
			if (m_tFrame.iFrameStart_X == 16)
				m_tFrame.dwFrameSpeed = 500;
			else if (m_tFrame.iFrameStart_X == m_tFrame.iFrameEnd_X - 1)
				m_tFrame.dwFrameSpeed = 800;
			else
				m_tFrame.dwFrameSpeed = 100;
		}
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		// 다른 Scene에 있는 경우(죽은 경우) stage scene으로 돌아오기
		if (m_bIs_On_Another_Scene)
		{
			if (iLife>0)
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE);
				this->Initialize();
				this->Set_Pos(m_fSaving_X, m_fSaving_Y);
				CScrollMgr::Reset_Scroll();
				CScrollMgr::Sum_ScrollX(m_fSaving_X - 340 - 100);
				CScrollMgr::Sum_ScrollY(-m_fSaving_Y + 340 + 100);
				m_eNextState = STANDING_LAND;
				m_pFrameKey = L"PLAYER_STANDING_LAND";
			}
			else
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_RESTART);
			}
		}

		// 위나 아래를 보는 경우 마지막에서 프레임 유지
		else if (m_eCurState == DOWN
			|| m_eCurState == DOWN_LEFT)
		{
			m_tFrame.iFrameStart_X = m_tFrame.iFrameEnd_X - 1;
			if (!m_bIsSeeingDown) m_dwDown = GetTickCount();
			m_bIsSeeingDown = true;
		}
		else if (m_eCurState == UP
			|| m_eCurState == UP_LEFT)
		{
			m_tFrame.iFrameStart_X = m_tFrame.iFrameEnd_X - 1;
			if (!m_bIsSeeingUp && !m_bIsScrollEffect)
			{
				CScrollMgr::Sum_ScrollY(+30.f);
				m_bIsScrollEffect = true;
			}
			m_bIsSeeingUp = true;
		}

		// ledge를 오르는 경우 마지막에 좌표 이동
		else if (m_eCurState == CLIMBING_LEDGE
			|| m_eCurState == CLIMBING_LEDGE_LEFT)
		{
			BackToIdle();
			if (m_bIsRightDir)
			{
				m_tInfo.fX += 10.f;
			}
			else
			{
				m_tInfo.fX -= 10;
			}
			m_tInfo.fY -= 50.f;

			//// 위로 약간 튀자
			//m_bIsJump = true;
			//m_fJumpPower = -10.f;
			//m_fDeltaTime = 0.f;

			m_bIsDangling = false;
		}

		// 구르는 경우나, 짖는 경우, 몬스터와 부딪힌 경우, 착지한 경우, 마지막에 IDLE로 교체
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
			m_iTransparentCount = 0;
		}
		else if (m_eCurState == STANDING_LAND
			|| m_eCurState == STANDING_LAND_LEFT)
		{
			BackToIdle();
		}
		else if (m_bIsDangling)
		{
			if (m_bIsRightDir)
			{
				m_pFrameKey = L"PLAYER_GRABBING_LEDGE_SECOND";
				m_eNextState = GRABBING_LEDGE_SECOND;
			}
			else
			{
				m_pFrameKey = L"PLAYER_GRABBING_LEDGE_SECOND_LEFT";
				m_eNextState = GRABBING_LEDGE_SECOND_LEFT;
			}
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
	if (Is_Counter_One_Of(CLizard))
	{
		if (m_bIsJump && m_tInfo.fY < pCounterObj->Get_Info().fY)
		{
			m_bIsJump = true;
			m_fJumpPower = -10.f;
			m_fDeltaTime = 0.f;

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

			pCounterObj->Set_Dead();
		}
		else
		{
			// m_dwNoCollision 동안은 부딪혀도 다치지 않음.
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

				m_bIsHurting = true;
				m_bIsRolling = false;
				m_bIsDangling = false;
			}
		}
	}

	if (Is_Counter_One_Of(CHedgeHog))
	{
		CHedgeHog* pHedgeHog = static_cast<CHedgeHog*>(pCounterObj);

		if (m_bIsJump && m_tInfo.fY < pCounterObj->Get_Info().fY)
		{
			if (pHedgeHog->Get_UpsideState())
			{
				m_bIsJump = true;
				m_fJumpPower = -10.f;
				m_fDeltaTime = 0.f;

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
				//pHedgeHog->Set_Dead();
			}
			else
			{
				// m_dwNoCollision 동안은 부딪혀도 다치지 않음.
				if (m_dwNoCollision + 2000 < GetTickCount())
				{
					m_iHp -= 10;
					m_dwNoCollision = GetTickCount();

					m_bIsJump = true;
					m_fJumpPower = -10.f;
					m_fDeltaTime = 0.f;

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

					m_bIsHurting = true;
					m_bIsRolling = false;
					m_bIsDangling = false;
				}
			}
		}

		else if (m_eCurState == ROLLING || m_eCurState == ROLLING_LEFT)
		{
			if (pHedgeHog->Get_UpsideState())
			{
				//pHedgeHog->Set_Dead();
				// 고슴도치 클래스에서 알아서 함
			}
			else
			{
				// m_dwNoCollision 동안은 부딪혀도 다치지 않음.
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

					m_bIsHurting = true;
					m_bIsRolling = false;
					m_bIsDangling = false;
				}
			}
		}

		else
		{
			// m_dwNoCollision 동안은 부딪혀도 다치지 않음.
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

				m_bIsHurting = true;
				m_bIsRolling = false;
				m_bIsDangling = false;
			}
		}
	}


	if (Is_Counter_One_Of(CFly))
	{
		CFly* pFly = static_cast<CFly*>(pCounterObj);
		CFly::STATE eState = pFly->Get_State();

		if (eState == CFly::STATE::BOMB)
		{
			// m_dwNoCollision 동안은 부딪혀도 다치지 않음.
			if (m_dwNoCollision + 2000 < GetTickCount())
			{
				m_iHp -= 10;

				m_dwNoCollision = GetTickCount();

				m_bIsJump = true;
				m_fJumpPower = -10.f;
				m_fDeltaTime = 0.f;

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

				m_bIsHurting = true;
				m_bIsRolling = false;
				m_bIsDangling = false;
			}
		}
		else if (m_bIsJump && m_tInfo.fY < pCounterObj->Get_Info().fY)
		{
			m_bIsJump = true;
			m_fJumpPower = -10.f;
			m_fDeltaTime = 0.f;

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

			if ((eState == CFly::STATE::IDLE || eState == CFly::STATE::IDLE_LEFT))
			{
				pFly->Bombing();
			}
		}
		else
		{
			// m_dwNoCollision 동안은 부딪혀도 다치지 않음.
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

				m_bIsHurting = true;
				m_bIsRolling = false;
				m_bIsDangling = false;
			}
		}
	}

	if (Is_Counter_One_Of(CHyena))
	{
		CHyena* pHyena = static_cast<CHyena*>(pCounterObj);
		CHyena::STATE eState = pHyena->Get_State();

		if (m_bIsJump && m_tRect.bottom < pCounterObj->Get_Info().fY &&
			(eState == CHyena::STATE::TIRED || eState == CHyena::STATE::TIRED_LEFT))
		{
			m_bIsJump = true;
			m_fJumpPower = -10.f;
			m_fDeltaTime = 0.f;

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
			if (m_dwKill + 2000 < GetTickCount())
			{
				static_cast<CHyena*>(pCounterObj)->Get_Damage();
				m_dwKill = GetTickCount();
			}
		}
		else
		{
			// m_dwNoCollision 동안은 부딪혀도 다치지 않음.
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

				m_bIsHurting = true;
				m_bIsRolling = false;
				m_bIsDangling = false;
			}
		}
	}

	if (Is_Counter_One_Of(CItem))
	{
		int iTargetX = pCounterObj->Get_Info().fX;
		int iTargetY = pCounterObj->Get_Info().fY;

		if (iTargetX - 20 <= m_tInfo.fX && m_tInfo.fX <= iTargetX + 20 && iTargetY - 20 <= m_tInfo.fY && m_tInfo.fY <= iTargetY + 20)
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
				m_fSaving_X = pCounterObj->Get_Info().fX;
				m_fSaving_Y = pCounterObj->Get_Info().fY;
				break;
			}
		}
	}

	if (Is_Counter_One_Of(CVertex))
	{
		if (!m_bIsDangling && !m_bIsHurting)
		{
			float fTargetX = pCounterObj->Get_Info().fX;
			float fTargetY = pCounterObj->Get_Info().fY;

			if (m_bIsJump
				&& fTargetX - 10 <= m_tInfo.fX && m_tInfo.fX <= fTargetX + 10
				&& fTargetY - 10 <= m_tInfo.fY && m_tInfo.fY <= fTargetY + 10)
			{
				CVertex::DIR eDir = static_cast<CVertex*>(pCounterObj)->Get_Dir();

				if (m_bIsRightDir && eDir == CVertex::L)
				{
					m_pFrameKey = L"PLAYER_GRABBING_LEDGE_FIRST";
					m_eNextState = GRABBING_LEDGE_FIRST;

					m_tInfo.fX = fTargetX;
					m_tInfo.fY = fTargetY;

					m_bIsDangling = true;
					m_bIsJump = false;

					m_fJumpPower = 0.f;
					m_fDeltaTime = 0.f;
				}

				else if (!m_bIsRightDir && eDir == CVertex::R)
				{
					m_pFrameKey = L"PLAYER_GRABBING_LEDGE_FIRST_LEFT";
					m_eNextState = GRABBING_LEDGE_FIRST_LEFT;

					m_bIsDangling = true;
					m_bIsJump = false;

					m_tInfo.fX = fTargetX;
					m_tInfo.fY = fTargetY;
					m_fJumpPower = 0.f;
					m_fDeltaTime = 0.f;
				}
			}
		}
	}

	if (Is_Counter_One_Of(CBlock))
	{
		if (m_eCurState == STANDING_JUMP
			|| m_eCurState == STANDING_JUMP_LEFT)
		{
			if (pCounterObj->Get_Rect().top - 10 <= m_tInfo.fY
				&& m_tInfo.fY <= pCounterObj->Get_Rect().bottom)
			{
				if (!m_bIsBlockCollision)
				{
					m_fJumpPower = 0.f;
					m_fDeltaTime = 0.f;
					m_bIsBlockCollision = true;
				}
			}
		}
	}

	if (Is_Counter_One_Of(CVerticalBlocck))
	{
		RECT rc = {};
		IntersectRect(&rc, &m_tRect, &pCounterObj->Get_Rect());
		if (m_tInfo.fX < pCounterObj->Get_Info().fX)
		{
			this->Set_Pos(m_tInfo.fX - (rc.right - rc.left), m_tInfo.fY);
		}
		else
		{
			this->Set_Pos(m_tInfo.fX + (rc.right - rc.left), m_tInfo.fY);
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
	m_fJumpPower = 0.f;
	m_fDeltaTime = 0.f;
}
