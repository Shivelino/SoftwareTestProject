#include "stdafx.h"
#include "Scene.h"

#define ESCAPE_KEY 27

const float SceneManager::raycast_maxdist = 1e3;
bool* SceneManager::key_dict = new bool[256]();
bool* SceneManager::special_key_dict = new bool[256]();
Player SceneManager::start_first_position = Player(CVector767(0, 0, 0), CEuler767(0, 0, 0));
Player SceneManager::start_third_position = Player(CVector767(0, 0, 0), CEuler767(0, 0, 0));

void SceneManager::Initialize() {
	//Initialize Variables
	global_window_width = 800;
	global_window_height = 600;
	camera_mode = EULER_ROTATION;
	current_player = &player_third_person;
	binding_bubble = NULL;
	transition_countdown = 50;
	//Players
	Reset_Position();
	player_third_person.Update(EULER_ROTATION);
	player_first_person.Update(EULER_ROTATION);
	//Bounding Box
	boundary_box = Boundary_Box(-50, 50, -50, 50, -50, 50);
	boundary_box.max_speed = 0.5f;
	boundary_box.bubble_radius = 5.0f;
	boundary_box.Random_Generate_Bubbles(50);
	//Set Gears
	move_speed_gear = Gears(8, 4, new float[8]{ 0.05f, 0.1f, 0.25f, 0.5f, 1.0f, 2.0f, 5.0f, 10.0f }, &move_speed);
	rotate_speed_gear = Gears(8, 4, new float[8]{ 0.1f, 0.25f, 0.5f, 0.75f, 1.0f, 1.5f, 3.0f, 5.0f }, &rotate_speed);
	bubble_global_speed_gear = Gears(8, 4, new float[8]{ 0.05f, 0.1f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f, 8.0f }, &boundary_box.simulate_speed);
	bubble_rotate_speed_gear = Gears(8, 4, new float[8]{ 0.1f, 0.25f, 0.5f, 0.75f, 1.0f, 1.5f, 3.0f, 5.0f }, &bubble_rotate_speed);
	//Set Light Sources
	Set_LightSource();
}

//Functions
void SceneManager::Keyboard_Detect(const unsigned char& key, const bool& s) {
	key_dict[key] = s;
}

void SceneManager::Keyboard_Detect_Special(const unsigned char& key, const bool& s) {
	special_key_dict[key] = s;
}

void SceneManager::Reset_Binding() {
	if (binding_bubble == NULL) {
		return;
	}
	binding_bubble = NULL;
}

void SceneManager::Reset_Position() {
	if (isFreezed) {
		return;
	}
	Reset_Binding();
	player_third_person = start_third_position;
	player_first_person = start_first_position;
	current_player = &player_third_person;
	transition_state = THIRD_PERSON;
}

void SceneManager::Change_Mode(CameraMode mode) {
	if (isFreezed) {
		return;
	}
	camera_mode = mode;
}

void SceneManager::Toggle_Pause() {
	if (isFreezed) {
		return;
	}
	isPaused ^= 1;
}

void SceneManager::Window_Resize(const int& w, const int& h) {
	GLfloat nRange = 100.0f;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, GLfloat(w) / h, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	global_window_width = w, global_window_height = h;
	glGetFloatv(GL_PROJECTION_MATRIX, Projection_Matrix);
}

void SceneManager::Window_Close() {
	if (!glutGetWindow()) {
		return;
	}
	exit(0);
}

void SceneManager::Update_Timer() {
	transition_timer++;
	if (transition_timer >= transition_countdown) {
		transition_timer = 0;
		transition_state = goal_transition_state;
	}
}

void SceneManager::Update_State() {
	//If the number of bubbles is 1 or less, exit program
	if (boundary_box.num_bubbles <= 1) {
		Window_Close();
		return;
	}
	//Update States
	if (!isFreezed && isPaused == 0) {
		boundary_box.Simulate_Steps();
		boundary_box.Simulate_Absorb_Bubbles(binding_bubble);
		boundary_box.Simulate_Collision_Boundaries();
		boundary_box.Simulate_Collision_Bubbles();
	}
	//Execute Keyboard Events
	Keyboard_Events_Hold();
	//Bind the bubble
	player_first_person.Bind_Bubble(binding_bubble);
	//Update Cameras
	if (transition_state == TRANSITION) {
		isFreezed = 1;
		View_Matrix = camera_A.Slerp(camera_B, Util::Ratio(transition_timer, transition_countdown));
		Update_Timer();
	}
	else {
		isFreezed = 0;
		View_Matrix = current_player->IView_MG;
	}
}

