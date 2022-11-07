#include "stdafx.h"
#include "Pch.h"

CVector767 CVector767::default_vector = CVector767(1, 0, 0);

string CVector767::toString() {
	return Util::format("%.2f,%.2f,%.2f", x, y, z);
}

void CVector767::Reset() {
	x = 0.0f, y = 0.0f, z = 0.0f;
}

void CVector767::Set(const float& x_, const float& y_, const float& z_) {
	x = x_, y = y_, z = z_;
}

CVector767& CVector767::operator=(const CVector767& other){
	Set(other.x, other.y, other.z);
	return *this;
}

CVector767 operator+(const CVector767& a, const CVector767& b) {
	return CVector767(a.x + b.x, a.y + b.y, a.z + b.z);
}

CVector767 operator-(const CVector767& a, const CVector767& b) {
	return CVector767(a.x - b.x, a.y - b.y, a.z - b.z);
}

CVector767 CVector767::operator- () {
	return CVector767(-x,-y,-z);
}

CVector767 operator*(const float& n, const CVector767& v) {
	return CVector767(n * v.x, n * v.y, n * v.z);
}

inline float CVector767::dotMul(const CVector767& other) {
	return x * other.x + y * other.y + z * other.z;
}

CVector767 CVector767::crossMul(const CVector767& other) {
	return CVector767(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

bool operator == (const CVector767& a, const CVector767& b) {
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

bool operator != (const CVector767& a, const CVector767& b) {
	return (a.x != b.x || a.y != b.y || a.z != b.z);
}

float CVector767::len() {
	return sqrt(len2());
}

float CVector767::len2() {
	return x*x + y*y + z*z;
}

bool CVector767::Normalize() {
	float l = len();
	if (l == 0.0f) {
		(*this) = default_vector;
		return 0;
	}
	x /= l, y /= l, z /= l;
	return 1;
}

CVector767 CVector767::GetNormalize() {
	float l = len();
	if (l == 0.0f) {
		return default_vector;
	}
	CVector767 ret = (*this);
	ret.x /= l, ret.y /= l, ret.z /= l;
	return ret;
}

CVector767 CVector767::project(CVector767& other) {
	return (dotMul(other)/other.len2()) * other;
}

CVector767 CVector767_ext::To3DVector() {
	return CVector767(x, y, z);
}

CEuler767 CVector767::ToEuler() {
	CVector767 n = GetNormalize();
	float p = asin(n.y);
	float l = sqrt(1 - n.y*n.y);
	float h = 0.0f;
	if (l > 0.0f) {
		h = atan2(-n.x,-n.z);
	}
	h = Util::RadToDeg(h), p = Util::RadToDeg(p);
	return CEuler767(h, p, 0);
}

CVector767 CVector767::Slerp(CVector767& other, const float& t) {
	CVector767 va = (*this), d = other - (*this);
	return va + t * d;
}

CVector767 CVector767::Find_Bisector(CVector767& v1, CVector767& v2) {
	CVector767 n1 = v1.GetNormalize(), n2 = v2.GetNormalize();
	CVector767 n = n1 + n2;
	//Special case: if n1 == -n2, just pick any vector perpendicular to n1
	if (n.len() == 0.0f) {
		return CVector767(n1.y, -n1.x, 0).GetNormalize();
	}
	return n.GetNormalize();
}