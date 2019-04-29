#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	enum STATE {
		IDLE, IDLE_LEFT
		, ROARING, ROARING_LEFT
		, DOWN, DOWN_LEFT
		, UP, UP_LEFT
		, RUNNING, RUNNING_LEFT
		, ROLLING, ROLLING_LEFT
		, LEDGE_DOWN, LEDGE_DOWN_LEFT
		, STANDING_LAND, STANDING_LAND_LEFT
		, STANDING_JUMP, STANDING_JUMP_LEFT
		, GRABBING_LEDGE_FIRST, GRABBING_LEDGE_FIRST_LEFT
		, GRABBING_LEDGE_SECOND, GRABBING_LEDGE_SECOND_LEFT
		, HURT, HURT_LEFT
	};

public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void IsJumping();
	void IsRoaring();
	void IsRolling();
	void IsHurting();
	void IsDanging();

	void KeyCheck(); 
	void SceneChange();
	virtual void FrameMove();
	void Move(float fScrollMaxX, bool is_MovingDir_Right);
	virtual void Collision_Proc(CObj* pCounterObj);
	void BackToIdle();
	STATE Get_CurState() { return m_eCurState; }

private:

	// jump에 필요한 변수. 
	bool m_bIsJump; 
	float m_fJumpPower;
	float m_fDeltaTime; 

	float m_fVelX;
	float m_fVelY;

	bool m_bIsRolling;
	bool m_bIsHurting;
	bool m_bIsRoaring;
	bool m_bIsDanging;

	STATE m_eNextState;
	STATE m_eCurState;

	DWORD m_dwRecover;
	DWORD m_dwNoCollision;

private:
	bool m_bIsSaved;
	float m_fSaving_X;
	float m_fSaving_Y;
};

