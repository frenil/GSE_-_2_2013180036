#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(Renderer* ren)
{
	m_nObject = 0;
	m_pRendertarget = ren;
	shoottime = 0;
	m_nIndex = 0;
	m_BuildingTex = ren->CreatePngTexture("./resource/Buckler.png");
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
	if (shoottime > 2) {
		for (int i = 0; i < obj.size(); ++i) {
			if (obj[i].GetType() == BUILDING)
				AddObject(obj[i].GetPosition(), 10, BULLET);
			else if (obj[i].GetType() == CHARACTER)
				AddObject(obj[i].GetPosition(), 10, ARROW, obj[i].GetIndex());
		}
		shoottime = 0;
	}
	for (auto it = obj.begin(); it != obj.end(); ) {
		it->Update(timeelapsed);

		it->colided = false;
		if (it->GetLife() <= 0) {
			obj.erase(it);
			break;
		}
		else
			++it;
	}
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		for (auto it2 = it+1; it2 != obj.end(); ++it2) {
			if (it != it2) {
				if (Colide(*it, *it2)) {
					if (it->GetType() == BUILDING) {
						if (it2->GetType() == CHARACTER)
						{
							it->colided = true;
							it2->colided = true;
						}
						else if (it2->GetType() == ARROW) {
							it->Damage(it2->GetLife());
							it2->colided = true;
						}
					}

					else if (it->GetType() == CHARACTER) {
						if (it2->GetType() == BUILDING)
						{
							it->colided = true;
							it2->colided = true;
						}
						
						else if ((it2->GetType() == ARROW&& it2->GetParent() != it->GetIndex())|| it2->GetType() == BULLET) {
							it->Damage(it2->GetLife());
							it2->colided = true;
						}
					}	

					else if (it->GetType() == ARROW&& it->GetParent()!=it2->GetIndex()) {
						if (it2->GetType() == BUILDING || it2->GetType() == CHARACTER)
						{
							it2->Damage(it->GetLife());
							it->colided = true;
						}
					}
					else if (it->GetType() == BULLET) {
						if (it2->GetType() == CHARACTER)
						{
							it2->Damage(it->GetLife());
							it->colided = true;
						}
					}
				}
			}
		}
	}
	for (auto it = obj.begin(); it != obj.end(); ) {
		if (it->colided&&it->GetType() == BUILDING) {
			it->Damage(10);
			printf("%f\n", it->GetLife());
		}
		if (it->colided && (it->GetType() == CHARACTER || it->GetType() == BULLET || it->GetType() == ARROW)) {
			auto it2 = it;
			--it;
			obj.erase(it2);
		}
		else
			++it;
	}
}

CGameObject SceneMgr::AddObject(Vector pos, float s, int type,int p)
{
	CGameObject addobj;
	switch (type) {
	case CHARACTER:
		addobj = CGameObject(pos, s, Vector(1, 1, 1), 1, type);
		addobj.SetLife(10);
		addobj.SetSpeed(100);
		break;
	case BUILDING:
		addobj = CGameObject(pos, s, Vector(1, 1, 0), 1, type);
		addobj.SetLife(500);
		addobj.SetSpeed(0);
		addobj.SetTexture(m_BuildingTex);
		break;
	case BULLET:
		addobj = CGameObject(pos, s, Vector(1, 0, 0), 1, type);
		addobj.SetLife(20);
		addobj.SetSpeed(600);
		addobj.SetMove(Vector((float)(rand() % (100))-50, (float)(rand() % (100)) - 50, 0).Normalize());
		break;
	case ARROW:
		addobj = CGameObject(pos, s, Vector(0, 1, 0), 1, type);
		addobj.SetLife(10);
		addobj.SetMove(Vector((float)(rand() % (100)) - 50, (float)(rand() % (100)) - 50, 0).Normalize());
		addobj.SetSpeed(100);
		break;
	}
	addobj.SetParent(p);
	addobj.SetIndex(m_nIndex++);
	obj.push_back(addobj);
	++m_nObject;
	return addobj;
}

bool SceneMgr::Colide(CGameObject a, CGameObject b)
{
	if (a.GetOOBB().Left > b.GetOOBB().Right)	return false;
	if (a.GetOOBB().Right < b.GetOOBB().Left)	return false;
	if (a.GetOOBB().Up < b.GetOOBB().Down)	return false;
	if (a.GetOOBB().Down > b.GetOOBB().Up)	return false;

	return true;
}
