#include "VampireKiller.h"

VampireKiller* VampireKiller::_instance = NULL;

VampireKiller* VampireKiller::GetInstance()
{
	if (_instance == NULL)
		_instance = new VampireKiller();

	return _instance;
}


VampireKiller::VampireKiller() {
	level = VAMPIRE_KILLER_LEVEL_NORMAL;
	SetState(VAMPIRE_KILLER_STATE_INACTIVE);
	VampireKillerPosLoop = 0;
	activeTime = 0;
	isAttack = false;
}

void VampireKiller::SetPosition() {
	Simon::GetInstance()->GetPosition(x, y);
	if (VampireKillerPosLoop == 1) {
		x += 100;
		VampireKillerPosLoop++;
	}


}

void VampireKiller::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	//if(simon->GetState() != SIMON_STATE_DIE)
		//CalcPotentialCollisions(coObjects, coEvents);

	//when simon atack 
	if (Simon::GetInstance()->AttackState() == true) {
		//update current position of vampire killer based on simon
		if ((GetTickCount() - Simon::GetInstance()->GetAttackTime()) >= activeTime && isAttack == true) {

			if (activeTime == 0 && isAttack == true) {
				Simon::GetInstance()->GetPosition(x, y);
			}

			if (activeTime >= (2* VAMPIRE_KILLER_FRAME_TIME)) {
				if (Simon::GetInstance()->nx > 0) {
					x += 22;
				}

				else {
					x -= 35;
				}
				
				y -= 1;
				isAttack = false;
				activeTime = 0;
			}
				

			else {
				if (Simon::GetInstance()->nx > 0) {
					//frame 1
					if (activeTime < VAMPIRE_KILLER_FRAME_TIME) {
						x -= 5;
						y += 5;
					}

					//frame 2
					else if (activeTime < (2* VAMPIRE_KILLER_FRAME_TIME)) {
						x += 1;
						y -= 3;
					}
				}
					

				else if (Simon::GetInstance()->nx < 0) {
					//frame 1
					if (activeTime < VAMPIRE_KILLER_FRAME_TIME) {
						x += 20;
						y += 5;
					}

					//frame 2
					else if (activeTime < (2 * VAMPIRE_KILLER_FRAME_TIME)) {
						x -= 4;
						y -= 2;
					}
				}
					
				
				activeTime += VAMPIRE_KILLER_FRAME_TIME;

				
			}

			
			
		}
		//Get simon position
		//SetPosition();
		//update follow frame


	}

	if (coEvents.size() == 0)
	{
		//no collision detected
		//Simon::GetInstance()->GetPosition(x, y);
	}



	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
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
		}
	}
}

void VampireKiller::Render() {
	int ani = -1;

	if (Simon::GetInstance()->AttackState() == true) {
		if (Simon::GetInstance()->nx < 0)
			ani = VAMPIRE_KILLER_ANI_ATTACK_LEFT;

		else {
			ani = VAMPIRE_KILLER_ANI_ATTACK_RIGHT;
		}


		int alpha = 255;

		animation_set->at(ani)->Render(x, y, alpha);

		RenderBoundingBox();
	}
	

}

void VampireKiller::SetState(int state) {
	switch (state)
	{
	case VAMPIRE_KILLER_STATE_CROUCH_ATTACK:
		break;

	case VAMPIRE_KILLER_STATE_STAND_ATTACK:
		break;


	default:
		break;
	}
}

void VampireKiller::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

}



