#pragma once
class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENEID
	{
		SCENE_LOGO
		, SCENE_LINE_EDIT
		, SCENE_STAGE
		, SCENE_DEAD
		, SCENE_RESTART
		, SCENE_END};

public:
	void SceneChange(SCENEID eScene);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release(); 

public:
	SCENEID Get_SCENEID() { return m_eCurScene; }
	CScene* Get_pScene() { return m_pScene; }
	POINT Get_SceneRect();

private:
	CScene* m_pScene;

	// 이것이 다음씬 받아올것 
	SCENEID m_eNextScene;
	// 이것이 현재씬 가지고 있을것. 
	SCENEID m_eCurScene; 
};

