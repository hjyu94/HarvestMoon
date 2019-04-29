#pragma once
#include "Obj.h"
class CTestPlayer :
	public CObj
{
public:
	CTestPlayer();
	virtual ~CTestPlayer();

	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool m_bIsJump = false;

	float m_fJumpPower; // 물리에서 v가 되겠다. 
	float m_fJumpAccel; // 이게 이제 t가 되겠다. 가속도. 
};

	