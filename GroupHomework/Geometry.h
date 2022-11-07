#pragma once

#ifndef _TEST_Geometry
#define _TEST_Geometry

class CRay767 {
public:
	CVector767 pos, dir;
	CRay767() {};
	CRay767(CVector767 pos, CVector767 dir):pos(pos), dir(dir) {
		dir.Normalize();
	};
	//Basic Functions
	void Set(const CVector767&, const CVector767&);
	//Geometric Detection
	float Collision_Sphere(CSphere767&);
};

class CSphere767 {
public:
	CVector767 pos;
	float radius;
	CSphere767() {
		//cout << "CSphere767()" << endl;
		radius = 0.0f;
	};
	//Geometric Detection
	bool Collision_Sphere(CSphere767&);
};

class CCube767 {
public:
	float X_min, X_max;
	float Y_min, Y_max;
	float Z_min, Z_max;
	CCube767() {
		X_min = 0.0f, X_max = 0.0f, Y_min = 0.0f, Y_max = 0.0f, Z_min = 0.0f, Z_max = 0.0f;
	}
	CCube767(float X_min, float X_max, float Y_min, float Y_max, float Z_min, float Z_max) :
		X_min(X_min), X_max(X_max),
		Y_min(Y_min), Y_max(Y_max),
		Z_min(Z_min), Z_max(Z_max) {};
};

#endif