#pragma once
#include "Scene.h"
class CLineEditor :
	public CScene
{
public:
	CLineEditor();
	virtual ~CLineEditor();

public:
	// Inherited via CScene
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

