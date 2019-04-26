#pragma once

template<class T>
class CAbstractFactory
{
public:
	static T* Create()
	{
		T* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static T* Create(float fx, float fy)
	{
		T* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fx, fy);
		return pObj;
	}
};
