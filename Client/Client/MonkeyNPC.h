#pragma once
#include "Obj.h"
class CMonkeyNPC :
	public CObj
{
public:
	enum STATE
	{
		YES
		, NO
	};

public:
	CMonkeyNPC();
	virtual ~CMonkeyNPC();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void StateChange();
	virtual void FrameMove() override;
	void Set_State(STATE eState) { m_eNextState = eState; }
	STATE Get_State() { return m_eCurState; }

private:
	STATE m_eCurState;
	STATE m_eNextState;
};

