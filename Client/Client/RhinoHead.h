#pragma once
#include "Obj.h"
class CRhinoHead :
	public CObj
{
public:
	CRhinoHead();
	virtual ~CRhinoHead();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	enum STATE
	{
		IDLE
		, UP
	};
	
public:
	void StateChange();
	virtual void FrameMove() override;
	void Set_State(STATE eState) { m_eNextState = eState; }
	STATE Get_State() { return m_eCurState; }

private:
	STATE m_eCurState;
	STATE m_eNextState;
};
