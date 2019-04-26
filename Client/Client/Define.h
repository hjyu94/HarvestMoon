#pragma once

#define WINCX 800
#define WINCY 600

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define ToRadian(Degree) Degree * 3.141592f / 180.f 
#define ToDegree(Radian) Radian * 180.f / 3.141592f


#define DECLARE_SINGLETON(Class)			\
private:									\
	Class();								\
	~Class();								\
public:										\
	static Class* Get_Instance()			\
	{										\
		if (nullptr == m_pInstance)			\
			m_pInstance = new Class;		\
											\
		return m_pInstance;					\
	}										\
	static void Destroy_Instance()			\
		{									\
			if (m_pInstance)				\
			{								\
				delete m_pInstance;			\
				m_pInstance = nullptr;		\
			}								\
	}										\
private:									\
	static Class* m_pInstance;

#define IMPLEMENT_SINGLETON(Class)			\
Class* Class::m_pInstance = nullptr; 
