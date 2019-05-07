#include "stdafx.h"
#include "Hyena.h"
#include "LineMgr.h"
#include "VerticalBlocck.h"
#include "ObjMgr.h"
#include "Player.h"

CHyena::CHyena()
{
}


CHyena::~CHyena()
{
}

void CHyena::Initialize()
{
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_DIE.bmp", L"HYENA_DIE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_DIE_LEFT.bmp", L"HYENA_DIE_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_IDLE.bmp", L"HYENA_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_IDLE_LEFT.bmp", L"HYENA_IDLE_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_JUMP.bmp", L"HYENA_JUMP");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_JUMP_LEFT.bmp", L"HYENA_JUMP_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_ROARING.bmp", L"HYENA_ROARING");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_ROARING_LEFT.bmp", L"HYENA_ROARING_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_START.bmp", L"HYENA_START");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_TIRED.bmp", L"HYENA_TIRED");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HYENA_TIRED_LEFT.bmp", L"HYENA_TIRED_LEFT");

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"HyenaBGM.mp3");

	m_pFrameKey = L"HYENA_START";

	m_fMoveDistance = 300.f;
	m_fSpeed = 10.f;

	m_tInfo.fCX = 154.f;
	m_tInfo.fCY = 154.f;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 15;
	m_tFrame.iFrameStart_Y = 0;

	m_bIsRightDir = false;
	m_bIsJump = true;
	m_bIsStop = false;

	m_fSpeed = -3.f;
	m_fDeltaTime = 0.f;
	m_fVelY = 0.f;
	m_fJumpPower = 10.f;

	m_dwPattern = GetTickCount();
	m_bIsAlreadyColl = false;

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	m_bIsTired = false;

	m_iHp = 3;
}

int CHyena::Update()
{
	if (!m_bIsInit)
	{
		// 0초~1초 그냥 등장
		if (m_dwPattern + 1000 > GetTickCount())
		{

		}
		// 1초~2초 왼쪽으로 이동하면서 점프
		else if (m_dwPattern + 1500 > GetTickCount())
		{
			m_tInfo.fX -= 2.f;
			if (!m_bIsJump)
			{
				m_bIsJump = true;
				m_fJumpPower = -10.f;
				m_eNextState = JUMP_LEFT;
				m_pFrameKey = L"HYENA_JUMP_LEFT";
			}
		}
		else
		{
			m_bIsInit = true;
			m_Center_fx = WINCY - 300.f;
			m_dwPattern = GetTickCount();
			m_fSpeed = 3.f;
		}
	}

	if (m_bIsInit && m_eCurState != DIE && m_eCurState != DIE_LEFT)
	{
		// 4초마다 한번씩 짖는다
		if (m_dwPattern + 4000 < GetTickCount())
		{
			m_dwPattern = GetTickCount();

			if (!m_bIsJump)
			{
				if (m_bIsRightDir)
				{
					m_eNextState = ROARING;
					m_pFrameKey = L"HYENA_ROARING";
				}
				else
				{
					m_eNextState = ROARING_LEFT;
					m_pFrameKey = L"HYENA_ROARING_LEFT";
				}
				m_bIsStop = true;
				m_bIsJump = false;
			}
		}


		// ##1 타겟이 있을 때
		if (nullptr != m_pTarget)
		{
			if (!m_bIsTired)
			{

				// 1) 플레이어가 있는 방향으로 움직임
				if (!m_bIsStop)
				{
					float fTargetX = m_pTarget->Get_Info().fX;
					float fTargetY = m_pTarget->Get_Info().fY;

					float fDeltaX = fTargetX - m_tInfo.fX;
					float fDeltaY = fTargetY - m_tInfo.fY;

					float fTheta = atan2(fDeltaY, fDeltaX); // 호도법

					m_tInfo.fX += m_fSpeed * cosf(fTheta);

					if (fTargetX > m_tInfo.fX)
					{
						m_eNextState = IDLE;
						m_pFrameKey = L"HYENA_IDLE";
					}
					else
					{
						m_eNextState = IDLE_LEFT;
						m_pFrameKey = L"HYENA_IDLE_LEFT";
					}
				}

				// 2) 플레이어가 뛰면 같이 뛴다.
				if (m_pTarget->Get_IsJumping()
					&& !m_pTarget->Get_IsHurt()
					&& !m_bIsJump
					&& (m_eCurState == IDLE || m_eCurState == IDLE_LEFT)
					)
				{
					m_bIsJump = true;
					m_bIsStop = false;
					m_fJumpPower = -15.f;

					if (m_bIsRightDir)
					{
						m_eNextState = JUMP;
						m_pFrameKey = L"HYENA_JUMP";
					}
					else
					{
						m_eNextState = JUMP_LEFT;
						m_pFrameKey = L"HYENA_JUMP_LEFT";
					}
				}
			}
		}

		// ##2 타겟이 없을 때
		else if (nullptr == m_pTarget)
		{

		}
	}

	CObj::UpdateRect();
	TargetCheck();
	PosLock();
	CHyena::IsJumping();
	StateChange();
	FrameMove();	

	return 0;
}

