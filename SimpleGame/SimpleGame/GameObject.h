#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "Renderer.h"

class CGameObject
{
protected:
	int teamNum;

	Vector position	;
	float size		;
	Vector color	;
	float alpha		;
					;
	float speed		;
	Vector moveto	;
	int type;
	float Life;
	float MaxLife;
	float timer;
	float Dlevel;
	GLuint m_Texture = NULL;
	OOBB oobb;
public:
	bool colided;
	CGameObject();
	CGameObject(Vector pos, float s, Vector col,float a,int t,float level) :position(pos),size(s),color(col),alpha(a),type(t),Dlevel(level) {			
	speed= 100.f ;
	MaxLife = 100.f;
	Life = MaxLife;

	 moveto= Normalize( Vector((float)(1.f/(-50+rand()%100)), (float)(1.f / (-50+rand() % 100)), 0)) ;
	 oobb = {-size/2,size/2,size/2,-size/2};
	 timer = 0;
	}
	~CGameObject();



	Vector Normalize(Vector v) {
		float L = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
		v.x = v.x / L;
		v.y = v.y / L;
		v.z = v.z / L;
		return v;
	}
	float GetTimer() { return timer; }
	Vector GetPosition() { return position; }
	float GetSize() { return size; }
	Vector GetColor() { return color; }
	float Getalpha() { return alpha; }
	float GetSpeed() { return speed; }
	Vector GetMove() { return moveto; }
	float GetLife() { return Life; }
	float GetMaxLife() { return Life; }
	int GetTeam() { return teamNum; }
	OOBB GetOOBB() { 
		OOBB result;
		result.Right =oobb.Right + position.x;
		result.Left =oobb.Left + position.x;
		result.Down =oobb.Down + position.y;
		result.Up =oobb.Up + position.y;
		return result;
	}
	int GetType() { return type; }
	


	void Damage(float damage) { Life -= damage; }
	void SetColor(Vector col) { color = col; }
	void SetType(int T) { type = T; }
	void SetMove(Vector M) { moveto = M; }
	void SetMaxLife(float L) { Life= MaxLife = L; }
	void SetLife(float L) { Life = L; }
	void SetSpeed(float S) { speed = S; }
	void SetPosition(float px, float py) { position.x = px, position.y = py; }
	void SetTeam(int tnum) { teamNum = tnum; }
	void ResetTimer(float num) { timer -= num; }


	void SetTexture(GLuint tex) { m_Texture = tex; }

	void Translate(Vector v) { position = position + v; }
	void MultipleScale(float num) { size *= num; }
	void ChangeColor(Vector col) { color = col; }
	

	virtual void Render(Renderer* ren);
	virtual void Update(float timeelapsed);
};