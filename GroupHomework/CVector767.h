#pragma once

#ifndef _TEST_CVector767
#define _TEST_CVector767

class CVector767 {
public:
	static CVector767 default_vector;
	static CVector767 Find_Bisector(CVector767&, CVector767&);
	float x,y,z;
	CVector767(){
		Reset();
	};
	CVector767(float x, float y, float z) :x(x), y(y), z(z) {};
	CVector767(const CVector767& other) {
		(*this) = other;
	}
	//Basic Operations
	void Reset();
	void Set(const float&, const float&, const float&);
	operator float* () { return &x; };
	operator const float* () const { return &x; };
	CVector767& operator = (const CVector767&);
	CVector767 operator - ();
	friend CVector767 operator + (const CVector767&, const CVector767&);
	friend CVector767 operator - (const CVector767&, const CVector767&);
	friend CVector767 operator * (const float&, const CVector767&);
	float dotMul(const CVector767&);
	CVector767 crossMul(const CVector767&);
	friend bool operator == (const CVector767&, const CVector767&);
	friend bool operator != (const CVector767&, const CVector767&);
	float len();
	float len2();
	bool Normalize();
	CVector767 GetNormalize();
	string toString();
	CVector767 project(CVector767&);
	//Euler Angles Convertion
	CEuler767 ToEuler();
	//Slerp
	CVector767 Slerp(CVector767&, const float&);
};

class ColoredVector767 : public CVector767{
public:
	float r, g, b;
	ColoredVector767() {};
	ColoredVector767(float x, float y, float z,float r,float g,float b) :CVector767(x,y,z), r(r), g(g), b(b) {};
};

class CVector767_ext : public CVector767 {
public:
	float w;
	CVector767_ext() {};
	CVector767_ext(CVector767 v, float w) : CVector767(v), w(w){};
	CVector767_ext(float x, float y, float z, float w) :CVector767(x, y, z), w(w){};
	CVector767 To3DVector();
};

#endif