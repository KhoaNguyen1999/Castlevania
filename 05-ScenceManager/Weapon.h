#pragma once
#include "GameObject.h"
class Weapon : CGameObject
{
	
public:
	Weapon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void TorchCollision(DWORD dt, vector<LPGAMEOBJECT>& listObj);
};

