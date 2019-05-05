#pragma once
#include "Obj.h"
class CVertex :
	public CObj
{
public:
	CVertex();
	virtual ~CVertex();

public:
	enum DIR
	{
		L, R
	};

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	DIR& Get_Dir() { return m_eDir; }
	void Set_Dir(DIR eDir) { m_eDir = eDir; }

private:
	DIR m_eDir;
};

