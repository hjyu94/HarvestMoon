#pragma once
#include "Scene.h"
class CMyMenu :
	public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

