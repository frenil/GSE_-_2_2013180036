#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::Update(float timeelapsed)
{
	timer += timeelapsed;
	position = position + (moveto*speed*timeelapsed);
	if (type != BULLET || type != ARROW)
	{
		if (position.x >= WINW / 2 || position.x <= -(WINW / 2))
			moveto.x = moveto.x*-1;
		if (position.y >= WINH / 2 || position.y <= -(WINH / 2))
			moveto.y = moveto.y*-1;
	}
}


void CGameObject::Render(Renderer* ren)
{
	if (m_Texture)
		ren->DrawTexturedRect(position.x, position.y, position.z, size, color.x, color.y, color.z, alpha, m_Texture,Dlevel);
	else
		ren->DrawSolidRect(position.x, position.y, position.z, size, color.x, color.y, color.z, alpha,Dlevel);
	if (type == BUILDING || type == CHARACTER) {
		Vector tmpCol;
		if (teamNum == 1)
			tmpCol = Vector(1, 0, 0);
		else if (teamNum == 2)
			tmpCol = Vector(0, 0, 1);
		ren->DrawSolidRectGauge(position.x, position.y + (size*0.5f)+10, position.z, size,size/5, tmpCol.x, tmpCol.y, tmpCol.z, alpha, Life/MaxLife,0.1f);
	}
}

