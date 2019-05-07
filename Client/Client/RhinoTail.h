#pragma once
#include "Obj.h"
class CTailVertex;

class CRhinoTail :
	public CObj
{
public:
	CRhinoTail();
	virtual ~CRhinoTail();

public:
	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void FrameMove() override;

private:
	float			m_fDist;
	float			m_fTheta;
	CTailVertex*	m_pTailVertex;
};