void CHyena::LateUpdate()
{
	m_bIsAlreadyColl = false;
}

void CHyena::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();

	// 치트키
	if (CKeyMgr::Get_Instance()->KeyPressing('M'))
	{
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, // 실제 복사받을 DC
		m_tRect.left - iScrollX, m_tRect.top + iScrollY, //출력될 위치의 xy 좌표 
		m_tInfo.fCX, m_tInfo.fCY, // 출력할 비트맵의 가로세로 사이즈. 
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart_X,
		m_tInfo.fCY* m_tFrame.iFrameStart_Y, // 시작 위치 
		m_tInfo.fCX, m_tInfo.fCY,// 출력할 비트맵의 전체 가로세로 길이. 
		RGB(255, 255, 255)
	);

	// 치트키
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Ellipse(hDC, m_tInfo.fX - 5 - iScrollX, m_tInfo.fY - 5 + iScrollY, m_tInfo.fX + 5 - iScrollX, m_tInfo.fY + 5 + iScrollY);
	}

}

void CHyena::Release()
{
}

void CHyena::PosLock()
{
	if (m_tInfo.fX <= 2400) m_tInfo.fX = 2400.f;
	if (m_tInfo.fX >= 2930) m_tInfo.fX = 2930.f;
}

void CHyena::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::START:
			m_tInfo.fCX = 154.f;
			m_tInfo.fCY = 154.f;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 15;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::IDLE:
		case STATE::IDLE_LEFT:
			m_tInfo.fCX = 170.f;
			m_tInfo.fCY = 108.f;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 11;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::DIE:
		case STATE::DIE_LEFT:
			m_tInfo.fCX = 172.f;
			m_tInfo.fCY = 128.f;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 10;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::JUMP:
		case STATE::JUMP_LEFT:
			m_tInfo.fCX = 168.f;
			m_tInfo.fCY = 150.f;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 14;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::ROARING:
		case STATE::ROARING_LEFT:
			CSoundMgr::Get_Instance()->PlaySound(L"HYENA_ROARING.MP3", CSoundMgr::MONSTER);
			m_tInfo.fCX = 140.f;
			m_tInfo.fCY = 106.f;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 15;
			m_tFrame.iFrameStart_Y = 0;
			m_bIsStop = true;
			break;

		case STATE::TIRED:
		case STATE::TIRED_LEFT:
			m_bIsTired = true;
			m_tInfo.fCX = 158.f;
			m_tInfo.fCY = 102.f;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 8;
			m_tFrame.iFrameStart_Y = 0;
			break;
		}

		m_eCurState = m_eNextState;
	}
}

