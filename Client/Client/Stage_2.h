#pragma once
#include "Scene.h"
class CStage_2 :
	public CScene
{
public:
	CStage_2();
	virtual ~CStage_2();

public:
	// Inherited via CScene
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

