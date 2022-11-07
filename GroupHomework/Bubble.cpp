#include "stdafx.h"
#include "Pch.h"
#include "Bubble.h"

CVector767 Bubble::default_vel = CVector767(0, 0, -1);

void Bubble::Set_Init() {
	E = vel.ToEuler().ToMatrix(); //Set the default bank angle to 0
}

void Bubble::Calc_Properties() {
	volume = 4 * Util::Pi * pow(radius, 3) / 3;
	mass = density * volume;
}

void Bubble::Update() {
	vel = E.vecMul(default_vel);
}

void Bubble::Transition_By_Vector(CVector767& v) {
	CMatrix767 M_n, M_r;
	//Choose the acute angle of vel and v
	if (vel.dotMul(v) >= 0) {
		M_n.SetRotate(180, CVector767::Find_Bisector(vel, v));
		//Flip the x-axis, y-axis to keep the original position
		M_r.SetScale(CVector767(-1, -1, 1));
		
	}
	else {
		M_n.SetRotate(180, CVector767::Find_Bisector(-vel, v));
		//Flip the z-axis, y-axis is also flipped to keep coordinate right-handed
		M_r.SetScale(CVector767(1, -1, -1));
	}
	E = M_n * E * M_r;
	Update();
	speed = v.len();
}

void Bubble::Adjust_By_Vector(const float& simulate_speed, CVector767& n) {
	pos = pos + simulate_speed * speed * n;
}

void Bubble::Bounce_By_Vector(const float& simulate_speed, CVector767& n) {
	//Adjust the position by normal vector to avoid gluing
	Adjust_By_Vector(simulate_speed, n);
	//Find the final vector by breaking the coordinates along normal vector
	CVector767 vx = vel.project(n), vy = vel - vx;
	CVector767 v_final = speed * (-vx + vy);
	Transition_By_Vector(v_final);
}

void Bubble::Absorb(Bubble& b) {
	float vol = volume + b.volume;
	radius = pow((3 * vol)/(4 * Util::Pi), 1.0f / 3);
	Calc_Properties();
}

//Movement Functions
void Bubble::Move(const float& simulate_speed) {
	pos = pos + simulate_speed * speed * vel;
}

void Bubble::Rotate_x(const float& t) {
	CMatrix767 T;
	T.SetRotate(t, CVector767(0, 1, 0));
	E = E * T;
	Update();
}

void Bubble::Rotate_y(const float& t) {
	CMatrix767 T;
	T.SetRotate(t, CVector767(1, 0, 0));
	E = E * T;
	Update();
}

bool Bubble::Comperator(Bubble* x, Bubble* y) {
	return x->dist_from_player > y->dist_from_player;
}