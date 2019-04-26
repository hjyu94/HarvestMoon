#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	enum STATE { IDLE, WALK, ATT, HIT, DIE};

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
	void KeyCheck(); 
	void SceneChange();

private:
	// jump에 필요한 변수. 
	bool m_bIsJump; 
	float m_fJumpPower; // 물리에서 v가 되겠다. 
	float m_fJumpAccel; // 이게 이제 t가 되겠다. 가속도. 

	TCHAR* m_pFrameKey;
	STATE m_eNextState;
	STATE m_eCurState; 
};

