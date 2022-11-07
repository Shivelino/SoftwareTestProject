#include "stdafx.h"
#include "Pch.h"
#include "Bubble.h"
#include "Boundary_Box.h"

//Boundary Box
void Boundary_Box::Random_Generate_Bubbles(const int& bubble_num) {
	for (int i = 0; i < bubble_num; i++) {
		Bubble* b = new Bubble;
		b->radius = Util::Get_Random_Float(0.5f * bubble_radius, bubble_radius);
		b->pos = Util::Get_Random_Position(
			X_min + b->radius, X_max - b->radius,
			Y_min + b->radius, Y_max - b->radius,
			Z_min + b->radius, Z_max - b->radius
		);
		b->col = Util::Get_Random_Color();
		b->speed = Util::Get_Random_Float(0.25f * max_speed, max_speed);
		b->vel = Util::Get_Random_Direction();
		b->Set_Init();
		b->Calc_Properties();
		bubble_array.push_back(b);
	}
	num_bubbles = bubble_array.size();
}

void Boundary_Box::Simulate_Steps() {
	for (Bubble* b : bubble_array) {
		b->Move(simulate_speed);
	}
}

void Boundary_Box::Simulate_Collision_Boundaries() {
	for (Bubble* b : bubble_array) {
		if (b->pos.x < X_min + b->radius) {
			b->Bounce_By_Vector(simulate_speed, CVector767(1, 0, 0));
		}
		if (b->pos.x > X_max - b->radius) {
			b->Bounce_By_Vector(simulate_speed, CVector767(-1, 0, 0));
		}
		if (b->pos.y < Y_min + b->radius) {
			b->Bounce_By_Vector(simulate_speed, CVector767(0, 1, 0));
		}
		if (b->pos.y > Y_max - b->radius) {
			b->Bounce_By_Vector(simulate_speed, CVector767(0, -1, 0));
		}
		if (b->pos.z < Z_min + b->radius) {
			b->Bounce_By_Vector(simulate_speed, CVector767(0, 0, 1));
		}
		if (b->pos.z > Z_max - b->radius) {
			b->Bounce_By_Vector(simulate_speed, CVector767(0, 0, -1));
		}
	}
}

bool Boundary_Box::Calculate_Bubble_Collision(Bubble* b1, Bubble* b2) {
	if (b1 == b2 || !b1->Collision_Sphere(*b2)) {
		return 0;
	}
	CVector767 v1 = b1->speed * b1->vel, v2 = b2->speed * b2->vel;
	CVector767 x_axis = (b1->pos - b2->pos).GetNormalize();
	//Bump two bubbles along x_axis to avoid gluing
	b1->Adjust_By_Vector(simulate_speed, x_axis), b2->Adjust_By_Vector(simulate_speed, -x_axis);
	//Project the velocity vectors along x_axis
	CVector767 v1_x = v1.project(x_axis), v1_y = v1 - v1_x;
	CVector767 v2_x = v2.project(x_axis), v2_y = v2 - v2_x;
	//Calculate the velocity from perfectly elastic collision formula (vector form)
	float m1 = b1->mass, m2 = b2->mass;
	float mr = 1 / (m1 + m2);
	CVector767 v1_final_x = mr * ((m1 - m2) * v1_x + 2 * m2 * v2_x);
	CVector767 v2_final_x = mr * ((m2 - m1) * v2_x + 2 * m1 * v1_x);
	CVector767 v1_final = v1_final_x + v1_y, v2_final = v2_final_x + v2_y;
	//Transition the camera by vector
	b1->Transition_By_Vector(v1_final), b2->Transition_By_Vector(v2_final);
	return 1;
}

bool Boundary_Box::Calculate_Bubble_Absorb(Bubble* b1, Bubble* b2) {
	if (b1 == b2 || !b1->Collision_Sphere(*b2) || b1->volume <= b2->volume) {
		return 0;
	}
	CVector767 v1 = b1->speed * b1->vel, v2 = b2->speed * b2->vel;
	CVector767 x_axis = (b1->pos - b2->pos).GetNormalize();
	//Project the velocity vectors along x_axis
	CVector767 v1_x = v1.project(x_axis), v1_y = v1 - v1_x;
	CVector767 v2_x = v2.project(x_axis), v2_y = v2 - v2_x;
	//Calculate the velocity from perfectly inelastic collision formula (vector form)
	float m1 = b1->mass, m2 = b2->mass;
	float mr = 1 / (m1 + m2);
	CVector767 v1_final_x = mr * (m1 * v1_x + m2 * v2_x);
	CVector767 v1_final = v1_final_x + v1_y;
	//Transition the camera by vector
	b1->Transition_By_Vector(v1_final);
	b1->Absorb(*b2);
	return 1;
}

void Boundary_Box::Simulate_Collision_Bubbles() {
	for (int i = 0; i < num_bubbles; i++) {
		for (int j = i + 1; j < num_bubbles; j++) {
			Calculate_Bubble_Collision(bubble_array[i], bubble_array[j]);
		}
	}
}

void Boundary_Box::Simulate_Absorb_Bubbles(Bubble* binding_bubble) {
	if (binding_bubble == NULL) {
		return;
	}
	vector<Bubble*> V_tmp;
	for (Bubble* b : bubble_array) {
		if (Calculate_Bubble_Absorb(binding_bubble, b)) {
			delete b;
		}
		else {
			V_tmp.push_back(b);
		}
	}
	bubble_array = V_tmp;
	num_bubbles = bubble_array.size();
}

void Boundary_Box::Sort_By_Distance(CVector767& player_pos) {
	for (Bubble* b : bubble_array) {
		b->dist_from_player = (b->pos - player_pos).len();
	}
	sort(bubble_array.begin(), bubble_array.end(), Bubble::Comperator);
}