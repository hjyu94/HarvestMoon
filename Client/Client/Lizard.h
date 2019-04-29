#pragma once
#include "Monster.h"
class CLizard :
	public CMonster
{
public:
	CLizard();
	virtual ~CLizard();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	enum STATE {
		IDLE, IDLE_LEFT
		, ATTACK, ATTACK_LEFT
	};

public:
	void KeyCheck();
	void SceneChange();
	virtual void FrameMove();
	void Collision_Proc(CObj* pCounterObj);
private:
	STATE m_eNextState;
	STATE m_eCurState;

	DWORD m_dwWalking;
	DWORD m_dwAttack;
	bool m_bIsAttacking;
	bool m_bIsStop;
};

