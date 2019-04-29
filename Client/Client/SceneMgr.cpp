#include "stdafx.h"
#include "SceneMgr.h"

#include "Logo.h"
#include "LineEditor.h"
#include "Stage.h"
#include "LineEditorTest.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	,m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SCENEID eScene)
{
	m_eNextScene = eScene;
	if (m_eCurScene != m_eNextScene)
	{
		if (m_pScene)
		{
			delete m_pScene;
			m_pScene = nullptr; 
		}
		switch (m_eNextScene)
		{
		case CSceneMgr::SCENE_LOGO:
			m_pScene = new CLogo; 
			break;
		case CSceneMgr::SCENE_STAGE:
			m_pScene = new CStage;
			break;

		case CSceneMgr::SCENE_LINE_EDIT:
			m_pScene = new CLineEditor;
			break;

		case CSceneMgr::SCENE_LINE_TEST:
			m_pScene = new CLineEditorTest;
			break;
		}
		
		m_pScene->Initialize(); 
		m_eCurScene = m_eNextScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	if (m_pScene)
	{
		delete m_pScene; 
		m_pScene = nullptr; 
	}
}
