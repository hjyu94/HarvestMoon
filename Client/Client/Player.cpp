// Rolling: �ƹ� Ű�� �� ����
// Roaring: �ƹ� Ű�� �� ����
// Hurting: �ƹ� Ű�� �� ����
// Danging: ����, ������, ����, �Ʒ���
// Jump: ����, ������

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
#include "Monkey.h"

#include "Item.h"
#include "Vertex.h"
#include "Block.h"
#include "VerticalBlocck.h"
#include "TailVertex.h"

#include "Line.h"

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
	//m_iMp = 30;
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

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_SWING.bmp", L"PLAYER_SWING");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Player/PLAYER_RIDING.bmp", L"PLAYER_RIDING");

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

	m_bIsSeeingDown = false;
	m_bIsSeeingUp = false;
	m_bIsScrollEffect = false;
	m_bIsBlockCollision = false;
	m_bIs_On_Another_Scene = false;
	m_bIsDangling_with_Rhino = false;
	m_bIsRolling_with_Monkey = false;
	m_bIsRiding_On_Ostrich = false;

	m_bIsTransparent = false;
	m_iTransparentCount = 0;

	m_dwUp = GetTickCount();
	m_dwDown = GetTickCount();

	m_eNextState = STANDING_LAND;
	m_pFrameKey = L"PLAYER_STANDING_LAND";

	m_dwKill = GetTickCount();
	m_dwDangling_with_Rhino = GetTickCount();
	m_dwMonkeyCoolTime = GetTickCount();
	m_iJumpCount = 0;
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
		IsRiding();
	}

	if (m_bIs_On_Another_Scene)
	{
		Is_On_Another_Scene();
	}

	SceneChange();
	FrameMove();

	// ġƮŰ: ���� �������� ���� ó������ �ǵ���
	if (CKeyMgr::Get_Instance()->KeyDown(VK_F1))
	{
		m_bIsDangling = false;
		m_bIsHurting = false;
		m_bIsRoaring = false;
		m_bIsRolling = false;
		m_bIsJump = false;
	}

	// ġƮŰ: ���� ������ ������
	if (CKeyMgr::Get_Instance()->KeyDown(VK_F7))
	{
		if (m_iCurStage == 1)
		{
			m_tInfo.fX = 2200.f;
			m_tInfo.fY = -2000.f;
			CScrollMgr::Reset_Scroll();
			CScrollMgr::Sum_ScrollX(1900.f);
			CScrollMgr::Sum_ScrollY(2200.f);
		}
		else if (m_iCurStage == 2)
		{

		}
	}

	// ġƮŰ
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_F4))
	{
		iLife = 1;
	}

	if (CKeyMgr::Get_Instance()->KeyPressing(VK_F6))
	{
		iLife = 4;
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

	if ((m_iHp <= 0 && !m_bIs_On_Another_Scene)
		/*|| (CSceneMgr::Get_Instance()->Get_SCENEID() == CSceneMgr::SCENE_STAGE_2
			&& m_tRect.bottom<=0 && CScrollMgr::Get_ScrollY() == 0)*/)
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


	// ġƮŰ : �浹�ϴ� Rect ���
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
		else
		{
			GdiTransparentBlt(hDC, // ���� ������� DC
				m_tRect.left, m_tRect.top, //��µ� ��ġ�� xy ��ǥ 
				m_tInfo.fCX, m_tInfo.fCY, // ����� ��Ʈ���� ���μ��� ������. 
				hMemDC,
				m_tInfo.fCX * (m_tFrame.iFrameEnd_X - m_tFrame.iFrameStart_X - 1),
				m_tInfo.fCY* m_tFrame.iFrameStart_Y, // ���� ��ġ 
				m_tInfo.fCX, m_tInfo.fCY,// ����� ��Ʈ���� ��ü ���μ��� ����. 
				RGB(0, 0, 0)
			);
		}


	}
	// ��¦�̴� ȿ��
	else if (m_bIsHurting)
	{
		if (m_iTransparentCount % 4 == 0)
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
	}
	else
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

	// ġƮŰ : �浹�ϴ� Rect ���
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

	if(!m_bIsDangling && !m_bIsDangling_with_Rhino)
		if (fabs(m_tInfo.fY - fy) > 30.f) 
			m_bIsJump = true;

	if (!m_bIsDangling && !m_bIsDangling_with_Rhino)
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
				m_bIsRolling = false;

				m_fDeltaTime = 0.f;
				m_fJumpPower = 0.f;
				m_tInfo.fY = fy;
				
 				m_bIsRolling_with_Monkey = false;
				m_bIsBlockCollision = false;
				m_iJumpCount = 0;

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
		CSoundMgr::Get_Instance()->PlaySound(L"PLAYER_HURT.MP3", CSoundMgr::PLAYER);
	
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

	if (m_bIsRolling_with_Monkey)
	{
		if (iOffsetX + 60 < m_tInfo.fX - iScrollX)
			CScrollMgr::Sum_ScrollX(+18);
		if (iOffsetX - 60 > m_tInfo.fX - iScrollX)
			CScrollMgr::Sum_ScrollX(-18);
	}
	else
	{
		if (iOffsetX + 60 < m_tInfo.fX - iScrollX)
			CScrollMgr::Sum_ScrollX(+m_fSpeed);
		if (iOffsetX - 60 > m_tInfo.fX - iScrollX)
			CScrollMgr::Sum_ScrollX(-m_fSpeed);
	}

	if (iOffsetY - 100 > m_tInfo.fY + iScrollY)
		CScrollMgr::Sum_ScrollY(m_fSpeed);
	if (iOffsetY + 100 < m_tInfo.fY + iScrollY)
		CScrollMgr::Sum_ScrollY(-m_fSpeed);

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

