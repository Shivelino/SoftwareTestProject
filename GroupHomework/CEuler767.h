#pragma once

#ifndef _TEST_CEuler767
#define _TEST_CEuler767

class CEuler767 {
public:
	static const float euler_eps;
	float h, p, b; //Unit: Deg
	CEuler767() {
		Reset();
	};
	CEuler767(float h, float p, float b) :h(h), p(p), b(b) {};
	//Basic Operations
	void Reset();
	void Set(const float&, const float&, const float&);
	operator float*() { return &h; };
	string toString();
	void Normalize();
	//Euler Angles Convertion
	CVector767 ToVector3();
	CMatrix767 ToMatrix();
	CQuaternion767 ToQuaternion();
};

#endif