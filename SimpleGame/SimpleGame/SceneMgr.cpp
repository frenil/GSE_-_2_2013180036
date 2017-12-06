#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(Renderer* ren)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.f);
	m_nObject = 0;
	m_pRendertarget = ren;
	shoottime = 0;
	settime = 2;
	m_nIndex = 0;
	m_BuildingTex[0] = ren->CreatePngTexture("./resource/Buckler.png");
	m_BuildingTex[1] = ren->CreatePngTexture("./resource/Kite Shield.png");
	m_BackGround = ren->CreatePngTexture("./resource/images.png");
	m_CharacterTex[0] = ren->CreatePngTexture("./resource/goblin.png");
	m_CharacterTex[1] = ren->CreatePngTexture("./resource/player.png");
	m_ParticleTex = ren->CreatePngTexture("./resource/img.png");
		
	for (int i = 0; i < 10; ++i) {
		Vector pos = Vector(-225+(i*50), 0, 0);
		AddObject(pos, WALL, -1);
	}
	m_Back = new CGameObject(Vector(0, 0, 0), 800, Vector(1, 1, 1), 1, BACK, 0.6f);
	m_Back->SetMaxLife(500);
	m_Back->SetSpeed(0);

	m_Back->SetTexture(m_BackGround);
	m_sound = new Sound();
	soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	m_sound->PlaySound(soundBG, true, 0.2f);

}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Render()
{
	
	m_Back->Render(m_pRendertarget);
	

	for (auto it = obj.begin(); it != obj.end(); ++it) {
		it->Render(m_pRendertarget);
	}
	m_pRendertarget->DrawText(-200.0f,0.0f, GLUT_BITMAP_TIMES_ROMAN_24
		, 1.0f, 0.0f, 0.0f, "Text Daje");

}

