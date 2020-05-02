#include "BackGrounds.h"

void BackGrounds::Render() {
	animation_set->at(0)->Render(x, y);
}

void BackGrounds::GetBoundingBox(float& l, float& t, float& r, float& b) {
	//ignore backgrounds
	
}