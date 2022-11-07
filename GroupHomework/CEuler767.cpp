#include "stdafx.h"
#include "Pch.h"

const float CEuler767::euler_eps = 89.9999f;

string CEuler767::toString() {
	return Util::format("%.2f,%.2f,%.2f", h, p, b);
}

void CEuler767::Reset() {
	h = 0.0f, p = 0.0f, b = 0.0f;
}

void CEuler767::Set(const float& h_, const float& p_, const float& b_) {
	h = h_, p = p_, b = b_;
}

CVector767 CEuler767::ToVector3() {
	float h_rad = Util::DegToRad(h), p_rad = Util::DegToRad(p), b_rad = Util::DegToRad(b);
	float nx = -cos(p_rad)*sin(h_rad);
	float ny = sin(p_rad);
	float nz = -cos(p_rad)*cos(h_rad);
	return CVector767(nx, ny, nz);
}

CMatrix767 CEuler767::ToMatrix() {
	CMatrix767 ry, rx, rz;
	ry.SetRotate(h, CVector767(0, 1, 0));
	rx.SetRotate(p, CVector767(1, 0, 0));
	rz.SetRotate(b, CVector767(0, 0, 1));
	return ry * rx * rz;
}

void CEuler767::Normalize() {
	h = Util::WrapAngle(h), p = Util::WrapAngle(p), b = Util::WrapAngle(b);
	if (p > CEuler767::euler_eps) {
		p = CEuler767::euler_eps;
	}
	if (p < -CEuler767::euler_eps) {
		p = -CEuler767::euler_eps;
	}
}

CQuaternion767 CEuler767::ToQuaternion() {
	float h2 = Util::DegToRad(h/2), p2 = Util::DegToRad(p/2), b2 = Util::DegToRad(b/2);
	CQuaternion767 qh = CQuaternion767(0,sin(h2),0,cos(h2));
	CQuaternion767 qp = CQuaternion767(sin(p2),0,0,cos(p2));
	CQuaternion767 qb = CQuaternion767(0,0,sin(b2),cos(b2));
	return qh * qp * qb;
}