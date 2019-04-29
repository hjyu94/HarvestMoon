#pragma once

#include "BitmapMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual void Initialize() = 0;
	virtual void Update()= 0 ;
	virtual void LateUpdate() =0;
	virtual void Render(HDC hDC)=0;
	virtual void Release()=0;

public:
	int Get_BackgroundWidth() { return iBackgroundWidth; }
	int Get_BackgroundHeight() { return iBackgroundHeight; }

protected:
	int iBackgroundWidth;
	int iBackgroundHeight;
};

