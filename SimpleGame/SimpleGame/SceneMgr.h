#pragma once
#include <vector>
#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"
class SceneMgr
{
private:
	vector<CGameObject> obj;
public:
	SceneMgr();
	~SceneMgr();

	void Render();
	void Update();

	void AddObject(CGameObject* addobj, Renderer* ren);
	bool Colide(CGameObject a, CGameObject b);
};

