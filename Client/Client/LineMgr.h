#pragma once
class CLine;
class CVertex;
class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();
public:
	static CLineMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineMgr; 

		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}

public:
	void AddLine(CLine* pLine);
	void Initialize();
	void Render(HDC hDC);
	void Release(); 
	list<CLine*>& Get_List() { return m_listLine; }

public:
	bool LineCollision(float fInX, float fInY, float* pOutY);
	void LoadData(); 
	void LoadData_for_stage_2();

private:
	static CLineMgr* m_pInstance;
	list<CLine*> m_listLine;
	list<CVertex*> m_listVertex;
};

