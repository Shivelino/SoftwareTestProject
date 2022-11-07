#pragma once

#ifndef _TEST_CQuaternion767
#define _TEST_CQuaternion767

class CQuaternion767 {
public:
	static CQuaternion767 default_quaternion;
	float x, y, z, w;
	CQuaternion767() {
		Reset(); 
	};
	CQuaternion767(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {};
	CQuaternion767(CVector767 n, float w) :x(n.x), y(n.y), z(n.z), w(w) {};
	//Basic Operations
	void Reset();
	void Set(const float&, const float&, const float&, const float&);
	operator float*() { return &x; }
	void SetAngle(const float&, const CVector767&);
	CQuaternion767& operator = (const CQuaternion767&);
	CQuaternion767 operator - ();
	friend CQuaternion767 operator + (const CQuaternion767&, const CQuaternion767&);
	friend CQuaternion767 operator - (const CQuaternion767&, const CQuaternion767&);
	friend CQuaternion767 operator * (const CQuaternion767&, const CQuaternion767&);
	friend CQuaternion767 operator * (const float&, const CQuaternion767&);
	float dotMul(const CQuaternion767&);
	float len();
	float len2();
	bool Normalize();
	CQuaternion767 GetNormalize();
	CQuaternion767 Conjugate();
	CQuaternion767& Inverse();
	CQuaternion767 GetInverse();
	CQuaternion767 Div(const CQuaternion767&); //a.Div(b): from a to b
	void GetAngle(float&, CVector767&); //angle unit: rad
	CQuaternion767 Slerp(const CQuaternion767&, const float&);
	void Slerp(const CQuaternion767&, const int&, float*, CQuaternion767*);
	string toString();
	//Euler Angles Convertion
	CEuler767 ToEuler();
	CMatrix767 ToMatrix();
};

#endif