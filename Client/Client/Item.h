#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	enum ID
	{
		HP
		, MP
		, LIFE
		, SAVE
	};

	enum STATE
	{
		IDLE, BLINK,
	};

public:
	virtual void Collision_Proc(CObj* pCounterObj);

public:
	void Set_ID(ID eID);
public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void FrameMove() override;
	void StateChange();
	CItem::ID Get_ID() { return m_eID; }

private:
	CItem::ID m_eID;
	STATE m_eCurState;
	STATE m_eNextState;
};

