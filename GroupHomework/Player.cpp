#include "stdafx.h"
#include "glut.h"
#include "Pch.h"
#include "Player.h"
#include "Bubble.h"

void Player::Reset() { //Initial position
	pos0.Reset(), dir0.Reset();
	Update(EULER_ROTATION);
}

void Player::Set_Init(const CVector767& pos0_, const CEuler767& dir0_) { //Initial position
	pos0 = pos0_, dir0 = dir0_;
	Update(EULER_ROTATION);
}

void Player::Set_Local(const CVector767& pos_, const CEuler767& dir_) {
	pos = pos_, dir = dir_;
	Update(EULER_ROTATION);
}

void Player::Update(CameraMode mode) {
	M0.SetTrans(pos0);
	E0 = dir0.ToMatrix();
	View_M0 = M0 * E0;
	ML.SetTrans(pos);
	if (mode == FREE_ROTATION) {
		dir = EL.ToEuler();
	}
	dir.Normalize();
	EL = dir.ToMatrix();
	EG = E0 * EL;
	View_ML = ML * EL;
	View_MG = View_M0 * View_ML;
	IView_MG = View_MG.GetInverse();
}

void Player::Move_x(const float& t, CameraMode mode) {
	CVector767 d = CVector767(View_ML.m00, View_ML.m10, View_ML.m20);
	pos = pos + t * d;
	Update(mode);
}

void Player::Move_y(const float& t, CameraMode mode) {
	CVector767 d = CVector767(View_ML.m01, View_ML.m11, View_ML.m21);
	pos = pos + t * d;
	Update(mode);
}

void Player::Move_z(const float& t, CameraMode mode) {
	CVector767 d = CVector767(View_ML.m02, View_ML.m12, View_ML.m22);
	pos = pos + t * d;
	Update(mode);
}

void Player::Rotate_h(const float& t, CameraMode mode) {
	if (mode == EULER_ROTATION) {
		dir.h += t;
	}
	if (mode == FREE_ROTATION) {
		CMatrix767 T;
		T.SetRotate(t,CVector767(0, 1, 0));
		EL = EL * T;
	}
	Update(mode);
}

void Player::Rotate_p(const float& t, CameraMode mode) {
	if (mode == EULER_ROTATION) {
		dir.p += t;
	}
	if (mode == FREE_ROTATION) {
		CMatrix767 T;
		T.SetRotate(t, CVector767(1, 0, 0));
		EL = EL * T;
	}
	Update(mode);
}

void Player::Rotate_b(const float& t, CameraMode mode) {
	if (mode == EULER_ROTATION) {
		dir.b += t;
	}
	if (mode == FREE_ROTATION) {
		CMatrix767 T;
		T.SetRotate(t, CVector767(0, 0, 1));
		EL = EL * T;
	}
	Update(mode);
}

void Player::Bind_Bubble(Bubble* other) {
	if (other != NULL) {
		Set_Init(other->pos, other->E.ToEuler());
	}
}

CMatrix767 Player::Slerp(Player& other, const float& t) {
	CVector767 va = View_M0.posMul(pos), vb = other.View_M0.posMul(other.pos);
	CVector767 vc = va.Slerp(vb, t);
	CQuaternion767 qa = EG.ToQuaternion(), qb = other.EG.ToQuaternion();
	CQuaternion767 qc = qa.Slerp(qb, t);
	CMatrix767 M;
	M.SetTrans(vc);
	return (M * qc.ToMatrix()).GetInverse();
}