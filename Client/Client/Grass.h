#pragma once
#include "Obj.h"
class CGrass :
	public CObj
{
public:
	CGrass();
	virtual ~CGrass();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

