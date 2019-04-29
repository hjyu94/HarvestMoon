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

	float m_fJumpPower; // �������� v�� �ǰڴ�. 
	float m_fJumpAccel; // �̰� ���� t�� �ǰڴ�. ���ӵ�. 
};

	