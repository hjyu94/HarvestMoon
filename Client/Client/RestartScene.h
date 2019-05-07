#pragma once
#include "Scene.h"
class CRestartScene :
	public CScene
{
public:
	CRestartScene();
	virtual ~CRestartScene();

	// Inherited via CScene
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD m_dwContinueSelect;
	bool m_bIsCountinueSelect;
};

