#pragma once
#include "Obj.h"

class CLine;

class CGiraffe :
	public CObj
{
public:
	enum STATE {IDLE, NECK};

public:
	CGiraffe();
	~CGiraffe();

	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SceneChange();
	virtual void Collision_Proc(CObj* pCounterObj);
	virtual void FrameMove();


private:
	TCHAR* m_pFrameKey;
	STATE m_eNextState;
	STATE m_eCurState;
	CLine* m_pLine;

	DWORD m_dwTiltDelay;
	bool m_bIs_Collision_With_Player;
};

