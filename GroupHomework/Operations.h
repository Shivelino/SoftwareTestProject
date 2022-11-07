#pragma once
#include "Pch.h"

#ifndef _TEST_Operations
#define _TEST_Operations

void readMatrix(CMatrix767& M) {
	for (int i = 0; i < 16; i++) {
		cin >> M[i];
		if (i < 15) cin.get();
	}
}

void readVector(CVector767& v) {
	for (int i = 0; i < 3; i++) {
		cin >> v[i];
		if (i < 2) cin.get();
	}
}

void readEuler(CEuler767& e) {
	for (int i = 0; i < 3; i++) {
		cin >> e[i];
		if (i < 2) cin.get();
	}
}

void readQuaternion(CQuaternion767& q) {
	for (int i = 0; i < 4; i++) {
		cin >> q[i];
		if (i < 3) cin.get();
	}
}

void readMatrix(ifstream& file_stream, CMatrix767& M) {
	for (int i = 0; i < 16; i++) {
		file_stream >> M[i];
		if (i < 15) file_stream.get();
	}
}

void readVector(ifstream& file_stream, CVector767& v) {
	for (int i = 0; i < 3; i++) {
		file_stream >> v[i];
		if (i < 2) file_stream.get();
	}
}

void readEuler(ifstream& file_stream, CEuler767& e) {
	for (int i = 0; i < 3; i++) {
		file_stream >> e[i];
		if (i < 2) file_stream.get();
	}
}

void readQuaternion(ifstream& file_stream, CQuaternion767& q) {
	for (int i = 0; i < 4; i++) {
		file_stream >> q[i];
		if (i < 3) file_stream.get();
	}
}

//Operations
string Operation_Vector_Add(ifstream& in_stream) {
	CVector767 va, vb;
	readVector(in_stream, va);
	readVector(in_stream, vb);
	CVector767 vc = va + vb;
	return va.toString() + '\t' + vb.toString() + '\t' + vc.toString();
}

string Operation_Vector_Dot(ifstream& in_stream) {
	CVector767 va, vb;
	readVector(in_stream, va);
	readVector(in_stream, vb);
	float f = va.dotMul(vb);
	return va.toString() + '\t' + vb.toString() + '\t' + Util::format("%.2f", f);
}

string Operation_Vector_Cross(ifstream& in_stream) {
	CVector767 va, vb;
	readVector(in_stream, va);
	readVector(in_stream, vb);
	CVector767 vc = va.crossMul(vb);
	return va.toString() + '\t' + vb.toString() + '\t' + vc.toString();
}

string Operation_Vector_Normalize(ifstream& in_stream) {
	CVector767 va;
	readVector(in_stream, va);
	CVector767 vc = va;
	vc.Normalize();
	return va.toString() + '\t' + vc.toString();
}

string Operation_Vector_Norm(ifstream& in_stream) {
	CVector767 va;
	readVector(in_stream, va);
	float f = va.len();
	return va.toString() + '\t' + Util::format("%.2f", f);
}

string Operation_Vector_Project(ifstream& in_stream) {
	CVector767 va, vb;
	readVector(in_stream, va);
	readVector(in_stream, vb);
	CVector767 vc = va.project(vb);
	return va.toString() + '\t' + vb.toString() + '\t' + vc.toString();
}

string Operation_Matrix_Multiplication(ifstream& in_stream) {
	CMatrix767 A, B;
	readMatrix(in_stream, A);
	readMatrix(in_stream, B);
	CMatrix767 C = A * B;
	return A.toString() + '\t' + B.toString() + '\t' + C.toString();
}

string Operation_Matrix_vecMul(ifstream& in_stream) {
	CMatrix767 A; CVector767 v;
	readMatrix(in_stream, A);
	readVector(in_stream, v);
	CVector767 v_out = A.vecMul(v);
	return A.toString() + '\t' + v.toString() + '\t' + v_out.toString();
}

string Operation_Matrix_posMul(ifstream& in_stream) {
	CMatrix767 A; CVector767 v;
	readMatrix(in_stream, A);
	readVector(in_stream, v);
	CVector767 v_out = A.posMul(v);
	return A.toString() + '\t' + v.toString() + '\t' + v_out.toString();
}

string Operation_Matrix_Rotate(ifstream& in_stream) {
	float angle; CMatrix767 A; CVector767 v;
	in_stream >> angle;
	readVector(in_stream, v);
	A.SetRotate(angle, v);
	return Util::format("%.2f", angle) + '\t' + v.toString() + '\t' + A.toString();
}

string Operation_Matrix_Translate(ifstream& in_stream) {
	CMatrix767 A;
	CVector767 v;
	readVector(in_stream, v);
	A.SetTrans(v);
	return v.toString() + '\t' + A.toString();
}

string Operation_Matrix_Scale(ifstream& in_stream) {
	CMatrix767 A;
	CVector767 v;
	readVector(in_stream, v);
	A.SetScale(v);
	return v.toString() + '\t' + A.toString();
}

