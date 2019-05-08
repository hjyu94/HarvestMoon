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
		, CLIMBING_LEDGE, CLIMBING_LEDGE_LEFT
		, GRABBING_LEDGE_FIRST, GRABBING_LEDGE_FIRST_LEFT
		, GRABBING_LEDGE_SECOND, GRABBING_LEDGE_SECOND_LEFT
		, HURT, HURT_LEFT
		, DIE, DIE_LEFT
		, SWING
		, RIDING
	};

	enum DIR
	{
		D_LEFT, D_RIGHT, D_DOWN, D_UP, D_END
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
	void IsOffset();
	void IsRecovering();
	void IsRiding();

	void Is_On_Another_Scene();

	void KeyCheck(); 
	void SceneChange();
	virtual void FrameMove();
	virtual void Collision_Proc(CObj* pCounterObj);
	void BackToIdle();
	void Jump_with_Rhino();
	void Rolling_Along_Giraffe(bool bIs_GiraffeDir_Right, RECT rcGiraffe);
	void Rolling_With_Monkey(CPlayer::DIR eDIR);
	void Riding_On_Ostrich();

public:
	STATE Get_CurState() { return m_eCurState; }
	bool Get_IsHurt() { return m_bIsHurting; }
	bool Get_Is_Dangling_With_Rhino() { return m_bIsDangling_with_Rhino; }
public:
	bool IsBetween(DWORD dwTime, float min, float max)
	{
		return (dwTime >= min && dwTime <= max);
	}
	
	int Get_CurStage() { return m_iCurStage; }
	void Set_CurStage(int iStage) { m_iCurStage = iStage; }
	int& Get_JumpCount() { return m_iJumpCount; }
	void FinalShooting();
private:

	bool m_bIsRolling;
	bool m_bIsHurting;
	bool m_bIsRoaring;
	bool m_bIsDangling;
	bool m_bIsDangling_with_Rhino;

 	bool m_bIsRolling_with_Monkey;
	bool m_bIsRiding_On_Ostrich;

	bool m_bIsSeeingDown;
	bool m_bIsSeeingUp;
	bool m_bIsScrollEffect;
	bool m_bIsBlockCollision;
	bool m_bIs_On_Another_Scene;

	STATE m_eNextState;
	STATE m_eCurState;

	DWORD m_dwRecover;
	DWORD m_dwNoCollision;
	DWORD m_dwUp;
	DWORD m_dwDown;
	DWORD m_dwAnimation;
	DWORD m_dwKill;
	DWORD m_dwDangling_with_Rhino;
	DWORD m_dwMonkeyCoolTime;

	bool m_bIsTransparent;
	int m_iTransparentCount;

	float m_fVelX;
	int m_iCurStage;
	int m_iJumpCount; // Ostrich 2단 점프

	
};
