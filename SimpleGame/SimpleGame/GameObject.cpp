#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::Render()
{
	renderer->DrawSolidRect(position.x, position.y, position.z, size, color.x, color.y, color.z, alpha);
}
