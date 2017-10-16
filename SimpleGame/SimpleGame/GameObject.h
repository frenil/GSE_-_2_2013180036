#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "Renderer.h"

class CGameObject
{
protected:
	Renderer* renderer = nullptr;
	Vector position	;
	float size		;
	Vector color	;
	float alpha		;
					;
	float speed		;
	Vector moveto	;

public:
	CGameObject();
	CGameObject(Vector pos, float s, Vector col,float a) :position(pos),size(s),color(col),alpha(a) {			
	speed= 0.1f ;
	 moveto= Vector(1, 0.5f, 0) ;
	}
	~CGameObject();


	Vector GetPosition() { return position; }
	float GetSize() { return size; }
	Vector GetColor() { return color; }
	float Getalpha() { return alpha; }
	float GetSpeed() { return speed; }
	Vector GetMove() { return moveto; }

	void SetPosition(float px, float py) { position.x = px, position.y = py; }
	void SetRenderer(Renderer* ren) { renderer = ren; }
	void Translate(Vector v) { position = position + v; }
	void MultipleScale(float num) { size *= num; }
	void ChangeColor(Vector col) { color = col; }

	virtual void Render();
	virtual void Update();
};

class VerticalObject:public CGameObject{

public:
	VerticalObject(Vector pos, float s, Vector col, float a) :CGameObject(pos, s, col, a) { 
		speed = 0;
		moveto = Vector(0, 1, 0); }

};