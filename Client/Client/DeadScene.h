#pragma once
#include "Scene.h"
class CDeadScene :
	public CScene
{
public:
	CDeadScene();
	virtual ~CDeadScene();

	// Inherited via CScene
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

