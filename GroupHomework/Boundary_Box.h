#pragma once

#ifndef _TEST_Boundary_Box
#define _TEST_Boundary_Box

class Boundary_Box : public CCube767 {
public:
	int num_bubbles;
	vector<Bubble*> bubble_array;
	float bubble_radius;
	float max_speed;
	float simulate_speed;
	Boundary_Box() {
		X_min = 0.0f, X_max = 0.0f, Y_min = 0.0f, Y_max = 0.0f, Z_min = 0.0f, Z_max = 0.0f;
		num_bubbles = 0;
	}
	Boundary_Box(float X_min, float X_max, float Y_min, float Y_max, float Z_min, float Z_max) : CCube767(X_min, X_max, Y_min, Y_max, Z_min, Z_max) {};
	void Random_Generate_Bubbles(const int&);
	//Simulate Functions
	void Simulate_Steps();
	void Simulate_Collision_Boundaries();
	void Simulate_Collision_Bubbles();
	void Simulate_Absorb_Bubbles(Bubble*);
	bool Calculate_Bubble_Collision(Bubble*, Bubble*);
	bool Calculate_Bubble_Absorb(Bubble*, Bubble*);
	void Sort_By_Distance(CVector767&);
};

#endif