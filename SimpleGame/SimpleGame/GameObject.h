#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "Renderer.h"

class CGameObject
{
protected:
	Renderer* renderer = nullptr;
private:
	Vector position	{ 0, 0, 0 };
	float size		{ 0 };
	Vector color	{ 0, 0, 0 };
	float alpha		{ 0 };
public:
	CGameObject();
	CGameObject(Vector pos, float s, Vector col,float a) :position(pos),size(s),color(col),alpha(a) {}
	~CGameObject();

	Vector GetPosition() { return position; }
	float GetSize() { return size; }
	Vector GetColor() { return color; }
	float Getalpha() { return alpha; }

	void SetRenderer(Renderer* ren) { renderer = ren; }
	void Translate(Vector v) { position = position + v; }
	void MultipleScale(float num) { size *= num; }
	void ChangeColor(Vector col) { color = col; }

	void Render();
};

