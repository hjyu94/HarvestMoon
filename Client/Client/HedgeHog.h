#pragma once
#include "Monster.h"
class CHedgeHog :
	public CMonster
{
public:
	enum STATE {
		IDLE, IDLE_LEFT
		, UPSIDE_DOWN, UPSIDE_DOWN_LEFT 
	};

public:
	CHedgeHog();
	virtual ~CHedgeHog();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void FrameMove() override;
	
public:
	void StateChange();
	virtual void Collision_Proc(CObj* pCounterObj);

public:
	bool Get_IsDying() { return m_bIsDying; }
	void Upside_Down();
	void IsDying();
	bool Get_UpsideState() { return m_bIsUpsidedown; }
	void Back_To_Idle();
	
private:
	STATE m_eNextState;
	STATE m_eCurState;

	float fRandTime;
	DWORD m_dwUpsidedown;
	DWORD m_dwWalking;
	DWORD m_dwWalking2;

	bool m_bIsStop;
	bool m_bIsUpsidedown;
	bool m_bIsJump;
	bool m_bIsDying;
	
	float m_fJumpPower;
	float m_fDeltaTime;
	float m_fVelY;
};

