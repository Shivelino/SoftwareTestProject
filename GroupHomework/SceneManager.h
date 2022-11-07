#pragma once

#ifndef _TEST_SceneManager
#define _TEST_SceneManager

enum PlayerState {
	FIRST_PERSON,
	THIRD_PERSON,
	TRANSITION
};

class SceneManager {
public:
	//static variables
	static const float raycast_maxdist;
	static Player start_first_position;
	static Player start_third_position;
	//Window width and height
	int global_window_width;
	int global_window_height;
	//Keyboard Detect
	static bool* key_dict;
	static bool* special_key_dict;
	static void Keyboard_Detect(const unsigned char&, const bool&);
	static void Keyboard_Detect_Special(const unsigned char&, const bool&);

	SceneManager() {
		transition_timer = 0;
		transition_state = THIRD_PERSON;
		goal_transition_state = THIRD_PERSON;
		isFreezed = 0;
		isPaused = 0;
	};
	//Initialize
	void Initialize();
	//Basic Functions
	void Reset_Position();
	void Reset_Binding();
	void Change_Mode(CameraMode);
	void Toggle_Pause();
	void Update_Timer();
	void Update_State();
	void ReturnToThird();
	void ReturnToFirst();
	void CameraTransition(Bubble*);
	void Window_Resize(const int&, const int&);
	void Window_Close();
	//Move Functions
	void Move_x(const float&);
	void Move_y(const float&);
	void Move_z(const float&);
	void Rotate_h(const float&);
	void Rotate_p(const float&);
	void Rotate_b(const float&);
	void Rotate_Bubble_x(const float&);
	void Rotate_Bubble_y(const float&);
	//Change Gears
	void Change_MoveSpeed(const int&);
	void Change_RotateSpeed(const int&);
	void Change_BubbleGlobalSpeed(const int&);
	void Change_BubbleRotateSpeed(const int&);
	//Mouse RayCast
	CRay767 Mouse_Raycast(const int&, const int&, const int&, const int&);
	Bubble* Detect_Bubble(CRay767&, const float&);
	//Keyboard Events
	void Mouse_Clicking_Events(const int&, const int&);
	void Keyboard_Events_Hold();
	void Keyboard_Events_Down(const unsigned char&);
	void Keyboard_Events_Down_Special(const unsigned char&);
	//Render Functions
	void Draw_Axis();
	void Draw_Ground();
	void Draw_HUD();
	void Render();
	void Set_LightSource();

private:
	//Public Variables
	Boundary_Box boundary_box;
	Player player_third_person;
	Player player_first_person;
	Player camera_A, camera_B;
	Gears move_speed_gear;
	Gears rotate_speed_gear;
	Gears bubble_global_speed_gear;
	Gears bubble_rotate_speed_gear;
	//State Variables
	Player* current_player;
	Bubble* binding_bubble;
	CameraMode camera_mode;
	float move_speed;
	float rotate_speed;
	float bubble_rotate_speed;
	//Matrices
	CMatrix767 View_Matrix;
	CMatrix767 Projection_Matrix;
	//Transition
	PlayerState transition_state;
	int transition_countdown;
	int transition_timer;
	PlayerState goal_transition_state;
	//Pause State
	bool isFreezed;
	bool isPaused;
	//Light Sources
	CVector767 light0_pos, light1_pos;
};

#endif