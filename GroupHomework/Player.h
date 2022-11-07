#pragma once
#ifndef _TEST_Player
#define _TEST_Player

enum CameraMode {
	EULER_ROTATION,
	FREE_ROTATION
};

class Player {
public:
	CVector767 pos0, pos;
	CEuler767 dir0, dir; //Euler Mode
	CMatrix767 M0, E0, View_M0;
	CMatrix767 ML, EL, View_ML;
	CMatrix767 EG, View_MG, IView_MG;
	Player() {};
	Player(CVector767 pos, CEuler767 dir):
		pos(pos),
		dir(dir)
	{
		Reset();
		Update(EULER_ROTATION);
	};
	//void Initialize();
	void Update(CameraMode);
	void Reset();
	void Set_Init(const CVector767&, const CEuler767&);
	void Set_Local(const CVector767&, const CEuler767&);
	void Move_x(const float&, CameraMode);
	void Move_y(const float&, CameraMode);
	void Move_z(const float&, CameraMode);
	void Rotate_h(const float&, CameraMode);
	void Rotate_p(const float&, CameraMode);
	void Rotate_b(const float&, CameraMode);
	//Binding
	void Bind_Bubble(Bubble*);
	//Slerp
	CMatrix767 Slerp(Player&, const float&);
};

#endif