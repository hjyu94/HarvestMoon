#pragma once
#include "Monster.h"
class CMonkey :
	public CMonster
{
public:
	CMonkey();
	virtual ~CMonkey();

public:
	enum COLOR
	{
		C_PINK
		, C_BLUE
	};

	enum STATE 
	{
		IDLE, IDLE_LEFT
		, THROW, THROW_LEFT
	};

	enum DIR
	{
		LEFT, RIGHT, DOWN, UP, END
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
	void Thorw_Player(DIR eDIR);
	void Turn_Around();

public:
	void Set_Color(COLOR eCol);
	CMonkey::COLOR& Get_Color();
	void Set_ThrowDir(DIR eDir);
	CMonkey::DIR& Get_ThrowDir();

	void Change_Color();
	void Change_Dir();

private:
	STATE m_eNextState;
	STATE m_eCurState;

	COLOR m_eColor;
	DIR m_eDir;

	DWORD m_dwTurnCoolTime;
};



