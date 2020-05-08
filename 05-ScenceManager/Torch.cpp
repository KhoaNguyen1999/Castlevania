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
}

Torch::Torch(const Torch& origin) {
	torchID = origin.torchID;
}

Torch& Torch::operator=(const Torch& origin) {
	torchID = origin.torchID;
	return (*this);
}

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (state == TORCH_STATE_DESTROY) {
		if (itemValue == WHIP_VALUE) {
			VampireKiller::GetInstance()->SetLevel(1);
		}
	}

	if (state != TORCH_STATE_DESTROY) {
		CGameObject::Update(dt);

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (Simon::GetInstance()->isAttack == true) {
				//collide with vampire killer
				if (dynamic_cast<VampireKiller*>(coObjects->at(i))) {

					//VampireKiller* torch = dynamic_cast<VampireKiller*>(coObjects->at(i));
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
				animation_set->at(torchID)->Render(x, y);
				this->currentAni = TORCH_ANI_HEART;
				itemValue = HEART_VALUE;
				break;

			case 2:
				//render animation item whip here
				animation_set->at(torchID)->Render(x, y);
				this->currentAni = TORCH_ANI_WHIP;
				itemValue = WHIP_VALUE;
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
		r = x + TORCH_PILLAR_WIDTH;
		b = y + TORCH_PILLAR_HEIGHT;
	}

	else {
		l = t=r=b=0;
	}

}

void Torch::SetActive(boolean active) {
	active = false;
	this->isActive = active;
}
