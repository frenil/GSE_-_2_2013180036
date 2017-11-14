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
	int m_nIndex;

public:
	SceneMgr(Renderer* ren);
	~SceneMgr();

	void Render();
	void Update(float timeelapsed);
	CGameObject AddObject(Vector pos, float s, int type, int p = -1);
	bool Colide(CGameObject a, CGameObject b);
};

