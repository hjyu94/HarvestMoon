#pragma once
class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENEID{SCENE_LOGO, SCENE_MENU, SCENE_EDIT, SCENE_STAGE, SCENE_END};

public:
	void SceneChange(SCENEID eScene);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release(); 

private:
	CScene* m_pScene;

	// �̰��� ������ �޾ƿð� 
	SCENEID m_eNextScene;
	// �̰��� ����� ������ ������. 
	SCENEID m_eCurScene; 
};

