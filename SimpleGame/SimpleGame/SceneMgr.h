#pragma once
#include <vector>
#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"

class SceneMgr
{
private:
	CGameObject* m_Back;
	vector<CGameObject> obj;
	int m_nObject;
	float shoottime;
	float settime;
	Renderer* m_pRendertarget;
	GLuint m_BuildingTex[2];
	GLuint m_CharacterTex[2];
	GLuint m_BackGround;
	GLuint m_ParticleTex;
	int m_nIndex;

	float m_fParticleTime{ 0 };

public:
	SceneMgr(Renderer* ren);
	~SceneMgr();

	void Render();
	void Update(float timeelapsed);
	CGameObject AddObject(Vector pos, int type, int tnum, int p = -1);
	bool Colide(CGameObject a, CGameObject b);

	void SetPlayerCharacter(Vector pos);
};

