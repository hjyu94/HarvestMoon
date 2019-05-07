#pragma once
#include "Scene.h"
class CBridgeScene :
	public CScene
{
public:
	CBridgeScene();
	virtual ~CBridgeScene();

public:
	// Inherited via CScene
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD dwClose;
	bool m_bIsSound;
};

