#pragma once
#include "Obj.h"
class CVertex :
	public CObj
{
public:
	CVertex();
	virtual ~CVertex();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

