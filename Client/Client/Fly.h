#pragma once
#include "Monster.h"
class CFly :
	public CMonster
{
public:
	CFly();
	virtual ~CFly();

public:
	enum STATE {
		IDLE, IDLE_LEFT
		, DIE, DIE_LEFT
		, BOMB
	};

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void StateChange();
	void Bombing();
	CFly::STATE Get_State();

public:
	virtual void Collision_Proc(CObj* pCounterObj);
	virtual void FrameMove();
private:
	STATE m_eNextState;
	STATE m_eCurState;

	DWORD m_dwWalking;
	bool m_bIsStop;

	float fRandTime;
};






