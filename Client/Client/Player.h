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
		, HURT, HURT_LEFT
	};

public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void IsJumping();
	void KeyCheck(); 
	void SceneChange();
	virtual void FrameMove();

private:
	// jump�� �ʿ��� ����. 
	bool m_bIsJump; 
	float m_fJumpPower; // �������� v�� �ǰڴ�. 
	float m_fJumpAccel; // �̰� ���� t�� �ǰڴ�. ���ӵ�. 

	TCHAR* m_pFrameKey;
	STATE m_eNextState;
	STATE m_eCurState; 

	bool m_bIsRolling = false;


};

