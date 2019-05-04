#pragma once
#include "Obj.h"
class CLine;

class CBlock :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
};

