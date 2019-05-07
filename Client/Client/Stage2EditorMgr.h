#pragma once
class CLine;

class CStage2EditorMgr
{
	DECLARE_SINGLETON(CStage2EditorMgr)
	
public:
	void Initialize();
	void Render(HDC hDC);
	void Update();
	void Release();

public:
	void SaveData();
	void LoadData();

public:

private:
	list<CLine*> m_listLine;
};

