#pragma once
#include "Scene.h"
class CStage2Editor :
	public CScene
{
public:
	CStage2Editor();
	virtual ~CStage2Editor();

public:
	// Inherited via CScene
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

