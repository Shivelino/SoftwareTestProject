#include "stdafx.h"
#include "Pch.h"
#include "Geometry.h"

void CRay767::Set(const CVector767& pos_, const CVector767& dir_) {
	pos = pos_, dir = dir_;
}

float CRay767::Collision_Sphere(CSphere767& S) { //-1: Not Detected
	CVector767 vo = S.pos;
	CVector767 vl = S.pos - pos;
	CVector767 vn = vl.crossMul(dir);
	if (vn.len() <= S.radius) {
		float d = vl.dotMul(dir);
		if (d >= 0) {
			return d;
		}
	}
	return -1;
}

bool CSphere767::Collision_Sphere(CSphere767& S) {
	return (pos - S.pos).len() < (radius + S.radius);
}