//Key Functions
void SceneManager::Keyboard_Events_Hold() {
	//Player Control
	if (key_dict['s']) {
		Move_z(1);
	}
	if (key_dict['w']) {
		Move_z(-1);
	}
	if (key_dict['d']) {
		Move_x(1);
	}
	if (key_dict['a']) {
		Move_x(-1);
	}
	if (key_dict['e']) {
		Move_y(1);
	}
	if (key_dict['q']) {
		Move_y(-1);
	}
	//Camera Control
	if (key_dict['j']) {
		Rotate_h(1);
	}
	if (key_dict['l']) {
		Rotate_h(-1);
	}
	if (key_dict['i']) {
		Rotate_p(1);
	}
	if (key_dict['k']) {
		Rotate_p(-1);
	}
	if (key_dict['o']) {
		Rotate_b(1);
	}
	if (key_dict['u']) {
		Rotate_b(-1);
	}
	//Special Key Functions
	if (special_key_dict[GLUT_KEY_UP]) {
		Rotate_Bubble_y(1);
	}
	if (special_key_dict[GLUT_KEY_DOWN]) {
		Rotate_Bubble_y(-1);
	}
	if (special_key_dict[GLUT_KEY_LEFT]) {
		Rotate_Bubble_x(1);
	}
	if (special_key_dict[GLUT_KEY_RIGHT]) {
		Rotate_Bubble_x(-1);
	}
}

void SceneManager::Keyboard_Events_Down(const unsigned char& key) {
	//Touch Events
	if (key == ESCAPE_KEY) { //Escape Key
		ReturnToThird();
	}
	if (key == 'p') {
		Toggle_Pause();
	}
	if (key == 'r') {
		Reset_Position();
	}
	if (key == '[') {
		Change_MoveSpeed(-1);
	}
	if (key == ']') {
		Change_MoveSpeed(1);
	}
	if (key == '-') {
		Change_RotateSpeed(-1);
	}
	if (key == '=') {
		Change_RotateSpeed(1);
	}
	if (key == ',') {
		Change_BubbleGlobalSpeed(-1);
	}
	if (key == '.') {
		Change_BubbleGlobalSpeed(1);
	}
	if (key == '0') {
		ReturnToFirst();
	}
	if (key == '1') {
		Change_Mode(EULER_ROTATION);
	}
	if (key == '2') {
		Change_Mode(FREE_ROTATION);
	}
}

void SceneManager::Keyboard_Events_Down_Special(const unsigned char& key) {
	if (key == GLUT_KEY_END) {
		Window_Close();
	}
	if (key == GLUT_KEY_PAGE_UP) {
		Change_BubbleRotateSpeed(1);
	}
	if (key == GLUT_KEY_PAGE_DOWN) {
		Change_BubbleRotateSpeed(-1);
	}
}

void SceneManager::ReturnToThird() { //Will not reset states
	if (transition_state != FIRST_PERSON) {
		return;
	}
	camera_A = player_first_person;
	camera_B = player_third_person;
	current_player = &player_third_person;
	transition_state = TRANSITION;
	goal_transition_state = THIRD_PERSON;
}

void SceneManager::ReturnToFirst() { //Will not reset states
	if (transition_state != THIRD_PERSON || binding_bubble == NULL) {
		return;
	}
	camera_A = player_third_person;
	camera_B = player_first_person;
	current_player = &player_first_person;
	transition_state = TRANSITION;
	goal_transition_state = FIRST_PERSON;
}

void SceneManager::CameraTransition(Bubble* b) { //Will also reset states
	if (b == NULL) {
		return;
	}
	Reset_Binding();
	binding_bubble = b;
	binding_bubble->Set_Init();
	camera_A = *current_player;
	player_first_person = start_first_position;
	player_first_person.Bind_Bubble(binding_bubble);
	camera_B = player_first_person;
	current_player = &player_first_person;
	transition_state = TRANSITION;
	goal_transition_state = FIRST_PERSON;
}

CRay767 SceneManager::Mouse_Raycast(const int& width, const int& height, const int& mouse_x, const int& mouse_y) {
	float x = (2.0f * mouse_x) / width - 1.0f, y = 1.0f - (2.0f * mouse_y) / height;
	//4d Homogeneous Clip Coordinates
	CVector767_ext ray_clip = CVector767_ext(x, y, -1.0, 1.0);
	//4d Eye Coordinates
	CVector767_ext ray_eye = Projection_Matrix.GetInverse() * ray_clip;
	ray_eye.z = -1.0f, ray_eye.w = 0.0f;
	//4d World Coordinates
	CVector767 ray_dir = (current_player->View_MG * ray_eye).To3DVector();
	//Set the position vector
	CVector767 ray_pos = current_player->View_M0.posMul(current_player->pos);
	return CRay767(ray_pos, ray_dir);
}

Bubble* SceneManager::Detect_Bubble(CRay767& ray, const float& max_dist) {
	Bubble* Chosen_Bubble = NULL;
	float min_dist = max_dist;
	for (Bubble* b : boundary_box.bubble_array) {
		if (transition_state == FIRST_PERSON && b == binding_bubble) {
			continue; //Avoid Duplication
		}
		float d = ray.Collision_Sphere(*b);
		if (d > 0 && d < min_dist) {
			min_dist = d;
			Chosen_Bubble = b;
		}
	}
	return Chosen_Bubble;
}

