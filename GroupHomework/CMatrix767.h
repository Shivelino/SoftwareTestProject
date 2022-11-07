#pragma once

#ifndef _TEST_CMatrix767
#define _TEST_CMatrix767

class CMatrix767
{
public:
	float m00, m10, m20, m30;
	float m01, m11, m21, m31;
	float m02, m12, m22, m32;
	float m03, m13, m23, m33;
	CMatrix767() {
		Reset();
	};
	CMatrix767(const CMatrix767& other) {
		(*this) = other;
	};
	CMatrix767(float* other) {
		Set(other);
	};
	//Basic Operations
	void Reset();
	void Set(float*);
	operator float* (){ return &m00; };
	operator const float* () const { return &m00; };
	CMatrix767& operator = (const CMatrix767&);
	CMatrix767& operator *= (const float&);
	friend CMatrix767 operator * (const float&, const CMatrix767&);
	friend CMatrix767 operator * (const CMatrix767&, const CMatrix767&);
	friend CVector767_ext operator * (const CMatrix767&, const CVector767_ext&);
	CVector767 vecMul(const CVector767&);
	CVector767 posMul(const CVector767&);
	void SetRotate(const float&, const CVector767&);
	void SetTrans(const CVector767&);
	void SetScale(const CVector767&);
	void SetIdentity();
	float Det();
	float Inverse();
	CMatrix767 GetInverse();
	string toString();
	string matrixShow();
	//Euler Angle Convertion
	CEuler767 ToEuler();
	CQuaternion767 ToQuaternion();
};

#endif