#include "stdafx.h"
#include "Pch.h"

CQuaternion767 CQuaternion767::default_quaternion = CQuaternion767(1, 0, 0, 0);

string CQuaternion767::toString() {
	return Util::format("%.2f,%.2f,%.2f,%.2f", x, y, z, w);
}

void CQuaternion767::Reset() {
	x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
}

void CQuaternion767::Set(const float& x_, const float& y_, const float& z_, const float& w_) {
	x = x_, y = y_, z = z_, w = w_;
}

void CQuaternion767::SetAngle(const float& angle, const CVector767& axis) {
	float t = angle / 2;
	float st = sin(t), ct = cos(t);
	Set(axis.x * st, axis.y * st, axis.z * st, ct);
}

CQuaternion767& CQuaternion767::operator=(const CQuaternion767 &other) {
	Set(other.x, other.y, other.z, other.w);
	return *this;
}

CQuaternion767 operator+(const CQuaternion767 &a, const CQuaternion767 &b) {
	return CQuaternion767(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

CQuaternion767 operator-(const CQuaternion767 &a, const CQuaternion767 &b) {
	return CQuaternion767(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

CQuaternion767 CQuaternion767::operator- () {
	return CQuaternion767(-x, -y, -z, -w);
}

CQuaternion767 operator*(const float& lambda, const CQuaternion767& other) {
	return CQuaternion767(lambda * other.x, lambda * other.y, lambda * other.z, lambda * other.w);
}

CQuaternion767 operator*(const CQuaternion767& a, const CQuaternion767& b) {
	CVector767 va = CVector767(a.x, a.y, a.z), vb = CVector767(b.x, b.y, b.z);
	CVector767 v2 = a.w * vb + b.w * va + va.crossMul(vb);
	float w2 = a.w * b.w - va.dotMul(vb);
	return CQuaternion767(a.w * vb + b.w * va + va.crossMul(vb), a.w * b.w - va.dotMul(vb));
}

float CQuaternion767::len() {
	return sqrt(len2());
}

float CQuaternion767::len2() {
	return x*x + y*y + z*z + w*w;
}

bool CQuaternion767::Normalize() {
	float l = len();
	if (l == 0.0f) {
		(*this) = default_quaternion;
		return 0;
	}
	x /= l, y /= l, z /= l, w /= l;
	return 1;
}

CQuaternion767 CQuaternion767::GetNormalize() {
	float l = len();
	if (l == 0.0f) {
		return default_quaternion;
	}
	CQuaternion767 ret = (*this);
	ret.x /= l, ret.y /= l, ret.z /= l;
	return ret;
}

float CQuaternion767::dotMul(const CQuaternion767& other) {
	return x*other.x + y*other.y + z*other.z + w*other.w;
}

CQuaternion767 CQuaternion767::Conjugate() {
	return CQuaternion767(-x, -y, -z, w);
}

CQuaternion767& CQuaternion767::Inverse() {
	float l = len2();
	x = -x, y = -y, z = -z;
	x /= l, y /= l, z /= l, w /= l;
	return *this;
}

CQuaternion767 CQuaternion767::GetInverse() {
	CQuaternion767 ret = *this;
	return ret.Inverse();
}

void CQuaternion767::GetAngle(float& angle, CVector767& axis) {
	if (Normalize()) {
		angle = 2 * acos(w);
		CVector767 v = CVector767(x, y, z);
		if (v.Normalize()) {
			axis = v;
		}
	}
}

CQuaternion767 CQuaternion767::Div(const CQuaternion767& other) {
	return other * GetInverse();
}

CQuaternion767 CQuaternion767::Slerp(const CQuaternion767& Vend, const float& t) {
	CQuaternion767 qa = *this, qb = Vend;
	qa.Normalize(), qb.Normalize();
	CQuaternion767 d = qa.Div(qb);
	float angle = 0.0f;
	CVector767 v;
	d.GetAngle(angle, v);
	d.SetAngle(angle * t, v);
	return d * qa;
}

void CQuaternion767::Slerp(const CQuaternion767& Vend, const int& n, float* t, CQuaternion767* Result) {
	for (int i = 0; i < n; i++) {
		Result[i] = Slerp(Vend, t[i]);
	}
}

CMatrix767 CQuaternion767::ToMatrix() {
	CQuaternion767 q = GetNormalize();
	CMatrix767 ret;
	float qx = q.x, qy = q.y, qz = q.z, qw = q.w;
	ret.m00 = 1 - 2 * qy*qy - 2 * qz*qz; ret.m01 =     2 * qx*qy - 2 * qw*qz; ret.m02 =     2 * qx*qz + 2 * qw*qy;
	ret.m10 =     2 * qx*qy + 2 * qw*qz; ret.m11 = 1 - 2 * qx*qx - 2 * qz*qz; ret.m12 =     2 * qy*qz - 2 * qw*qx;
	ret.m20 =     2 * qx*qz - 2 * qw*qy; ret.m21 =     2 * qy*qz + 2 * qw*qx; ret.m22 = 1 - 2 * qx*qx - 2 * qy*qy;
	ret.m33 = 1;
	return ret;
}

CEuler767 CQuaternion767::ToEuler() {
	return ToMatrix().ToEuler();
}