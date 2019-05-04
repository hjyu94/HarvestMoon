#pragma once
#include "Obj.h"
class CVerticalBlocck :
	public CObj
{
public:
	CVerticalBlocck();
	virtual ~CVerticalBlocck();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

