#pragma once
#include "Monster.h"

class CPlayer;

class CHyena :
	public CMonster
{
public:
	CHyena();
	virtual ~CHyena();

public:
	enum STATE {
		START,
		IDLE, IDLE_LEFT
		, DIE, DIE_LEFT
		, JUMP, JUMP_LEFT
		, ROARING, ROARING_LEFT
		, TIRED, TIRED_LEFT
	};

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void PosLock();
	void StateChange();
	virtual void IsJumping() override;
	virtual void Collision_Proc(CObj* pCounterObj);
	STATE Get_State();
	virtual void FrameMove();
	void Get_Damage();
	bool Get_IsDead() { return m_bIsDead; }
	void TargetCheck();

private:
	STATE m_eNextState;
	STATE m_eCurState;

	bool m_bIsTired;
	bool m_bIsStop;
	DWORD m_dwPattern;
	PATTERN m_ePattern;

	bool m_bIsAlreadyColl;
	CPlayer* m_pTarget;

	int m_iHp;
};






