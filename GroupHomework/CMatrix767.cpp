#include "stdafx.h"
#include "Pch.h"

string CMatrix767::toString() {
	float* mat = *this;
	string ret;
	for (int i = 0; i < 16; i++) {
		ret += Util::format("%.2f", mat[i]);
		if (i < 15) ret += ',';
	}
	return ret;
}

string CMatrix767::matrixShow() {
	float* mat = *this;
	string out[4], ret;
	int top = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out[j] += Util::format("%.2f", mat[top]);
			if (i < 3) out[j] += ' ';
			top++;
		}
	}
	for (int i = 0; i < 4; i++) {
		ret += out[i];
		if (i < 3) ret += '\n';
	}
	return ret;
}

void CMatrix767::Reset() {
	float* mat = *this;
	for (int i = 0; i < 16; i++) {
		mat[i] = 0.0f;
	}
}

void CMatrix767::Set(float* other) {
	float* mat = *this;
	for (int i = 0; i < 16; i++) {
		mat[i] = other[i];
	}
}

void CMatrix767::SetIdentity() {
	m00 = 1.0f, m01 = 0.0f, m02 = 0.0f, m03 = 0.0f;
	m10 = 0.0f, m11 = 1.0f, m12 = 0.0f, m13 = 0.0f;
	m20 = 0.0f, m21 = 0.0f, m22 = 1.0f, m23 = 0.0f;
	m30 = 0.0f, m31 = 0.0f, m32 = 0.0f, m33 = 1.0f;
}

CMatrix767& CMatrix767::operator = (const CMatrix767& other) {
	float* mat = *this;
	for (int i = 0; i < 16; i++) {
		mat[i] = other[i];
	}
	return *this;
}

CMatrix767 operator * (const float& lambda, const CMatrix767& other) {
	CMatrix767 ret = other;
	for (int i = 0; i < 16; i++) {
		ret[i] *= lambda;
	}
	return ret;
}

CMatrix767& CMatrix767::operator *= (const float& lambda) {
	float* mat = *this;
	for (int i = 0; i < 16; i++) {
		mat[i] *= lambda;
	}
	return *this;
}

CMatrix767 operator * (const CMatrix767& A_, const CMatrix767& B_) {
	CMatrix767 ret;
	const float (*A)[4] = (const float(*)[4])(&A_);
	const float (*B)[4] = (const float(*)[4])(&B_);
	float (*C)[4] = (float(*)[4])(&ret);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			C[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				C[i][j] += A[k][j] * B[i][k];
			}
		}
	}
	return ret;
}

CVector767_ext operator * (const CMatrix767& A_, const CVector767_ext& v) {
	CVector767_ext ret;
	const float(*A)[4] = (const float(*)[4])(&A_);
	for (int i = 0; i < 4; i++) {
		ret[i] = 0;
		for (int k = 0; k < 4; k++) {
			ret[i] += A[k][i] * v[k];
		}
	}
	return ret;
}

CVector767 CMatrix767::vecMul(const CVector767& v) {
	return ((*this) * CVector767_ext(v, 0.0f)).To3DVector();
}

CVector767 CMatrix767::posMul(const CVector767& v) {
	return ((*this) * CVector767_ext(v, 1.0f)).To3DVector();
}

float CMatrix767::Det() {
	return m00*(m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31)
	- m01*(m10*m22*m33 + m12*m23*m30 + m13*m20*m32 - m10*m23*m32 - m12*m20*m33 - m13*m22*m30)
	+ m02*(m10*m21*m33 + m11*m23*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 - m13*m21*m30)
	- m03*(m10*m21*m32 + m11*m22*m30 + m12*m20*m31 - m10*m22*m31 - m11*m20*m32 - m12*m21*m30);
}

