#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_nObject = 0;
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

void SceneMgr::Update(float timeelapsed)
{
	for (auto it = obj.begin(); it != obj.end(); ) {
		it->Update(timeelapsed);
		it->colided = false;
		if (it->GetLife()<=0) {
			auto it2 = it;
			--it;
		}
		++it;
	}
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		for (auto it2 = it+1; it2 != obj.end(); ++it2) {
			if (Colide(*it, *it2)) {
				it->colided = true;
				it2->colided = true;
			}
		}
	}
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		if(it->colided)
			it->SetColor(Vector(1, 0, 0));
		else
			it->SetColor(Vector(1, 1, 1));
	}
}

void SceneMgr::AddObject(CGameObject * addobj, Renderer* ren)
{
	addobj->SetRenderer(ren);

	obj.push_back(*addobj);
	++m_nObject;
}

bool SceneMgr::Colide(CGameObject a, CGameObject b)
{
	if (a.GetOOBB().Left>b.GetOOBB().Right)	return false;
	if (a.GetOOBB().Right<b.GetOOBB().Left)	return false;
	if (a.GetOOBB().Up<b.GetOOBB().Down)	return false;
	if (a.GetOOBB().Down>b.GetOOBB().Up)	return false;

	return true;
}
