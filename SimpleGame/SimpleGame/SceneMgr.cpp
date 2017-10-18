#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Render()
{
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		it->Render();
	}
}

void SceneMgr::Update()
{
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		it->Update();
	}
}

void SceneMgr::AddObject(CGameObject * addobj, Renderer* ren)
{
	addobj->SetRenderer(ren);

	obj.push_back(*addobj);
}

bool SceneMgr::Colide(CGameObject a, CGameObject b)
{

	return false;
}
