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
	/*if (type == CHARACTER) {
		if (moveto.y > 0) {
			m_eDir = UP;
		}
		else
			m_eDir = DOWN;
		m_fTick += (timeelapsed * 5);
		if (m_fTick > 4.f)
			m_fTick -= 4.f;
	}*/
}


void CGameObject::Render(Renderer* ren)
{
	if (m_Texture) {
		if (type == CHARACTER) {
			UINT tick = (UINT)m_fTick;
			ren->DrawTexturedRectSeq(position.x, position.y, position.z, size,
				color.x, color.y, color.z, alpha,
				m_Texture,
				tick, m_eDir, 4, 4,
				Dlevel);
		}
		else
			ren->DrawTexturedRect(position.x, position.y, position.z, size, color.x, color.y, color.z, alpha, m_Texture, Dlevel);
	}
	else
		ren->DrawSolidRect(position.x, position.y, position.z, size, color.x, color.y, color.z, alpha, Dlevel);
	if (m_ParticleTex) {
		ren->DrawParticle(position.x, position.y, position.z, size, 1, 1, 1, 1, -moveto.x * 20, -moveto.y * 20, m_ParticleTex, timer);
	}
	if (type == BUILDING || type == CHARACTER) {
		Vector tmpCol;
		if (teamNum == 1)
			tmpCol = Vector(1, 0, 0);
		else if (teamNum == 2)
			tmpCol = Vector(0, 0, 1);
		ren->DrawSolidRectGauge(position.x, position.y + (size*0.5f) + 10, position.z, size, size / 5, tmpCol.x, tmpCol.y, tmpCol.z, alpha, Life / MaxLife, 0.1f);
	}
}

CCharacter::~CCharacter()
{
}

void CCharacter::Render(Renderer * ren)
{
}

void CCharacter::Update(float timeelapsed)
{
	timer += timeelapsed;
	position = position + (moveto*speed*timeelapsed);
	if (moveto.y > 0) {
		m_eDir = UP;
	}
	else
		m_eDir = DOWN;
	m_fTick += (timeelapsed * 5);
	if (m_fTick > 4.f)
		m_fTick -= 4.f;
}

CWarrior::~CWarrior()
{
}

void CWarrior::Update(float timeelapsed)
{
	CCharacter::Update(timeelapsed);
}
