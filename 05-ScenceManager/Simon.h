#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.07f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.02f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_PULL_UP_SIT		5
#define SIMON_LOOK_RIGHT		1
#define SIMON_LOOK_LEFT			-1
#define SIMON_JUMP_COUNT		1

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_CROUCH_IDLE		500
#define SIMON_STATE_CROUCH_RIGHT	600
#define SIMON_STATE_CROUCH_LEFT		700
#define SIMON_STATE_STAND_ATTACK	800
#define SIMON_STATE_CROUCH_ATTACK	900


#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1


#define SIMON_ANI_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3

#define SIMON_ANI_CROUCH_RIGHT			4
#define SIMON_ANI_CROUCH_LEFT			5

#define SIMON_ANI_JUMP_RIGHT			4
#define SIMON_ANI_JUMP_LEFT				5

#define SIMON_ANI_STAND_ATTACK_RIGHT	6
#define SIMON_ANI_STAND_ATTACK_LEFT		7
#define SIMON_ANI_CROUCH_ATTACK_RIGHT	8
#define SIMON_ANI_CROUCH_ATTACK_LEFT	9


#define SIMON_ANI_DIE				10


#define SIMON_ATTACK_TIME	3000

#define SIMON_BOX_WIDTH  15
#define SIMON_BOX_HEIGHT 27

#define SIMON_BOX_CROUCH_WIDTH	15
#define SIMON_BOX_CROUCH_HEIGHT	22
#define	SIMON_STAND_UP_HEIGHT	7

#define SIMON_ATTACK_TIME		500
#define SIMON_UNTOUCHABLE_TIME 5000

class Simon : public CGameObject
{
	static Simon* _instance;
	int untouchable;
	DWORD untouchable_start;
	DWORD attack_time;

public:
	Simon();
	static Simon* GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	boolean isCrouch;
	boolean isJump;
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void CrouchControl(boolean isCrouch);
	void SetAttack(boolean attack);
	void StartAttack();
	void ResetAttackFrame();
	void SetAttackTime(DWORD time);
	DWORD GetAttackTime() { return this->attack_time; }
	boolean AttackState();
	boolean isAttack;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

