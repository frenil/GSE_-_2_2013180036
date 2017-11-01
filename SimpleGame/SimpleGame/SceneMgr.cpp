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
			obj.erase(it2);
			--it;
		}
		++it;
	}
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		for (auto it2 = it+1; it2 != obj.end(); ++it2) {
			if (Colide(*it, *it2)) {
				if (it->GetType() == CHARACTER&&it2->GetType() == BUILDING
					|| it2->GetType() == CHARACTER&&it->GetType() == BUILDING) {
					it->colided = true; 
					it2->colided = true;
				}
			}
		}
	}
	for (auto it = obj.begin(); it != obj.end(); ) {
		if (it->colided&&it->GetType() == BUILDING) {
			it->Damage(10);
			printf("%f\n", it->GetLife());
		}
		if (it->colided&&it->GetType()==CHARACTER) {
			auto it2 = it;
			--it;
			obj.erase(it2);
		}
		else
			++it;
	}
}

void SceneMgr::AddObject(Vector pos, float s, int type, Renderer* ren)
{
	CGameObject addobj;
	switch (type) {
	case CHARACTER:
		addobj= CGameObject(pos, s, Vector(1, 1, 1), 1,type);
		addobj.SetLife(10);
		addobj.SetSpeed(100);
		break;
	case BUILDING:
		addobj= CGameObject(pos, s, Vector(1, 1, 0), 1, type);
		addobj.SetSpeed(0);
		addobj.SetLife(500);
		break;
	case BULLET:
		addobj= CGameObject(pos, s, Vector(1, 0, 0), 1, type);
		addobj.SetLife(20);
		addobj.SetSpeed(300);
		break;
	case ARROW:
		addobj= CGameObject(pos, s, Vector(0, 1, 0), 1, type);
		addobj.SetLife(10);
		addobj.SetSpeed(100);
		break;
	}
	
	addobj.SetRenderer(ren);

	obj.push_back(addobj);
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
