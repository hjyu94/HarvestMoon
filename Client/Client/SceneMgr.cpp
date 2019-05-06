#include "stdafx.h"
#include "SceneMgr.h"

#include "Logo.h"
#include "LineEditor.h"
#include "Stage.h"
#include "DeadScene.h"
#include "RestartScene.h"
#include "BridgeScene.h"
#include "Stage_2.h"

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

		case CSceneMgr::SCENE_DEAD:
			m_pScene = new CDeadScene;
			break;

		case CSceneMgr::SCENE_RESTART:
			m_pScene = new CRestartScene;
			break;

		case CSceneMgr::SCENE_BRIDGE:
			m_pScene = new CBridgeScene;
			break;

		case CSceneMgr::SCENE_STAGE_2:
			m_pScene = new CStage_2;
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

POINT CSceneMgr::Get_SceneRect()
{
	POINT pt =
	{
		m_pScene->Get_BackgroundWidth(),
		m_pScene->Get_BackgroundHeight()
	};

	return pt;
}
