#pragma once
#include "Obj.h"
class CTailVertex :
	public CObj
{
public:
	CTailVertex();
	virtual ~CTailVertex();

	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

