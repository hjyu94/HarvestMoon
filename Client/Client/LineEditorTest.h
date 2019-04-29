#pragma once
#include "Scene.h"
class CLineEditorTest :
	public CScene
{
public:
	CLineEditorTest();
	virtual ~CLineEditorTest();

	// Inherited via CScene
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