void SceneManager::Mouse_Clicking_Events(const int& mouse_x, const int& mouse_y) {
	if (isFreezed) {
		return;
	}
	CRay767 ray = Mouse_Raycast(global_window_width, global_window_height, mouse_x, mouse_y);
	Bubble* chosen_bubble = Detect_Bubble(ray, raycast_maxdist);
	CameraTransition(chosen_bubble);
}

//Control Functions
void SceneManager::Move_x(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Move_x(t * move_speed, camera_mode);
}

void SceneManager::Move_y(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Move_y(t * move_speed, camera_mode);
}

void SceneManager::Move_z(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Move_z(t * move_speed, camera_mode);
}

void SceneManager::Rotate_h(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Rotate_h(t * rotate_speed, camera_mode);
}

void SceneManager::Rotate_p(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Rotate_p(t * rotate_speed, camera_mode);
}

void SceneManager::Rotate_b(const float& t) {
	if (isFreezed) {
		return;
	}
	current_player->Rotate_b(t * rotate_speed, camera_mode);
}

void SceneManager::Change_MoveSpeed(const int& t) {
	if (isFreezed) {
		return;
	}
	move_speed_gear.Change_Gear(t);
}

void SceneManager::Change_RotateSpeed(const int& t) {
	if (isFreezed) {
		return;
	}
	rotate_speed_gear.Change_Gear(t);
}

void SceneManager::Change_BubbleGlobalSpeed(const int& t) {
	if (isFreezed) {
		return;
	}
	bubble_global_speed_gear.Change_Gear(t);
}

void SceneManager::Change_BubbleRotateSpeed(const int& t) {
	if (isFreezed) {
		return;
	}
	bubble_rotate_speed_gear.Change_Gear(t);
}

void SceneManager::Rotate_Bubble_x(const float& t) {
	if (isFreezed || binding_bubble == NULL) {
		return;
	}
	//Reset the player to starting first position
	player_first_person = start_first_position;
	binding_bubble->Rotate_x(t * bubble_rotate_speed);
}

void SceneManager::Rotate_Bubble_y(const float& t) {
	if (isFreezed || binding_bubble == NULL) {
		return;
	}
	//Reset the player to starting first position
	player_first_person = start_first_position;
	binding_bubble->Rotate_y(t * bubble_rotate_speed);
}

//Render Functions
void SceneManager::Draw_Axis() {
	//Set Line Width
	glLineWidth(0);
	glBegin(GL_LINES);
	//Draw x-axis
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(200, 0, 0);
	//Draw y-axis
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 200, 0);
	//Draw z-axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 200);
	glEnd();
}

void SceneManager::Draw_Ground() {
	GLfloat X_min = -1e5, X_max = 1e5;
	GLfloat Z_min = -1e5, Z_max = 1e5;
	GLfloat Y = -50.5;
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(X_min, Y, Z_min);
	glVertex3f(X_min, Y, Z_max);
	glVertex3f(X_max, Y, Z_max);
	glVertex3f(X_max, Y, Z_min);
	glEnd();
}

void SceneManager::Draw_HUD() {
	string HUD = Util::format("Number of Bubbles: %d", boundary_box.num_bubbles);
	Shader::Font2D(HUD, CVector767(1, 1, 1), -0.95, 0.85, 4);
	if (binding_bubble == NULL) {
		HUD = "Bubble Volume: NA";
	}
	else {
		HUD = Util::format("Bubble Volume: %.2f", binding_bubble->volume);
	}
	Shader::Font2D(HUD, CVector767(1, 1, 1), -0.95, 0.75, 4);
}

void SceneManager::Set_LightSource() {
	light0_pos = CVector767(boundary_box.X_max, boundary_box.Y_max, boundary_box.Z_max);
	light1_pos = CVector767(boundary_box.X_min, boundary_box.Y_min, boundary_box.Z_min);
}

void SceneManager::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Set View Matrix
	glPushMatrix();
	glMultMatrixf(View_Matrix);

	Draw_Axis();
	Shader::Draw_Box(boundary_box);
	Shader::Set_Light(light0_pos, light1_pos);
	boundary_box.Sort_By_Distance(current_player->pos);
	glDepthMask(GL_FALSE);
	for (Bubble* b : boundary_box.bubble_array) {
		if (b == binding_bubble) {
			continue;
		}
		Shader::Draw_Bubble(*b, 1);
	}
	if (binding_bubble != NULL) {
		if (transition_state == FIRST_PERSON) {
			Shader::Draw_Bubble(*binding_bubble, 0);
		}
		else {
			Shader::Draw_Bubble(*binding_bubble, 1);
		}
	}
	glDepthMask(GL_TRUE);
	Shader::Disable_Light();
	Draw_HUD();

	glPopMatrix();
	glutSwapBuffers();
}