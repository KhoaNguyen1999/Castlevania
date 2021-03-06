#pragma once
#include "Simon.h"
#include "VampireKiller.h"
#include "GameObject.h"



#define TORCH_STATE_NORMAL	0
#define TORCH_STATE_ITEM	100
#define TORCH_STATE_DESTROY	900

#define TORCH_ANI_NORMAL	0
#define	TORCH_ANI_HEART		1
#define TORCH_ANI_WHIP		2

#define HEART_VALUE	0
#define WHIP_VALUE	1


#define TORCH_PILLAR_HEIGHT	14
#define TORCH_PILLAR_WIDTH	16

#define ITEM_GRAVITY		0.00000005f


class Torch : public CGameObject
{
	static int nextTorchID;
	boolean isActive;
	boolean itemFall;
	static Torch* _instance;
public:
	Torch();
	Torch(const Torch& origin);
	Torch& operator=(const Torch& origin);
	static Torch* GetInstance();
	int currentAni;
	int torchID;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetActive(boolean touch);

	int itemValue;
};

