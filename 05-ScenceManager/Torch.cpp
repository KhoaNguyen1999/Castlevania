#include "Torch.h"
#include "Simon.h"
#include "Brick.h"


Torch* Torch::_instance = NULL;

Torch* Torch::GetInstance()
{
	if (_instance == NULL)
		_instance = new Torch();

	return _instance;
}

int Torch::nextTorchID = 0;

Torch::Torch() {
	state = TORCH_STATE_NORMAL;
	torchID = ++nextTorchID;
	itemFall = true;
}

Torch::Torch(const Torch& origin) {
	torchID = origin.torchID;
}

Torch& Torch::operator=(const Torch& origin) {
	torchID = origin.torchID;
	return (*this);
}

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);

	if (state == TORCH_STATE_DESTROY) {
		if (itemValue == WHIP_VALUE) {
			if(VampireKiller::GetInstance()->GetLevel() == VAMPIRE_KILLER_LEVEL_NORMAL)
				VampireKiller::GetInstance()->SetLevel(VAMPIRE_KILLER_LEVEL_ORANGE);

			if (VampireKiller::GetInstance()->GetLevel() == VAMPIRE_KILLER_LEVEL_ORANGE)
				VampireKiller::GetInstance()->SetLevel(VAMPIRE_KILLER_LEVEL_PURPLE);
		}
	}

	if (state != TORCH_STATE_DESTROY) {

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (Simon::GetInstance()->isAttack == true) {
				//collide with vampire killer
				if (dynamic_cast<VampireKiller*>(coObjects->at(i))) {

					float l, t, r, b, l1, t1, r1, b1;
					GetBoundingBox(l, t, r, b);

					coObjects->at(i)->GetBoundingBox(l1, t1, r1, b1);

					if (!((l > r1) || (b1 < t) || (b < t1) || (l1 > r)))
					{
						if (state == TORCH_STATE_NORMAL) {
							state = TORCH_STATE_ITEM;
						}
					}
				}
			}

			if (state == TORCH_STATE_ITEM) {
				if (itemFall == true) {
					vy += ITEM_GRAVITY * dt;

					vector<LPCOLLISIONEVENT> coEvents;
					vector<LPCOLLISIONEVENT> coEventsResult;

					coEvents.clear();
					CalcPotentialCollisions(coObjects, coEvents);

					float min_tx, min_ty, nx = 0, ny;
					float rdx = 0;
					float rdy = 0;

					FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

					y += min_ty * dy + ny * 0.4f;

					if (ny != 0) {
						vy = 0;
						itemFall = false;
					}
				}
						
			}
		}
	}
	
}

void Torch::Render()
{
	if (state != TORCH_STATE_DESTROY) {
		if (state == TORCH_STATE_NORMAL) {
			animation_set->at(0)->Render(x, y);
			RenderBoundingBox();
		}

		else {
			switch (this->torchID)
			{
			case 1:
				//render animation item heart here
				animation_set->at(TORCH_ANI_HEART)->Render(x, y);
				this->currentAni = TORCH_ANI_HEART;
				itemValue = HEART_VALUE;
				break;

			case 2:
				//render animation item whip here
				animation_set->at(TORCH_ANI_HEART)->Render(x, y);
				this->currentAni = TORCH_ANI_HEART;
				itemValue = HEART_VALUE;
				break;

			case 3:
				animation_set->at(TORCH_ANI_WHIP)->Render(x, y);
				this->currentAni = TORCH_ANI_WHIP;
				itemValue = WHIP_VALUE;
				break;

			case 4:
				animation_set->at(TORCH_ANI_WHIP)->Render(x, y);
				this->currentAni = TORCH_ANI_WHIP;
				itemValue = WHIP_VALUE;
				break;

			case 5:
				animation_set->at(TORCH_ANI_HEART)->Render(x, y);
				this->currentAni = TORCH_ANI_HEART;
				itemValue = HEART_VALUE;
				break;

			default:
				break;
			}
			state = TORCH_STATE_ITEM;

		}
		RenderBoundingBox();
	}
	
}

void Torch::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (state == TORCH_STATE_NORMAL) {
		if (Simon::GetInstance()->isAttack == true) {
			l = x;
			t = y;
			r = x + TORCH_PILLAR_WIDTH;
			b = y + TORCH_PILLAR_HEIGHT;
		}

		else if (Simon::GetInstance()->isAttack == false) {
			l = t = r = b = 0;
		}
	}

	else if (state == TORCH_STATE_ITEM) {
		l = x;
		t = y;
		r = x + 12;
		b = y + 15;
	}

	else {
		l = t=r=b=0;
	}

}

void Torch::SetActive(boolean active) {
	active = false;
	this->isActive = active;
}