void CPlayer::IsRiding()
{
	if (m_bIsRiding_On_Ostrich)
	{
		m_tInfo.fX += 5.f;
		
		if (m_tInfo.fY > 400)
		{
			Set_Hp(0);
		}
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

		float fTheta = atan2(fDeltaY, fDeltaX); // ȣ����

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
		CSoundMgr::Get_Instance()->PlaySound(L"PLAYER_ROARING.MP3", CSoundMgr::PLAYER);

		if (m_iMp > 30)
		{
			OBJLIST listMonster = CObjMgr::Get_Instance()->Get_OBJLIST(OBJID::MONSTER);
			for (auto& pMonster : listMonster)
			{
				// ���� �ݰ� ���� �ִ� ������
				if (pMonster->Is_Inside(m_tRect.left - 150, m_tRect.top - 50, m_tRect.right + 150, m_tRect.bottom + 50))
				{
					// ����ġ�� ��������.
					// ������ ����� ���̸� ������. �̹� ������ ��� ������ ����.
					if (!static_cast<CHedgeHog*>(pMonster)->Get_UpsideState())
					{
						static_cast<CHedgeHog*>(pMonster)->Upside_Down();
					}
					else
					{
						pMonster->Set_Stun();
					}

					// ��ũ �����̴� �¿찡 �ٲ��.
					if (m_dwMonkeyCoolTime + 1500 < GetTickCount())
					{
						if (dynamic_cast<CMonkey*>(pMonster) != nullptr)
						{
							CMonkey* pMonkey = dynamic_cast<CMonkey*>(pMonster);
							if (pMonkey->Get_Color() == CMonkey::C_PINK)
							{
								m_dwMonkeyCoolTime = GetTickCount();
								pMonkey->Turn_Around();
							}
						}
					}
				}
			}
		}
	}
}

void CPlayer::IsRolling()
{
	 if (m_bIsRolling_with_Monkey)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"PLAYER_ROLLING.MP3.MP3", CSoundMgr::PLAYER);

		if (m_eCurState == ROLLING)
	 		m_tInfo.fX += 15.f;
		else if (m_eCurState == ROLLING_LEFT)
			m_tInfo.fX -= 15.f;
	}
	else if (m_bIsRolling)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"PLAYER_ROLLING.MP3.MP3", CSoundMgr::PLAYER);

		if (m_eCurState == ROLLING)
			m_tInfo.fX += m_fSpeed ;
		else if (m_eCurState == ROLLING_LEFT)
			m_tInfo.fX -= m_fSpeed;
	}

}

