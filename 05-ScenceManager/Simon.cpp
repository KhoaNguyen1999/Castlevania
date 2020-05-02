#include "Simon.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Game.h"

#include "Goomba.h"
#include "Brick.h"
#include "Portal.h"
#include "Torch.h"
#include "VampireKiller.h"

Simon* Simon::_instance = NULL;

Simon* Simon::GetInstance()
{
	if (_instance == NULL) 
		_instance = new Simon();

	return _instance;
}

Simon::Simon() : CGameObject() {
	isAttack = false;
	isCrouch = false;
	isJump = false;
	untouchable = 0;
	SetState(SIMON_STATE_IDLE);
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (x < 0) x = 0;

	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);


	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (GetTickCount() - attack_time > SIMON_ATTACK_TIME) {
		isAttack = false;
		ResetAttackFrame();
	}


	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}


	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back SIMON if collides with a moving objects, what if SIMON is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj)) {
				//when touch brick -> activate jump
				if (e->ny < 0) {
 					isJump = false;
				}
			}

			if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				DebugOut(L"[INFO] Switching to scene %d", p->GetSceneId());
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	int ani = -1;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;

	else {
		if (isJump == true) {
			if (isAttack == false) {
				if (nx > 0) ani = SIMON_ANI_JUMP_RIGHT;
				else ani = SIMON_ANI_JUMP_LEFT;
			}

			else if (isAttack == true) {
				if (nx > 0) ani = SIMON_ANI_STAND_ATTACK_RIGHT;
				else ani = SIMON_ANI_STAND_ATTACK_LEFT;
			}
			
		}

		//idle state
		else if (vx == 0)
		{
			if (nx > 0) {
				if (isCrouch == true) {
					ani = SIMON_ANI_CROUCH_RIGHT;
					if (isAttack == true) 
						ani = SIMON_ANI_CROUCH_ATTACK_RIGHT;
				}
				else {
					ani = SIMON_ANI_IDLE_RIGHT;
					if (isAttack == true) {
						ani = SIMON_ANI_STAND_ATTACK_RIGHT;
					}
				}
					
			}
			else {
				if (isCrouch == true ) {
					ani = SIMON_ANI_CROUCH_LEFT;
					if (isAttack == true) ani = SIMON_ANI_CROUCH_ATTACK_LEFT;
				}

				else {
					ani = SIMON_ANI_IDLE_LEFT;
					if (isAttack == true) {
						ani = SIMON_ANI_STAND_ATTACK_LEFT;
					}
				}
					
			}
		}

		//move state
		else {
			if (vx > 0 && isJump == false)
				ani = SIMON_ANI_WALKING_RIGHT;
			else if (vx < 0 && isJump == false) ani = SIMON_ANI_WALKING_LEFT;
		}
		
	}

	int alpha = 255;
	if (untouchable) alpha = 128;


	animation_set->at(ani)->Render(x, y, alpha);

	

	RenderBoundingBox();
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{

	case SIMON_STATE_WALKING_RIGHT:
		if (isAttack == true) vx = 0;

		else 
			vx = SIMON_WALKING_SPEED;
		
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (isAttack == true) vx = 0;

		else
			vx = -SIMON_WALKING_SPEED;
		
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		if (isJump == false && isCrouch == false) {
			isJump = true;
			vy = -SIMON_JUMP_SPEED_Y;
		}
		break;

	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;

	case SIMON_STATE_CROUCH_IDLE:
		vx = 0;
		CrouchControl(true);
		break;
	case SIMON_STATE_CROUCH_RIGHT:
		vx = 0;
		nx = 1;
		CrouchControl(true);
		break;

	case SIMON_STATE_CROUCH_LEFT:
		vx = 0;
		nx = -1;
		CrouchControl(true);
		break;

	case SIMON_STATE_STAND_ATTACK:
		vx = 0;
		SetAttack(true);
		break;

	case SIMON_STATE_CROUCH_ATTACK:
		vx = 0;
		SetAttack(true);
		break;
	}
}

void Simon::CrouchControl(boolean isCrouch) {
	if (isCrouch == true) {
		this->isCrouch = true;
	}

	else {
		//set pull up to avoid out of map
		y -= SIMON_PULL_UP_SIT;
		this->isCrouch = false;
	}
}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	//change simon bounding box value later
	left = x;
	top = y;
	right = x + SIMON_BOX_WIDTH;

	if (isCrouch == false) {

		bottom = y + SIMON_BOX_HEIGHT;
	}


	if (isCrouch == true) {
		bottom = y + SIMON_BOX_CROUCH_HEIGHT;
	}


}

void Simon::SetAttack(boolean atk) {
	this->isAttack = atk;
	if (atk == true) {
		VampireKiller::GetInstance()->isAttack = true;
	}
}

void Simon::ResetAttackFrame() {
	for (int i = SIMON_ANI_STAND_ATTACK_RIGHT; i <= SIMON_ANI_CROUCH_ATTACK_LEFT; i++) {
		animation_set->at(i)->SetCurrentFrame(-1);
	}

}

void Simon::SetAttackTime(DWORD time) {
	this->attack_time = time;
}

boolean Simon::AttackState() {
	return this->isAttack;
}

