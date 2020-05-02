#pragma once
#include "Simon.h"
#include "GameObject.h"

#define TORCH_STATE_PILLAR	0
#define TORCH_STATE_CANDLE	100
#define TORCH_STATE_DESTROY	900


#define TORCH_PILLAR_HEIGHT	14
#define TORCH_PILLAR_WIDTH	16


class Torch : public CGameObject
{
	boolean isActive;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetActive(boolean touch);
};

