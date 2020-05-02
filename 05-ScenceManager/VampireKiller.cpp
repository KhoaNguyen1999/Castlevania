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
	activeTime = 0;
	currentVampireKillerFrame = 0;
	isAttack = false;
}


void VampireKiller::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (Simon::GetInstance()->GetState() != SIMON_STATE_DIE) {

		CGameObject::Update(dt);

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;


		//when simon atack 
		if (Simon::GetInstance()->AttackState() == true) {
			//update current position of vampire killer based on simon

			//update attack pos y when jump
			if (Simon::GetInstance()->isJump == true) {
				float currentPosY;
				float currentPosX;
				Simon::GetInstance()->GetPosition(currentPosX, currentPosY);
				y = currentPosY;
			}

			//update x, y based on simon
			if ((GetTickCount() - Simon::GetInstance()->GetAttackTime()) >= activeTime && isAttack == true) {

				//start frame
				if (activeTime == 0 && isAttack == true) {
					Simon::GetInstance()->GetPosition(x, y);
					currentVampireKillerFrame = 0;
				}

				if (activeTime >= (2 * VAMPIRE_KILLER_FRAME_TIME)) {
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
							currentVampireKillerFrame = 1;
						}

						//frame 2
						else if (activeTime < (2 * VAMPIRE_KILLER_FRAME_TIME)) {
							x += 1;
							y -= 3;
							currentVampireKillerFrame = 2;
						}
					}


					else if (Simon::GetInstance()->nx < 0) {
						//frame 1
						if (activeTime < VAMPIRE_KILLER_FRAME_TIME) {
							x += 20;
							y += 5;
							currentVampireKillerFrame = 1;
						}

						//frame 2
						else if (activeTime < (2 * VAMPIRE_KILLER_FRAME_TIME)) {
							x -= 4;
							y -= 2;
							currentVampireKillerFrame = 2;
						}
					}

					//increase time to calculate frame
					activeTime += VAMPIRE_KILLER_FRAME_TIME;


				}



			}


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
	if (Simon::GetInstance()->isAttack == true) {
		if (currentVampireKillerFrame == 0) {
			left = x;
			top = y;
			right = x + VAMPIRE_KILLER_NORMAL_BEGIN_BOX_WIDTH;
			bottom = y + VAMPIRE_KILLER_NORMAL_BEGIN_BOX_HEIGHT;
		}

		else if (currentVampireKillerFrame == 1) {
			left = x;
			top = y;
			right = x + VAMPIRE_KILLER_NORMAL_MIDDLE_BOX_WIDTH;
			bottom = y + VAMPIRE_KILLER_NORMAL_MIDDLE_BOX_HEIGHT;
		}

		else
		{
			left = x;
			top = y;
			right = x + VAMPIRE_KILLER_NORMAL_END_BOX_WIDTH;
			bottom = y + VAMPIRE_KILLER_NORMAL_END_BOX_HEIGHT;
		}
	}


}



