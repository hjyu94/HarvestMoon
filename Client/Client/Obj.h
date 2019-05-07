#pragma once

#include "BitmapMgr.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	const INFO& Get_Info()const { return m_tInfo; }
	const RECT& Get_Rect()const { return m_tRect; }

public:
	virtual void Initialize() =0;
	virtual int  Update() =0;
	virtual void LateUpdate()= 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	void Set_Pos(float fx, float fy) 
	{
		m_tInfo.fX = fx; 
		m_tInfo.fY = fy; 
	}
	void Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void Set_Dead() { m_bIsDead = true; }
	void Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

public:
	void UpdateRect(); 
	virtual void FrameMove();
	virtual void IsJumping();
	virtual void LateInit(); 
	virtual void Collision_Proc(CObj* pCounterObj);
	bool Is_Inside(float left, float top, float right, float bottom);
	
	void Set_Stun();
	void IsStunning();

public:
	int Get_Hp() { return m_iHp; };
	int Get_Mp() { return m_iMp; };
	bool& Get_IsRightDir() { return m_bIsRightDir; }
	bool Get_IsJumping() { return m_bIsJump; }

public:
	void Set_Hp(int iHp) { m_iHp = iHp; }
	void Set_Dir(bool isRightDir) { m_bIsRightDir = isRightDir; }

protected:
	bool m_bIsJump;
	float m_fDeltaTime;
	float m_fVelY;
	float m_fJumpPower;

	INFO m_tInfo; 
	RECT m_tRect; 

	FRAME m_tFrame; 

	TCHAR* m_pFrameKey;
	
	float m_fSpeed; 
	float m_fAngle; 
	bool m_bIsDead;
	CObj* m_pTarget; 
	bool m_bIsInit; 

	bool m_bMotionEnd;
	bool m_bIsRightDir;

	int m_iHp;
	int m_iMaxHp;
	int m_iMp;
	int m_iMaxMp;
	
	bool m_bIsStun;
	DWORD m_dwStun;

};

