#pragma once
#include "Monster.h"
class CHedgeHog :
	public CMonster
{
public:
	enum STATE {
		IDLE, IDLE_LEFT
		, UPSIDE_DOWN, UPSIDE_DOWN_LEFT 
		, DIE
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
	
public:
	void StateChange();
	virtual void Collision_Proc(CObj* pCounterObj);


public:
	void Upside_Down();
	void IsJumping();
	bool Get_UpsideState() { return m_bIsUpsidedown; }

private:
	STATE m_eNextState;
	STATE m_eCurState;

	DWORD m_dwUpsidedown;
	bool m_bIsUpsidedown;
	
	DWORD m_dwWalking;
	bool m_bIsStop;

	bool m_bIsJump;
	float m_fJumpPower;
	float m_fDeltaTime;
	float m_fVelY;
};

