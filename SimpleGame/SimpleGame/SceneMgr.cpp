#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(Renderer* ren)
{
	m_nObject = 0;
	m_pRendertarget = ren;
	shoottime = 0;
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Render()
{
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		it->Render(m_pRendertarget);
	}
}

void SceneMgr::Update(float timeelapsed)
{
	shoottime += timeelapsed;
	if (obj.begin()->GetType() == BUILDING&&shoottime > 2) {
		shoottime = 0;
		AddObject(obj.begin()->GetPosition(), 10, BULLET);
	}
	for (auto it = obj.begin(); it != obj.end(); ) {
		it->Update(timeelapsed);

		it->colided = false;
		if (it->GetLife() <= 0) {
			obj.erase(it);
			break;
		}
		else
		{			
			++it;
		}
	}
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		for (auto it2 = it+1; it2 != obj.end(); ++it2) {
			if (Colide(*it, *it2)) {
				if (it->GetType() == CHARACTER&&it2->GetType() == BUILDING
					|| it2->GetType() == CHARACTER&&it->GetType() == BUILDING) {
					it->colided = true; 
					it2->colided = true;
				}

				if (it->GetType() == CHARACTER&&	it2->GetType() == BULLET) {
					it->Damage(it2->GetLife());
					it2->colided = true;
				}
				else if( it2->GetType() == CHARACTER&&it->GetType() == BULLET) {
					it2->Damage(it->GetLife());
					it->colided = true;
				}
			}
		}
	}
	for (auto it = obj.begin(); it != obj.end(); ) {
		if (it->colided&&it->GetType() == BUILDING) {
			it->Damage(10);
			printf("%f\n", it->GetLife());
		}
		if (it->colided&&(it->GetType()==CHARACTER||it->GetType() == BULLET)) {
			auto it2 = it;
			--it;
			obj.erase(it2);
		}
		else
			++it;
	}
}

void SceneMgr::AddObject(Vector pos, float s, int type)
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
		addobj.SetLife(500);
		addobj.SetSpeed(0);
		break;
	case BULLET:
		addobj= CGameObject(pos, s, Vector(1, 0, 0), 1, type);
		addobj.SetLife(20);
		addobj.SetSpeed(600);
		addobj.SetMove(Vector((rand() % 100)/100.f, (rand() % 100)/100.f, 0));
		break;
	case ARROW:
		addobj= CGameObject(pos, s, Vector(0, 1, 0), 1, type);
		addobj.SetLife(10);
		addobj.SetSpeed(100);
		break;
	}

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