void CPlayer::KeyCheck()
{
	if (m_eNextState == STANDING_JUMP
		|| m_eNextState == STANDING_JUMP_LEFT)
	{
		// �ٴ� ���� ��� �����̳� ������ Ű�� �Դ´�.
		// ����� �޸��Ⱑ �ƴ϶� ���� ���¸� �����ϸ� ���⸸ �ٲ��.
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

	if (m_bIsRiding_On_Ostrich)
	{
		// �Ʒ� Ű�� �� Ű�� �Դ´�
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_DOWN))
		{
			if (!m_bIsJump)
			{
				m_pFrameKey = L"PLAYER_DOWN";
				m_eNextState = DOWN;
			}
		}
		else if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE) && m_iJumpCount < 2)
		{
			m_iJumpCount++;
			m_bIsJump = true;
			m_fJumpPower = -16.f;
			m_fDeltaTime = 0.f;
			m_eNextState = STANDING_JUMP;
			m_pFrameKey = L"PLAYER_STANDING_JUMP";
		}
		else
		{
			if (!m_bIsJump)
			{
				m_eNextState = RIDING;
				m_pFrameKey = L"PLAYER_RIDING";
			}
		}
	}
	else if (m_bIsDangling)
	{
		if (m_bIsRightDir) // �������� ���� �ִ� ���, �Ʒ�Ű�� ������ Ű�� �Դ´�
		{
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RIGHT))
			{
				//m_tInfo.fX += 40.f;
				m_pFrameKey = L"PLAYER_CLIMBING_LEDGE";
				m_eNextState = CPlayer::CLIMBING_LEDGE;
				m_tInfo.fY += 50.f; // �ִϸ��̼� ȿ�������� �� �Ʒ��� �׸��� ����
									// m_bIsDangling = false; // ��� ������ false�� �ٲ��� ���⼭ ����
				m_tInfo.fX += 10.f;
			}
		}

		else if (!m_bIsRightDir) // ������ ���� �ִ� ���, �Ʒ�Ű�� ���� Ű�� �Դ´�
		{
			if (CKeyMgr::Get_Instance()->KeyDown(VK_LEFT))
			{
				m_pFrameKey = L"PLAYER_CLIMBING_LEDGE_LEFT";
				m_eNextState = CPlayer::CLIMBING_LEDGE_LEFT;
				m_tInfo.fY += 50.f; // �ִϸ��̼� ȿ�������� �� �Ʒ��� �׸��� ����
									// m_bIsDangling = false; // ��� ������ false�� �ٲ��� ���⼭ ����
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

	// �ڻԼ� ������ �Ŵ޷� �ִ� ���
	else if (m_bIsDangling_with_Rhino)
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE))
		{
			m_bIsDangling_with_Rhino = false;

			m_dwDangling_with_Rhino = GetTickCount();

			if (m_tFrame.iFrameStart_X <= 2)
			{
				m_fJumpPower = 0.f;
			}
			else if (m_tFrame.iFrameStart_X <= 7)
			{
				m_fJumpPower = -12.f;
			}
			else
			{
				m_fJumpPower = 0.f;
			}

			//m_fJumpPower = -15.f;
			m_fDeltaTime = 0.f;

			// �������� ���� ���������� ����
			if (m_tFrame.iFrameStart_X <= 3)
			{
				m_eNextState = ROLLING_LEFT;
				m_pFrameKey = L"PLAYER_ROLLING_LEFT";
			}
			else if(m_tFrame.iFrameStart_X <= 7)
			{
				m_eNextState = ROLLING;
				m_pFrameKey = L"PLAYER_ROLLING";
			}
			else
			{
				m_eNextState = ROLLING_LEFT;
				m_pFrameKey = L"PLAYER_ROLLING_LEFT";
			}

			m_bIsRolling = true;
			m_bIsJump = true;
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
		// �Ʒ��� ���� ���� �ִٰ� Ű�� ���� IDLE�� ���ƿ´�.
		// ��ũ�� ���� �ٲ� ���� �ٽ� �������´�.                            
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

		// ������ �� ������ �޸���.
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		{
			m_pFrameKey = L"PLAYER_RUNNING_LEFT";
			m_eNextState = RUNNING_LEFT;
			m_bIsRightDir = false;
			m_tInfo.fX -= m_fSpeed;
		}

		// �������� �� ������ �޸���.
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		{
			m_pFrameKey = L"PLAYER_RUNNING";
			m_eNextState = RUNNING;
			m_bIsRightDir = true;
			m_tInfo.fX += m_fSpeed;
		}

		if (m_bIsRightDir) // �������� ���� ���� ��
		{
			// ¢�� ���� �ƴҶ��� ¢�� �� �ִ�
			// ¢�� �߿� �� ¢�� �� ����.
			// MP 10 �Ҹ�
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

		else if (!m_bIsRightDir) // ������ ���� ���� ��
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

		// ��+�Ʒ� -> �������� ������
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT) && CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
		{
			m_pFrameKey = L"PLAYER_ROLLING_LEFT";
			m_eNextState = ROLLING_LEFT;
			m_bIsRightDir = false;
			m_bIsRolling = true;
		}

		// ��+�Ʒ� -> ���������� ������
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT) && CKeyMgr::Get_Instance()->KeyDown(VK_DOWN))
		{
			m_pFrameKey = L"PLAYER_ROLLING";
			m_eNextState = ROLLING;
			m_bIsRightDir = true;
			m_bIsRolling = true;
		}

		//## �����̳� �����ʿ� ���õ� Ű ó��
		// ���� ������ �� �� IDLE
		if (CKeyMgr::Get_Instance()->KeyUP(VK_LEFT))
		{
			m_pFrameKey = L"PLAYER_IDLE_LEFT";
			m_eNextState = IDLE_LEFT;
			m_bIsRightDir = false;
		}

		// ������ ������ �� �� IDLE
		if (CKeyMgr::Get_Instance()->KeyUP(VK_RIGHT))
		{
			m_pFrameKey = L"PLAYER_IDLE";
			m_eNextState = IDLE;
			m_bIsRightDir = true;
		}

		// �����̽��ٸ� �ٿ� ������ �� ���� �ڴ�.
		// ��մ�� �Ŵ޷� ������ �ٸ� �ȵ�
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_SPACE))
		{
			// ó�� �ӵ��� -12.f
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
			break;

		case CPlayer::SWING:
			m_tInfo.fCX = 280.f;
			m_tInfo.fCY = 240.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 11;
			m_tFrame.iFrameStart_Y = 0;
			break;

		case CPlayer::RIDING:
			m_tInfo.fCX = 108.f;
			m_tInfo.fCY = 78.f;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart_X = 0;
			m_tFrame.iFrameEnd_X = 4;
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
		// �ٸ� Scene�� �ִ� ���(���� ���) stage scene���� ���ƿ���
		// ����� 0���� ���� ���� �ٽ� �����Ұ��� ���� scene���� �̵�
		if (m_bIs_On_Another_Scene)
		{
			if (iLife>0)
			{
				if (m_iCurStage == 1)
				{


					CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE);

					if (CObjMgr::Get_Instance()->m_bIsSaved)
					{
						float fSavingX = CObjMgr::Get_Instance()->m_fSaving_X;
						float fSavingY = CObjMgr::Get_Instance()->m_fSaving_Y;

						this->Initialize();
						this->Set_Pos(fSavingX, fSavingY);
						CScrollMgr::Reset_Scroll();
						CScrollMgr::Sum_ScrollX(fSavingX - 130);
						CScrollMgr::Sum_ScrollY(-fSavingY + 340);
					}
					else
					{
						this->Initialize();
						this->Set_Pos(130.f, 340.f);
						CScrollMgr::Reset_Scroll();
					}
					m_eNextState = STANDING_LAND;
					m_pFrameKey = L"PLAYER_STANDING_LAND";
				}

				else if (m_iCurStage == 2)
				{
					CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_STAGE_2);
					if (CObjMgr::Get_Instance()->m_bIsSaved)
					{
						float fSavingX = CObjMgr::Get_Instance()->m_fSaving_X;
						float fSavingY = CObjMgr::Get_Instance()->m_fSaving_Y;

						this->Initialize();
						this->Set_Pos(fSavingX, fSavingY);
						CScrollMgr::Reset_Scroll();
						CScrollMgr::Sum_ScrollX(fSavingX - 200);
						//CScrollMgr::Sum_ScrollY(-fSavingY + 200);
					}
					else
					{
						this->Initialize();
						this->Set_Pos(130.f, 340.f);
						CScrollMgr::Reset_Scroll();
					}

					m_eNextState = STANDING_LAND;
					m_pFrameKey = L"PLAYER_STANDING_LAND";
				}

			}
			else
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENEID::SCENE_RESTART);
			}
		}

		// ���� �Ʒ��� ���� ��� ���������� ������ ����
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

		// ledge�� ������ ��� �������� ��ǥ �̵�
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

			//// ���� �ణ Ƣ��
			//m_bIsJump = true;
			//m_fJumpPower = -10.f;
			//m_fDeltaTime = 0.f;

			m_bIsDangling = false;
		}

		// ������ ��쳪, ¢�� ���, ���Ϳ� �ε��� ���, ������ ���, �������� IDLE�� ��ü
		else if (m_bIsRolling)
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
			// m_dwNoCollision ������ �ε����� ��ġ�� ����.
			if (m_dwNoCollision + 2000 < GetTickCount())
			{
				m_iHp -= 10;
				m_dwNoCollision = GetTickCount();

				m_bIsJump = true;
				m_fJumpPower = -10.f;

				if (m_bIsRightDir) // �������� ���� �ִ� ���
				{
					m_pFrameKey = L"PLAYER_HURT";
					m_eNextState = HURT;
				}
				else // ������ ���� �ִ� ���
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
				// m_dwNoCollision ������ �ε����� ��ġ�� ����.
				if (m_dwNoCollision + 2000 < GetTickCount())
				{
					m_iHp -= 10;
					m_dwNoCollision = GetTickCount();

					m_bIsJump = true;
					m_fJumpPower = -10.f;
					m_fDeltaTime = 0.f;

						if (m_bIsRightDir) // �������� ���� �ִ� ���
						{
							m_pFrameKey = L"PLAYER_HURT";
							m_eNextState = HURT;
						}
						else // ������ ���� �ִ� ���
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
				// ����ġ Ŭ�������� �˾Ƽ� ��
			}
			else
			{
				// m_dwNoCollision ������ �ε����� ��ġ�� ����.
				if (m_dwNoCollision + 2000 < GetTickCount())
				{
					m_iHp -= 10;

					m_dwNoCollision = GetTickCount();

					m_bIsJump = true;
					m_fJumpPower = -10.f;

						if (m_bIsRightDir) // �������� ���� �ִ� ���
						{
							m_pFrameKey = L"PLAYER_HURT";
							m_eNextState = HURT;
						}
						else // ������ ���� �ִ� ���
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
			// m_dwNoCollision ������ �ε����� ��ġ�� ����.
			if (m_dwNoCollision + 2000 < GetTickCount())
			{
				m_iHp -= 10;

				m_dwNoCollision = GetTickCount();

				m_bIsJump = true;
				m_fJumpPower = -10.f;

					if (m_bIsRightDir) // �������� ���� �ִ� ���
					{
						m_pFrameKey = L"PLAYER_HURT";
						m_eNextState = HURT;
					}
					else // ������ ���� �ִ� ���
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
			// m_dwNoCollision ������ �ε����� ��ġ�� ����.
			if (m_dwNoCollision + 2000 < GetTickCount())
			{
				m_iHp -= 10;

				m_dwNoCollision = GetTickCount();

				m_bIsJump = true;
				m_fJumpPower = -10.f;
				m_fDeltaTime = 0.f;

					if (m_bIsRightDir) // �������� ���� �ִ� ���
					{
						m_pFrameKey = L"PLAYER_HURT";
						m_eNextState = HURT;
					}
					else // ������ ���� �ִ� ���
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
			// m_dwNoCollision ������ �ε����� ��ġ�� ����.
			if (m_dwNoCollision + 2000 < GetTickCount())
			{
				m_iHp -= 10;

				m_dwNoCollision = GetTickCount();

				m_bIsJump = true;
				m_fJumpPower = -10.f;

					if (m_bIsRightDir) // �������� ���� �ִ� ���
					{
						m_pFrameKey = L"PLAYER_HURT";
						m_eNextState = HURT;
					}
					else // ������ ���� �ִ� ���
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
			// m_dwNoCollision ������ �ε����� ��ġ�� ����.
			if (m_dwNoCollision + 2000 < GetTickCount())
			{
				m_iHp -= 10;
				m_dwNoCollision = GetTickCount();

				m_bIsJump = true;
				m_fJumpPower = -10.f;

				if (m_bIsRightDir) // �������� ���� �ִ� ���
				{
					m_pFrameKey = L"PLAYER_HURT";
					m_eNextState = HURT;
				}
				else // ������ ���� �ִ� ���
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
				CObjMgr::Get_Instance()->m_bIsSaved = true;
				CObjMgr::Get_Instance()->m_fSaving_X = pCounterObj->Get_Info().fX;
				CObjMgr::Get_Instance()->m_fSaving_Y = pCounterObj->Get_Info().fY;
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
		if (m_eCurState != DOWN) // Ostrich Ÿ ���� �� ���϶��
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

	if (Is_Counter_One_Of(CTailVertex))
	{
		if (m_dwDangling_with_Rhino + 3000 < GetTickCount())
		{
			float fTargetX = pCounterObj->Get_Info().fX;
			float fTargetY = pCounterObj->Get_Info().fY;
			/*
					if (fTargetX - 5 <= m_tInfo.fX && m_tInfo.fX <= fTargetX + 5
						&& fTargetY - 5 <= m_tInfo.fY && m_tInfo.fY <= fTargetY + 5)
					{*/
			m_tInfo.fX = pCounterObj->Get_Info().fX;
			m_tInfo.fY = pCounterObj->Get_Info().fY;
			m_eNextState = SWING;
			m_pFrameKey = L"PLAYER_SWING";
			m_bIsDangling_with_Rhino = true;
			//}
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
	//m_bIsJump = false;
	m_bIsRoaring = false;
	m_fJumpPower = 0.f;
	m_fDeltaTime = 0.f;
}

void CPlayer::Jump_with_Rhino()
{
	m_bIsJump = true;
	m_bIsRolling = false;
	m_fJumpPower = -25.f;
	m_fDeltaTime = 0.f;
}

void CPlayer::Rolling_Along_Giraffe(bool bIs_GiraffeDir_Right, RECT rcGiraffe)
{
	if (rcGiraffe.left <= m_tInfo.fX && m_tInfo.fX <= rcGiraffe.right)
	{
		m_bIsRolling = true;
		m_bIsJump = true;
		m_fJumpPower = 0.f;
		m_fDeltaTime = 0.f;
		if (m_bIsRightDir)
		{
			m_eNextState = ROLLING;
			m_pFrameKey = L"PLAYER_ROLLING";
		}
		else
		{
			m_eNextState = ROLLING_LEFT;
			m_pFrameKey = L"PLAYER_ROLLING_LEFT";
		}


		list<CLine*>& line_List = CLineMgr::Get_Instance()->Get_List();
		for (auto& iter = line_List.begin(); iter != line_List.end(); )
		{
			LINEINFO info = (*iter)->Get_LineInfo();
			if (info.tLeftPoint.fx <= m_tInfo.fX && m_tInfo.fX <= info.tRightPoint.fx && *iter)
			{
				delete *iter;
				*iter = nullptr;
				iter = line_List.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

void CPlayer::Rolling_With_Monkey(CPlayer::DIR eDIR)
{
	m_fJumpPower = 0.f;
	m_fDeltaTime = 0.f;

	switch (eDIR)
	{
	case CPlayer::D_LEFT:
		m_bIsRolling_with_Monkey = true;
		m_pFrameKey = L"PLAYER_ROLLING_LEFT";
		m_eNextState = ROLLING_LEFT;
		m_bIsRightDir = false;
		m_bIsJump = true;
		m_fJumpPower = -5.5f;
		m_fDeltaTime = 0.f;
		break;
	
	case CPlayer::D_RIGHT:
		m_bIsRolling_with_Monkey = true;
		m_pFrameKey = L"PLAYER_ROLLING";
		m_eNextState = ROLLING;
		m_bIsRightDir = true;
		m_bIsJump = true;
		m_fJumpPower = -8.f;
		m_fDeltaTime = 0.f;
		break;

	case CPlayer::D_DOWN:
		m_bIsRolling_with_Monkey = false;
		m_pFrameKey = L"PLAYER_ROLLING";
		m_eNextState = ROLLING;
		m_bIsJump = true;
		m_fJumpPower = 4.f;
		m_fDeltaTime = 0.f;
		break;

	case CPlayer::D_UP:
		m_bIsRolling_with_Monkey = false;
		m_pFrameKey = L"PLAYER_ROLLING";
		m_eNextState = ROLLING;
		m_bIsJump = true;
		m_fJumpPower = -15.f;
		m_fDeltaTime = 0.f;
		break;
	}

	m_bIsRolling = false;
}

void CPlayer::Riding_On_Ostrich()
{
	// �ѹ��� ����ǵ���
	if (!m_bIsRiding_On_Ostrich)
	{
		m_bIsRiding_On_Ostrich = true;
		m_eNextState = RIDING;
		m_pFrameKey = L"PLAYER_RIDING";
	}
}

void CPlayer::FinalShooting()
{
	m_bIsRiding_On_Ostrich = false;
	m_bIsJump = true;
	m_fJumpPower = -15.f;
	m_fDeltaTime = 0.f;
	m_bIsRolling_with_Monkey = true;
	m_eNextState = ROLLING;
	m_pFrameKey = L"PLAYER_ROLLING";
}