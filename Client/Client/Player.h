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

private:
	// jump�� �ʿ��� ����. 
	bool m_bIsJump; 
	float m_fJumpPower; // �������� v�� �ǰڴ�. 
	float m_fJumpAccel; // �̰� ���� t�� �ǰڴ�. ���ӵ�. 

	TCHAR* m_pFrameKey;
	STATE m_eNextState;
	STATE m_eCurState; 
};

