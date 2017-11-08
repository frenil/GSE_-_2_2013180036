#pragma once
#include <vector>
#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"

class SceneMgr
{
private:
	vector<CGameObject> obj;
	int m_nObject;
	float shoottime;
	Renderer* m_pRendertarget;
	GLuint m_BuildingTex;

public:
	SceneMgr(Renderer* ren);
	~SceneMgr();

	void Render();
	void Update(float timeelapsed);
	CGameObject AddObject(Vector pos, float s, int type);
	bool Colide(CGameObject a, CGameObject b);
};

