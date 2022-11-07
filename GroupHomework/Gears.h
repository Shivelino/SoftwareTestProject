#pragma once

#ifndef _TEST_Gears
#define _TEST_Gears

class Gears {
public:
	int siz;
	int state;
	float* gears;
	float* binding_variable;
	Gears() {};
	Gears(int siz_,int state_, float* gears_, float* binding_variable_) {
		siz = siz_, state = state_, gears = gears_;
		binding_variable = binding_variable_;
		*binding_variable = gears[state];
	}
	void Change_Gear(const int&);
};

#endif