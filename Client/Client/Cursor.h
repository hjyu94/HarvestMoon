#pragma once
#include "Obj.h"
class CCursor :
	public CObj
{
public:
	CCursor();
	virtual ~CCursor();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	//void StateChange();
};

