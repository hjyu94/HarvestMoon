#pragma once
class CLine;
class CVertex;
class CBlock;
class CVerticalBlocck;
class CFly;
class CLizard;
class CHedgeHog;
class CItem;

class CEditorLineMgr
{
private:
	CEditorLineMgr();
	~CEditorLineMgr();
public:
	static CEditorLineMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CEditorLineMgr;

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
	void Initialize();
	void Render(HDC hDC);
	void Update();
	void Release();

private:
	void SaveData();
	void LoadData();

	enum ID
	{
		FLY, LIZARD, HEDGEHOG, ITEM, END	
	};

private:
	static CEditorLineMgr*	m_pInstance;
	list<CLine*>			m_listLine;
	list<CVertex*>			m_listVertex;
	list<CBlock*>			m_listBlock;
	list<CVerticalBlocck*>	m_listVerticalBlock;

	OBJLIST m_listEnum[ID::END];
	DWORD m_dwPosRenderTime;
};

