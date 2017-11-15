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
	position =position + (moveto*speed*timeelapsed);
	if (position.x >= WINW/2|| position.x <= -(WINW/2))
		moveto.x = moveto.x*-1;
	if (position.y >= WINH/2 || position.y <= -(WINH/2))
		moveto.y = moveto.y*-1;
}


void CGameObject::Render(Renderer* ren)
{
	if (m_Texture)
		ren->DrawTexturedRect(position.x, position.y, position.z, size, color.x, color.y, color.z, alpha, m_Texture);
	else
		ren->DrawSolidRect(position.x, position.y, position.z, size, color.x, color.y, color.z, alpha);
}

