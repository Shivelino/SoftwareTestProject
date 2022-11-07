#pragma once

#ifndef _TEST_Bubble
#define _TEST_Bubble

class Bubble : public CSphere767 {
public:
	static bool Comperator(Bubble*, Bubble*);
	static CVector767 default_vel;
	CVector767 vel, col;
	float speed;
	CMatrix767 E; //Local Coordinates
	//Properties
	float density, mass, volume;
	float dist_from_player;
	Bubble() : CSphere767() {
		speed = 0;
		density = 1; // The default density
		volume = 0;
		mass = 0;
		dist_from_player = 0;
	}
	//Basic Functions
	void Set_Init();
	void Calc_Properties();
	void Update();
	void Transition_By_Vector(CVector767&);
	void Adjust_By_Vector(const float&, CVector767&);
	void Bounce_By_Vector(const float&, CVector767&);
	void Absorb(Bubble&);
	//Movement Functions
	void Move(const float&);
	void Rotate_x(const float&);
	void Rotate_y(const float&);
};
#endif