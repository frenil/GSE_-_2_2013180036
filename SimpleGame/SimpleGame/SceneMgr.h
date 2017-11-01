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

public:
	SceneMgr();
	~SceneMgr();

	void Render();
	void Update(float timeelapsed);
	void AddObject(Vector pos, float s, int type, Renderer* ren);
	bool Colide(CGameObject a, CGameObject b);
};

