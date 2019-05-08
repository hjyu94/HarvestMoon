#pragma once
#include "Monster.h"
class CPlayer;
class CLine;

class COstrich :
	public CMonster
{
public:
	COstrich();
	virtual ~COstrich();

public:
	enum STATE {
		STOP, RUN, JUMP, DOWN,
	};

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void StateChange();
	virtual void Collision_Proc(CObj* pCounterObj);
	virtual void FrameMove();
	virtual void IsJumping() override;

private:
	STATE		m_eNextState;
	STATE		m_eCurState;
	bool		m_bIs_With_Player;
	CPlayer*	m_pPlayer;
	CLine*		m_pLine;
};