string Operation_Matrix_Inverse(ifstream& in_stream) {
	CMatrix767 A;
	readMatrix(in_stream, A);
	CMatrix767 C = A.GetInverse();
	return A.toString() + '\t' + C.toString();
}

string Operation_Euler_toVector(ifstream& in_stream) {
	CEuler767 e;
	readEuler(in_stream, e);
	CVector767 v = e.ToVector3();
	CVector767 up = CVector767(0, 1, 0);
	return e.toString() + '\t' + v.toString() + '\t' + up.toString();
}

string Operation_Vector_toEuler(ifstream& in_stream) {
	CVector767 v;
	readVector(in_stream, v);
	CEuler767 e = v.ToEuler();
	return v.toString() + '\t' + e.toString();
}

string Operation_Euler_toQuaternion(ifstream& in_stream) {
	CEuler767 e;
	readEuler(in_stream, e);
	CQuaternion767 q = e.ToQuaternion();
	return e.toString() + '\t' + q.toString();
}

string Operation_Quaternion_toEuler(ifstream& in_stream) {
	CQuaternion767 q;
	readQuaternion(in_stream, q);
	CEuler767 e = q.ToEuler();
	return q.toString() + '\t' + e.toString();
}

string Operation_Euler_toMatrix(ifstream& in_stream) {
	CEuler767 e;
	readEuler(in_stream, e);
	CMatrix767 M = e.ToMatrix();
	return e.toString() + '\t' + M.toString();
}

string Operation_Matrix_toEuler(ifstream& in_stream) {
	CMatrix767 M;
	readMatrix(in_stream, M);
	CEuler767 e = M.ToEuler();
	return M.toString() + '\t' + e.toString();
}

string Operation_Matrix_toQuaternion(ifstream& in_stream) {
	CMatrix767 M;
	readMatrix(in_stream, M);
	CQuaternion767 q = M.ToQuaternion();
	return M.toString() + '\t' + q.toString();
}

string Operation_Quaternion_toMatrix(ifstream& in_stream) {
	CQuaternion767 q;
	readQuaternion(in_stream, q);
	CMatrix767 M = q.ToMatrix();
	return q.toString() + '\t' + M.toString();
}

string Operation_Euler_Normalize(ifstream& in_stream) {
	CEuler767 ea;
	readEuler(in_stream, ea);
	CEuler767 eb = ea;
	eb.Normalize();
	return ea.toString() + '\t' + eb.toString();
}

string Operation_Quaternion_Normalize(ifstream& in_stream) {
	CQuaternion767 qa;
	readQuaternion(in_stream, qa);
	CQuaternion767 qb = qa;
	qb.Normalize();
	return qa.toString() + '\t' + qb.toString();
}

string Operation_Quaternion_Product(ifstream& in_stream) {
	CQuaternion767 qa, qb;
	readQuaternion(in_stream, qa);
	readQuaternion(in_stream, qb);
	CQuaternion767 qc = qb * qa;
	return qa.toString() + '\t' + qb.toString() + '\t' + qc.toString();
}

string Operation_Quaternion_Division(ifstream& in_stream) {
	CQuaternion767 qa, qb;
	readQuaternion(in_stream, qa);
	readQuaternion(in_stream, qb);
	CQuaternion767 qc = qa.Div(qb);
	return qa.toString() + '\t' + qb.toString() + '\t' + qc.toString();
}

string Operation_Quaternion_Dot(ifstream& in_stream) {
	CQuaternion767 qa, qb;
	readQuaternion(in_stream, qa);
	readQuaternion(in_stream, qb);
	float f = qa.dotMul(qb);
	return qa.toString() + '\t' + qb.toString() + '\t' + Util::format("%.2f", f);
}

string Operation_Quaternion_Inverse(ifstream& in_stream) {
	CQuaternion767 qa;
	readQuaternion(in_stream, qa);
	CQuaternion767 qb = qa.GetInverse();
	return qa.toString() + '\t' + qb.toString();
}

string Operation_Quaternion_GetAngle(ifstream& in_stream) {
	CQuaternion767 qa;
	readQuaternion(in_stream, qa);
	float angle; CVector767 axis;
	qa.GetAngle(angle, axis);
	angle = Util::RadToDeg(angle);
	return qa.toString() + '\t' + Util::format("%.2f", angle) + '\t' + axis.toString();
}

string Operation_Quaternion_Slerp(ifstream& in_stream) {
	CQuaternion767 qa, qb;
	readQuaternion(in_stream, qa);
	readQuaternion(in_stream, qb);
	float t = 0.0f;
	in_stream >> t;
	CQuaternion767 qc = qa.Slerp(qb, t);
	return qa.toString() + '\t' + qb.toString() + '\t' + Util::format("%.2f", t) + '\t' + qc.toString();
}

#endif