#pragma once
#include "GameObject.h"
#include "Game.h"
#include "GameObject.h"
#include "Simon.h"
#include "Torch.h"

#define VAMPIRE_KILLER_ATTACK_TIME	500
#define VAMPIRE_KILLER_FRAME_TIME	200

#define VAMPIRE_KILLER_STATE_INACTIVE				0
#define VAMPIRE_KILLER_STATE_STAND_ATTACK			100
#define VAMPIRE_KILLER_STATE_CROUCH_ATTACK			200

#define VAMPIRE_KILLER_ANI_ATTACK_RIGHT		0
#define VAMPIRE_KILLER_ANI_ATTACK_LEFT		1
#define VAMPIRE_KILLER_ANI_ORANGE_ATTACK_RIGHT		2
#define VAMPIRE_KILLER_ANI_ORANGE_ATTACK_LEFT		3

#define VAMPIRE_KILLER_LEVEL_NORMAL	0
#define VAMPIRE_KILLER_LEVEL_ORANGE	1
#define VAMPIRE_KILLER_LEVEL_PURPLE	2
#define VAMPIRE_KILLER_LEVEL_RED	3

#define VAMPIRE_KILLER_NORMAL_BEGIN_BOX_HEIGHT	30
#define VAMPIRE_KILLER_NORMAL_BEGIN_BOX_WIDTH	5

#define VAMPIRE_KILLER_NORMAL_MIDDLE_BOX_HEIGHT	20
#define VAMPIRE_KILLER_NORMAL_MIDDLE_BOX_WIDTH	5

#define VAMPIRE_KILLER_NORMAL_END_BOX_HEIGHT	10
#define VAMPIRE_KILLER_NORMAL_END_BOX_WIDTH		25

class VampireKiller : public CGameObject
{
private:
	int level;
	int activeTime;
	int currentVampireKillerFrame;
	static VampireKiller* _instance;
	DWORD attack_start;
	CGameObject* simon;

public:
	VampireKiller();
	static VampireKiller* GetInstance();
	int VampireKillerPosLoop;
	void SetPosition();
	void SetLevel(int value);
	int attackStart;
	int attack_pause;
	boolean active = false;

	void StartAttack();
	boolean isAttack;

	int GetCurrentAni(int ani) { return ani; }
	void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