void SceneMgr::Update(float timeelapsed)
{
	m_fParticleTime += timeelapsed;
	shoottime += timeelapsed;
	settime += timeelapsed;
	////////////////////////////자동 생성
	if (shoottime > 1) {
		Vector pos = Vector(rand() % 250, rand() % 250, 0);
		AddObject(pos, CHARACTER, 1);		
		shoottime -= 1;
	}
	for (int i = 0; i < obj.size(); ++i) {
		if (obj[i].GetType() == BUILDING&&obj[i].GetTimer()>=1) {
			AddObject(obj[i].GetPosition(), BULLET, obj[i].GetTeam());
			obj[i].ResetTimer(1.0f);
		}
		else if (obj[i].GetType() == CHARACTER&&obj[i].GetTimer() >= 1) {
			obj[i].ResetTimer(1.0f);
			AddObject(obj[i].GetPosition(), ARROW, obj[i].GetTeam());
		}
	}

	////////////////////////////////업데이트
	for (auto it = obj.begin(); it != obj.end(); ) {
		it->Update(timeelapsed);

		it->colided = false;
		if (it->GetType() == ARROW || it->GetType() == BULLET) {

			if (it->GetPosition().x >= WINW / 2 || it->GetPosition().x <= -(WINW / 2)
				|| it->GetPosition().y >= WINH / 2 || it->GetPosition().y <= -(WINH / 2))
			{
				obj.erase(it);
				break;
			}
			else
				++it;
		}
		else if (it->GetLife() <= 0) {
			obj.erase(it);
			break;
		}
		else
			++it;
	}

	//////////////////////////////////////충돌
	for (auto it = obj.begin(); it != obj.end(); ++it) {
		for (auto it2 = it+1; it2 != obj.end(); ++it2) {
			if (it != it2) {
				if (Colide(*it, *it2) && it2->GetTeam() != it->GetTeam()) {
					if (it->GetType() == BUILDING) {
						if (it2->GetType() == CHARACTER)
						{
							it->Damage(it2->GetLife());
							it->colided = true;
							it2->colided = true;
						}
						else if (it2->GetType() == ARROW || it2->GetType() == BULLET) {
							it->Damage(it2->GetLife());
							it2->colided = true;
						}
					}

					else if (it->GetType() == CHARACTER) {
						if (it2->GetType() == BUILDING)
						{
							it2->Damage(it->GetLife());
							it->colided = true;
							it2->colided = true;
						}
						
						else if ((it2->GetType() == ARROW)|| it2->GetType() == BULLET) {
							it->Damage(it2->GetLife());
							it2->colided = true;
						}
					}	

					else if (it->GetType() == ARROW) {
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
	//////////////////////////////////////삭제
	for (auto it = obj.begin(); it != obj.end(); ) {
		if (it->colided && (it->GetType() == CHARACTER || it->GetType() == BULLET || it->GetType() == ARROW)) {
			auto it2 = it;
			--it;
			obj.erase(it2);
		}
		else
			++it;
	}
}

CGameObject SceneMgr::AddObject(Vector pos, int type, int tnum, int p)
{
	CGameObject addobj;
	Vector color;
	switch (type) {
	
	case BUILDING:

		color = Vector(1, 1, 1);
		addobj = CGameObject(pos, 100, color, 1, type,0.4f);
		addobj.SetMaxLife(500);
		addobj.SetSpeed(0);

		if (tnum == 1) addobj.SetTexture(m_BuildingTex[0]);
		else if (tnum == 2) addobj.SetTexture(m_BuildingTex[1]);
		
		break;
	case BULLET:
		if (tnum == 1) color = Vector(1, 0, 0);
		else if (tnum == 2) color = Vector(0, 0, 1);
		addobj = CGameObject(pos,10, color, 1, type,0.1f);
		addobj.SetMaxLife(20);
		addobj.SetSpeed(600);
		addobj.SetMove(Vector((float)(rand() % (100))-50, (float)(rand() % (100)) - 50, 0).Normalize());
		addobj.SetParticle(m_ParticleTex);
		break;
	case ARROW:
		if (tnum == 1) color = Vector(0.5f, 0.2f, 0.7f);
		else if (tnum == 2) color = Vector(1, 1, 0);
		addobj = CGameObject(pos, 10, color, 1, type,0.1f);
		addobj.SetMaxLife(10);
		addobj.SetMove(Vector((float)(rand() % (100)) - 50, (float)(rand() % (100)) - 50, 0).Normalize());
		addobj.SetSpeed(100);
		break;
	case WALL:
		color = Vector(1, 1, 1);
		addobj = CGameObject(pos, 5, color, 1, type,0);
		addobj.SetMaxLife(10);
		addobj.SetMove(Vector(0,0,0));
		addobj.SetSpeed(0);
	}
	addobj.SetTeam(tnum);
	obj.push_back(addobj);
	++m_nObject;
	return addobj;
}

CGameObject SceneMgr::AddCharacter(Vector pos, int type, int tnum, int p)
{
	CGameObject addobj;
	Vector color;
	switch (type) {
	
	case Ground:
		if (tnum == 1) color = Vector(1, 0, 0);
		else if (tnum == 2) color = Vector(0, 0, 1);
		addobj = CCharacter(pos, 30, color, 1, type, 0.5f);
		addobj.SetMaxLife(15);
		addobj.SetSpeed(50);

		 addobj.SetTexture(m_CharacterTex[0]);
		break;
	case Flying:
		if (tnum == 1) color = Vector(1, 0, 0);
		else if (tnum == 2) color = Vector(0, 0, 1);
		addobj = CCharacter(pos, 30, color, 1, type, 0.5f);
		addobj.SetMaxLife(15);
		addobj.SetSpeed(100);

		addobj.SetTexture(m_CharacterTex[1]);
		break;
	}
	addobj.SetTeam(tnum);
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

void SceneMgr::SetPlayerCharacter(Vector pos)
{
	if (settime >= 2&&pos.y<=0) {
		AddObject(pos, CHARACTER, 2);
		settime = 0;
	}
}
