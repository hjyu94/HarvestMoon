#include "stdafx.h"
#include "HedgeHog.h"
#include "Player.h"
#include "LineMgr.h"

CHedgeHog::CHedgeHog()
{
}


CHedgeHog::~CHedgeHog()
{
}

void CHedgeHog::Initialize()
{
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HedgeHog_IDLE.bmp", L"HedgeHog_IDLE");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HedgeHog_IDLE_LEFT.bmp", L"HedgeHog_IDLE_LEFT");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HedgeHog_UPSIDE_DOWN.bmp", L"HedgeHog_UPSIDE_DOWN");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HedgeHog_UPSIDE_DOWN_LEFT.bmp", L"HedgeHog_UPSIDE_DOWN_LEFT");

	m_pFrameKey = L"HedgeHog_IDLE";

	m_fMoveDistance = 100.f;
	m_fSpeed = 0.000000000005f;

	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 50.f;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart_X = 0;
	m_tFrame.iFrameEnd_X = 6;
	m_tFrame.iFrameStart_Y = 0;

	m_bIsRightDir = true;
	m_bIsUpsidedown = false;
	m_bIsStop = false;
	m_bIsJump = true;
	m_bIsDead = false;

	m_fSpeed = 5.f;
	m_fDeltaTime = 0.f;
	m_fVelY = 0.f;
	m_fJumpPower = 10.f;
	
	m_dwWalking = GetTickCount();
	m_dwUpsidedown = GetTickCount();
	m_dwWalking2 = GetTickCount(); // õõ�� �ɾ���� ����
	
	fRandTime = rand() % 2000 + 4500;
}

int CHedgeHog::Update()
{
	// �¿�� �����϶� �����̴� ������ �߰���ǥ
	if (!m_bIsInit)
	{
		m_Center_fx = m_tInfo.fX;
		m_Center_fy = m_tInfo.fY;

		float fY_On_Line = 0.f;
		CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fY_On_Line);
		m_tInfo.fY = fY_On_Line;

		m_bIsInit = true;
	}

	if (m_bIsDead)
	{
		return OBJ_DEAD;
	}

	float fy = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fy);

	// �̵� ���� ������ ���� �ٲٱ�
	if (m_tInfo.fX - m_Center_fx > m_fMoveDistance)
	{
		m_fSpeed *= -1;
		m_pFrameKey = L"HedgeHog_IDLE_LEFT";
		m_eNextState = IDLE_LEFT;
		m_bIsRightDir = false;
	}
	else if (m_tInfo.fX - m_Center_fx < -m_fMoveDistance)
	{
		m_fSpeed *= -1;
		m_pFrameKey = L"HedgeHog_IDLE";
		m_eNextState = IDLE;
		m_bIsRightDir = true;
	}


	// ���� ���� ��� ��Ȳ�� �ٲ�
	if (!m_bIsDying)
	{
		// ������ ���¿��� 10�ʰ� ������
		if (m_bIsUpsidedown)
		{
			if (m_dwUpsidedown + 10000 < GetTickCount())
			{
				m_bIsUpsidedown = false;
				Back_To_Idle();
				m_dwUpsidedown = GetTickCount();
			}
		}
		// �������� ���� �����̸�
		else
		{
			// 0~1500: �ȱ�, 1500~5000: ����(3.5�ʰ� ����)
			if (m_dwWalking + fRandTime < GetTickCount())
			{
				m_bIsStop = true;
			}

			if (m_dwWalking + fRandTime + 3500 < GetTickCount())
			{
				m_dwWalking = GetTickCount();
				m_bIsStop = false;
			}

			// ���ƴٳ�� �Ѵ�.
			if (!m_bIsStop)
			{
				if (m_dwWalking2 + 100 < GetTickCount())
				{
					m_tInfo.fX += m_fSpeed;
					m_dwWalking2 = GetTickCount();
					/*srand(unsigned(time(0)));
					fRandTime = rand() % 2000 + 4500;*/
				}
			}
		}
	}

	if(!m_bIsDying)
		IsJumping();
	else
		CHedgeHog::IsDying();
	
	CObj::UpdateRect();
	StateChange();
	FrameMove();
	return OBJ_NOEVENT;
}

void CHedgeHog::LateUpdate()
{
}

