#pragma once

#define WINCX 650
#define WINCY 450

#define TILESIZEX 64
#define TILESIZEY 64
#define TILEX 100
#define TILEY 100

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

#define Is_Counter_One_Of(Class) dynamic_cast<Class*>(pCounterObj) != nullptr

#define KEYDOWN_LBUTTON_AND_COUT(content) \
if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON)) \
{ \
	cout << content << endl; \
}

#define KEYPRESSING_LBUTTON_AND_COUT(content) \
if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON)) \
{ \
	cout << content << endl; \
}