CMatrix767 CMatrix767::GetInverse() {
	CMatrix767 ret;
	float det = Det();
	if (det != 0.0f) {
		ret.m00 =  (m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31) / det;
		ret.m10 = -(m10*m22*m33 + m12*m23*m30 + m13*m20*m32 - m10*m23*m32 - m12*m20*m33 - m13*m22*m30) / det;
		ret.m20 =  (m10*m21*m33 + m11*m23*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 - m13*m21*m30) / det;
		ret.m30 = -(m10*m21*m32 + m11*m22*m30 + m12*m20*m31 - m10*m22*m31 - m11*m20*m32 - m12*m21*m30) / det;

		ret.m01 = -(m01*m22*m33 + m02*m23*m31 + m03*m21*m32 - m01*m23*m32 - m02*m21*m33 - m03*m22*m31) / det;
		ret.m11 =  (m00*m22*m33 + m02*m23*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 - m03*m22*m30) / det;
		ret.m21 = -(m00*m21*m33 + m01*m23*m30 + m03*m20*m31 - m00*m23*m31 - m01*m20*m33 - m03*m21*m30) / det;
		ret.m31 =  (m00*m21*m32 + m01*m22*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 - m02*m21*m30) / det;

		ret.m02 =  (m01*m12*m33 + m02*m13*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 - m03*m12*m31) / det;
		ret.m12 = -(m00*m12*m33 + m02*m13*m30 + m03*m10*m32 - m00*m13*m32 - m02*m10*m33 - m03*m12*m30) / det;
		ret.m22 =  (m00*m11*m33 + m01*m13*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 - m03*m11*m30) / det;
		ret.m32 = -(m00*m11*m32 + m01*m12*m30 + m02*m10*m31 - m00*m12*m31 - m01*m10*m32 - m02*m11*m30) / det;

		ret.m03 = -(m01*m12*m23 + m02*m13*m21 + m03*m11*m22 - m01*m13*m22 - m02*m11*m23 - m03*m12*m21) / det;
		ret.m13 =  (m00*m12*m23 + m02*m13*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 - m03*m12*m20) / det;
		ret.m23 = -(m00*m11*m23 + m01*m13*m20 + m03*m10*m21 - m00*m13*m21 - m01*m10*m23 - m03*m11*m20) / det;
		ret.m33 =  (m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 - m02*m11*m20) / det;
	}
	return ret;
}

float CMatrix767::Inverse() {
	float det = Det();
	if (det != 0.0f) {
		*this = GetInverse();
	}
	return det;
}

void CMatrix767::SetRotate(const float& angle,const CVector767& v) {
	CVector767 n = v;
	n.Normalize();
	float rad = Util::DegToRad(angle);
	float a = cos(rad), b = 1 - a, c = sin(rad);
	m00 = n.x * n.x * b +       a, m01 = n.x * n.y * b - n.z * c, m02 = n.x * n.z * b + n.y * c, m03 = 0.0f;
	m10 = n.x * n.y * b + n.z * c, m11 = n.y * n.y * b +       a, m12 = n.y * n.z * b - n.x * c, m13 = 0.0f;
	m20 = n.x * n.z * b - n.y * c, m21 = n.y * n.z * b + n.x * c, m22 = n.z * n.z * b +       a, m23 = 0.0f;
	m30 = 0.0f                   , m31 = 0.0f                   , m32 = 0.0f                   , m33 = 1.0f;
}

void CMatrix767::SetTrans(const CVector767& v) {
	m00 = 1.0f, m01 = 0.0f, m02 = 0.0f, m03 = v.x;
	m10 = 0.0f, m11 = 1.0f, m12 = 0.0f, m13 = v.y;
	m20 = 0.0f, m21 = 0.0f, m22 = 1.0f, m23 = v.z;
	m30 = 0.0f, m31 = 0.0f, m32 = 0.0f, m33 = 1.0f;
}

void CMatrix767::SetScale(const CVector767& v) {
	m00 = v.x,  m01 = 0.0f, m02 = 0.0f, m03 = 0.0f;
	m10 = 0.0f, m11 = v.y,  m12 = 0.0f, m13 = 0.0f;
	m20 = 0.0f, m21 = 0.0f, m22 = v.z,  m23 = 0.0f;
	m30 = 0.0f, m31 = 0.0f, m32 = 0.0f, m33 = 1.0f;
}

CEuler767 CMatrix767::ToEuler() {
	float h = 0.0f, p = 0.0f, b = 0.0f;
	p = asin(-m12);
	if (Util::RoughEqual(cos(p),0.0f)) {
		h = atan2f(-m20, m00);
	}
	else {
		h = atan2f(m02, m22);
		b = atan2f(m10, m11);
	}
	h = Util::RadToDeg(h), p = Util::RadToDeg(p), b = Util::RadToDeg(b);
	return CEuler767(h,p,b);
}

CQuaternion767 CMatrix767::ToQuaternion() {
	return ToEuler().ToQuaternion();
}