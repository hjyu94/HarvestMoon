#pragma once
#include "Obj.h"
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
	void KeyCheck();
	void SceneChange();

private:
	TCHAR* m_pFrameKey;
	STATE m_eNextState;
	STATE m_eCurState;
};

