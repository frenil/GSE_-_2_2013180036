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

	float Life;

	OOBB oobb;
public:
	bool colided;
	CGameObject();
	CGameObject(Vector pos, float s, Vector col,float a) :position(pos),size(s),color(col),alpha(a) {			
	speed= 100.f ;
	Life = 100.f;
	 moveto= Normalize( Vector((float)(1.f/(-50+rand()%100)), (float)(1.f / (-50+rand() % 100)), 0)) ;
	 oobb = {-size/2,size/2,size/2,-size/2};
	}
	~CGameObject();



	Vector Normalize(Vector v) {
		float L = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
		v.x = v.x / L;
		v.y = v.y / L;
		v.z = v.z / L;
		return v;
	}
	Vector GetPosition() { return position; }
	float GetSize() { return size; }
	Vector GetColor() { return color; }
	float Getalpha() { return alpha; }
	float GetSpeed() { return speed; }
	Vector GetMove() { return moveto; }
	float GetLife() { return Life; }

	OOBB GetOOBB() { 
		OOBB result;
		result.Right =oobb.Right + position.x;
		result.Left =oobb.Left + position.x;
		result.Down =oobb.Down + position.y;
		result.Up =oobb.Up + position.y;
		return result;
	}


	void SetColor(Vector col) { color = col; }
	void SetPosition(float px, float py) { position.x = px, position.y = py; }
	void SetRenderer(Renderer* ren) { renderer = ren; }
	void Translate(Vector v) { position = position + v; }
	void MultipleScale(float num) { size *= num; }
	void ChangeColor(Vector col) { color = col; }

	virtual void Render();
	virtual void Update(float timeelapsed);
};

class VerticalObject:public CGameObject{

public:
	VerticalObject(Vector pos, float s, Vector col, float a) :CGameObject(pos, s, col, a) { 
		speed = 0;
		moveto = Vector(0, 1, 0); }

};