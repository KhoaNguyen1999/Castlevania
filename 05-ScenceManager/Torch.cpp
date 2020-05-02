#include "Torch.h"
#include "Simon.h"


void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (state != TORCH_STATE_DESTROY) {
		CGameObject::Update(dt);

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (Simon::GetInstance()->isAttack == true) {
				if (dynamic_cast<VampireKiller*>(coObjects->at(i))) {

					VampireKiller* torch = dynamic_cast<VampireKiller*>(coObjects->at(i));
					float l, t, r, b, l1, t1, r1, b1;
					GetBoundingBox(l, t, r, b);

					coObjects->at(i)->GetBoundingBox(l1, t1, r1, b1);

					if (!((l > r1) || (b1 < t) || (b < t1) || (l1 > r)))
					{
						state = TORCH_STATE_DESTROY;

					}

				}
			}
		}
	}
	
}

void Torch::Render()
{
	if (state != TORCH_STATE_DESTROY) {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
	

	
}

void Torch::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (Simon::GetInstance()->isAttack == true) {
		l = x;
		t = y;
		r = x + TORCH_PILLAR_WIDTH;
		b = y + TORCH_PILLAR_HEIGHT;
	}

	else {
		l = t = r = b = 0;
	}



}

void Torch::SetActive(boolean active) {
	active = false;
	this->isActive = active;
}
