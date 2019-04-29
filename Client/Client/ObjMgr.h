#pragma once
class CObj; 
class CPlayer;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();
public:
	static CObjMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void Destory_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
public:
	CPlayer* Get_Player() { return (CPlayer*)(m_Objlist[OBJID::PLAYER].front()); }
	OBJLIST Get_OBJLIST(OBJID::ID eID) { return m_Objlist[eID]; }
	CObj* Get_Target(CObj* pSrc, OBJID::ID eID);

public:
	void AddObject(OBJID::ID eID, CObj* pObj);
	int Update();
	void LateUpdate();
	void Render(HDC hDC); 
	void Release(); 
	void DeleteID(OBJID::ID eID);
private:
	static CObjMgr* m_pInstance;
	OBJLIST m_Objlist[OBJID::END];
};