void CHyena::IsJumping()
{
	float fy_On_Line = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fy_On_Line);

	if (fabs(m_tInfo.fY+30 - fy_On_Line) > 10.f) m_bIsJump = true;

	if (m_bIsJump)
	{
		m_fVelY = m_fDeltaTime + m_fJumpPower;
		m_tInfo.fY += m_fVelY;
		m_fDeltaTime += 0.5f;

		if (m_tInfo.fY+30 >= fy_On_Line)
		{
			m_bIsJump = false;
			m_fDeltaTime = 0.f;
			m_fJumpPower = 0.f;
			m_tInfo.fY = fy_On_Line - 30;

			if (m_bIsRightDir)
			{
				m_eNextState = TIRED;
				m_pFrameKey = L"HYENA_TIRED";
			}
			else
			{
				m_eNextState = TIRED_LEFT;
				m_pFrameKey = L"HYENA_TIRED_LEFT";
			}

			m_bIsStop = true;
			m_bIsTired = true;
		}
	}
}

CHyena::STATE CHyena::Get_State()
{
	return m_eCurState;
}

void CHyena::Collision_Proc(CObj * pCounterObj)
{
	/*if (!m_bIsAlreadyColl)
	{
		if (Is_Counter_One_Of(CVerticalBlocck))
		{
			m_fSpeed *= -1;

			if (m_bIsRightDir)
			{
				m_pFrameKey = L"HYENA_IDLE_LEFT";
				m_eNextState = IDLE_LEFT;
				m_bIsRightDir = false;
				m_tInfo.fX -= m_tRect.right - pCounterObj->Get_Rect().left;
				m_tInfo.fX -= 5.f;
			}
			else
			{
				m_pFrameKey = L"HYENA_IDLE";
				m_eNextState = IDLE;
				m_bIsRightDir = true;
				m_tInfo.fX += pCounterObj->Get_Rect().right - m_tRect.left;
				m_tInfo.fX += 5.f;
			}
		}
		m_bIsAlreadyColl = true;
	}*/
}

void CHyena::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart_X;
		m_tFrame.dwFrameTime = GetTickCount();
		
		if (m_eCurState == DIE || m_eCurState == DIE_LEFT)
		{
			if (m_tFrame.iFrameStart_X == m_tFrame.iFrameEnd_X - 1)
			{
				m_tFrame.dwFrameSpeed = 2000;
			}
			else
			{
				m_tFrame.dwFrameSpeed = 150;
			}
		}
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		// 지쳐하다가 다시 걸음
		// 짖다가 다시 걸음
		if (m_eCurState == ROARING 
			|| m_eCurState == ROARING_LEFT
			|| m_eCurState == TIRED
			|| m_eCurState == TIRED_LEFT)
		{
			if (m_bIsRightDir)
			{
				m_eNextState = IDLE;
				m_pFrameKey = L"HYENA_IDLE";
			}
			else
			{
				m_eNextState = IDLE_LEFT;
				m_pFrameKey = L"HYENA_IDLE_LEFT";
			}

			m_bIsStop = false;
			m_bIsTired = false;
		}

		else if (m_eCurState == DIE || m_eCurState == DIE_LEFT)
		{
			m_bIsDead = true;
		}

		m_tFrame.iFrameStart_X = 0;
	}
}

void CHyena::Get_Damage()
{
	--m_iHp;

	if (m_iHp <= 0)
	{
		if (m_bIsRightDir)
		{
			m_eNextState = DIE;
			m_pFrameKey = L"HYENA_DIE";
		}
		else
		{
			m_eNextState = DIE_LEFT;
			m_pFrameKey = L"HYENA_DIE_LEFT";
		}
	}
}

void CHyena::TargetCheck()
{
	CPlayer* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	RECT tMyViewRect = { m_tInfo.fX - 360, m_tInfo.fY - 133, m_tInfo.fX + 360, m_tInfo.fY + 133 };
	RECT tTempRect = {};
	
	if (IntersectRect(&tTempRect, &pPlayer->Get_Rect(), &tMyViewRect))
	{
		m_pTarget = pPlayer;
	}
	else
	{
		m_pTarget = nullptr;
	}
}