void CHedgeHog::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_ScrollX();
	float iScrollY = CScrollMgr::Get_ScrollY();

	// ġƮŰ
	if (CKeyMgr::Get_Instance()->KeyPressing('M'))
	{
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Rectangle(hDC, m_tRect.left - iScrollX, m_tRect.top + iScrollY, m_tRect.right - iScrollX, m_tRect.bottom + iScrollY);
	}

	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

	if (!m_bIsUpsidedown)
	{
		GdiTransparentBlt(hDC, // ���� ������� DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //��µ� ��ġ�� xy ��ǥ 
			m_tInfo.fCX, m_tInfo.fCY, // ����� ��Ʈ���� ���μ��� ������. 
			hMemDC,
			m_tInfo.fCX * m_tFrame.iFrameStart_X,
			m_tInfo.fCY* m_tFrame.iFrameStart_Y, // ���� ��ġ 
			m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
			RGB(255, 255, 255)
		);
	}
	else
	{
		GdiTransparentBlt(hDC, // ���� ������� DC
			m_tRect.left - iScrollX, m_tRect.top + iScrollY, //��µ� ��ġ�� xy ��ǥ 
			m_tInfo.fCX, m_tInfo.fCY, // ����� ��Ʈ���� ���μ��� ������. 
			hMemDC,
			0,0,// ���� ��ġ 
			m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
			RGB(255, 255, 255)
		);
	}

	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		Ellipse(hDC, m_tInfo.fX - 5 - iScrollX, m_tInfo.fY - 5 + iScrollY, m_tInfo.fX + 5 - iScrollX, m_tInfo.fY + 5 + iScrollY);
	}
}

void CHedgeHog::Release()
{
}

void CHedgeHog::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		if (!m_bIsStop)
		{
			++m_tFrame.iFrameStart_X;
		}
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart_X >= m_tFrame.iFrameEnd_X)
	{
		m_tFrame.iFrameStart_X = 0;
		m_bMotionEnd = true;
	}
}

void CHedgeHog::StateChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::IDLE:
		case STATE::IDLE_LEFT:
			m_tInfo.fCX = 70.f;
			m_tInfo.fCY = 50.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 6;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case STATE::UPSIDE_DOWN:
		case STATE::UPSIDE_DOWN_LEFT:
			/*m_tInfo.fCX = 80.f;
			m_tInfo.fCY = 75.f;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 10;
			m_tFrame.iFrameStart_Y = 0;*/
			break;
		}

		m_eCurState = m_eNextState;
	}
}

void CHedgeHog::Collision_Proc(CObj * pCounterObj)
{
	if (Is_Counter_One_Of(CPlayer))
	{
		if (m_bIsUpsidedown)
		{
			if (static_cast<CPlayer*>(pCounterObj)->Get_CurState() == CPlayer::STANDING_JUMP
				|| static_cast<CPlayer*>(pCounterObj)->Get_CurState() == CPlayer::STANDING_JUMP_LEFT)
			{
				if (pCounterObj->Get_Rect().bottom < m_tInfo.fY)
				{
					if (!m_bIsDying)
					{
						m_bIsDying = true;
						m_fJumpPower = -8.f;
					}
				}
			}
			else if (static_cast<CPlayer*>(pCounterObj)->Get_CurState() == CPlayer::ROLLING
				|| static_cast<CPlayer*>(pCounterObj)->Get_CurState() == CPlayer::ROLLING_LEFT)
			{
				if (!m_bIsDying)
				{
					m_bIsDying = true;
					m_fJumpPower = -8.f;
				}
			}
		}
		
	}
}

void CHedgeHog::Upside_Down()
{
	if (!m_bIsUpsidedown)
	{
		if (m_bIsRightDir)
		{
			m_pFrameKey = L"HedgeHog_UPSIDE_DOWN";
			m_eNextState = UPSIDE_DOWN;
		}
		else
		{
			m_pFrameKey = L"HedgeHog_UPSIDE_DOWN_LEFT";
			m_eNextState = UPSIDE_DOWN_LEFT;
		}

		m_bIsUpsidedown = true;
		m_bIsJump = true;
		m_fJumpPower = -10.f;
		m_dwUpsidedown = GetTickCount();
	}
}

void CHedgeHog::IsDying()
{
	float fy = 0.f;
	bool bIsColl = CLineMgr::Get_Instance()->LineCollision(m_tInfo.fX, m_tInfo.fY, &fy);

	if (m_bIsDying)
	{
		// ���� �� ��������(m_fJumpPower�� �������ٰ� ����� �Ǹ鼭 ���� ������ ��ž)
		m_fVelY = m_fDeltaTime + m_fJumpPower;
		m_tInfo.fY += m_fVelY;
		m_fDeltaTime += 0.5f;

		if (m_tInfo.fY > fy)
		{
			m_bIsDead = true;
		}
	}
}

void CHedgeHog::Back_To_Idle()
{
	int i = 0;
	if (m_bIsRightDir)
	{
		m_pFrameKey = L"HedgeHog_IDLE";
		m_eNextState = IDLE;
	}
	else
	{
		m_pFrameKey = L"HedgeHog_IDLE_LEFT";
		m_eNextState = IDLE_LEFT;
	}
}
