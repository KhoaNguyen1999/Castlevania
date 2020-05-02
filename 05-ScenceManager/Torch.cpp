#include "Torch.h"
#include "Simon.h"


void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != TORCH_STATE_DESTROY)
		CalcPotentialCollisions(coObjects, coEvents);

	else {
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


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];


			if (dynamic_cast<Simon*>(e->obj))
			{
				Simon* p = dynamic_cast<Simon*>(e->obj);
				if (p->AttackState() == true) {
					int a = 1;
				}
			}
		}


		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void Torch::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void Torch::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if(isActive != false) {
		l = x;
		t = y;
		r = x + TORCH_PILLAR_WIDTH;
		b = y + TORCH_PILLAR_HEIGHT;
	}

}

void Torch::SetActive(boolean active) {
	active = false;
	this->isActive = active;
}
