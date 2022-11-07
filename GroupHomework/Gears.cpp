#include "stdafx.h"
#include "Pch.h"
#include "Gears.h"

void Gears::Change_Gear(const int& t) {
	state += t;
	if (state < 0) {
		state = 0;
	}
	else if (state >= siz) {
		state = siz - 1;
	}
	*binding_variable = gears[state];
}