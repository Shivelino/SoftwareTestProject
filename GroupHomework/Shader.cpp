#include "stdafx.h"
#include "Scene.h"

const float Shader::ray_max_render_dist = 1e3;
const int Shader::ball_lon = 32;
const int Shader::ball_lat = 32;
const int Shader::array_siz = Shader::ball_lon * (Shader::ball_lat + 1);
GLuint* Shader::texture = new GLuint[3]();
CVector767* Shader::ball_vert = new CVector767[Shader::array_siz];
CVector767* Shader::ball_norm = new CVector767[Shader::array_siz];
float** Shader::ball_texture_coordinate = new float*[Shader::array_siz];

//Lights and Materials
GLfloat* Shader::light_amb = new GLfloat[4]{ 0.4f, 0.4f, 0.4f, 1 };
GLfloat* Shader::light_dif = new GLfloat[4]{ 1, 1, 1, 1 };
GLfloat* Shader::light_spe = new GLfloat[4]{ 1, 1, 1, 1 };
GLfloat* Shader::mat_amb = new GLfloat[4]{ 0.3f, 0.3f, 0.3f, 1 };
GLfloat* Shader::mat_dif = new GLfloat[4]{ 1, 1, 1, 1 };
GLfloat* Shader::mat_spe = new GLfloat[4]{ 0.1f, 0.1f, 0.1f, 1 };

//Show Texts
void Shader::Font2D(string& s, CVector767& col, const double& x, const double& y, const int& size) {
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
	glColor3f(col.x, col.y, col.z);
	//Change Matrix Mode
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//Output strings
	int len = s.length();
	glRasterPos2f(x, y);
	for (int i = 0; i < len; ++i)
	{
		switch (size) {
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
			break;
		case 2:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			break;
		case 3:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[i]);
			break;
		case 4:
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
			break;
		case 5:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
			break;
		case 6:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
			break;
		case 7:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
			break;
		}
	}
	//Reset projections mode
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Shader::Initialize() {
	glGenTextures(3, Shader::texture);
	LoadGLTextures(0, "9.png");
	LoadGLTextures(1, "6.png");
	LoadGLTextures(2, "sky.png");
	//Set glut properties
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Shader::initBall() {
	for (int i = 0; i < array_siz; i++) {
		ball_texture_coordinate[i] = new float[2]();
	}
	GLfloat lonCur, latCur, lonStep = 2 * Util::Pi / ball_lon, latStep = Util::Pi / ball_lat;
	CVector767 normal;
	int index[4], nVert = 0;
	for (int i = 0; i < ball_lon; i++)
	{
		lonCur = i * lonStep;
		for (int j = 0; j <= ball_lat; j++)
		{
			latCur = -Util::Pi / 2 + j * latStep;
			ball_vert[nVert][2] = cos(latCur) * sin(lonCur);
			ball_vert[nVert][0] = cos(latCur) * cos(lonCur);
			ball_vert[nVert][1] = sin(latCur);
			ball_norm[nVert].Set(0, 0, 0);
			ball_texture_coordinate[nVert][0] = float(i) / float(ball_lon);
			ball_texture_coordinate[nVert][1] = float(j) / float(ball_lat);
			nVert++;
		}
	}
	for (int i = 0; i < ball_lon; i++)
	{
		for (int j = 0; j < ball_lat; j++)
		{
			index[0] = i * (ball_lat + 1) + j;
			if (i == ball_lon - 1) {
				index[1] = j;
			}
			else {
				index[1] = index[0] + ball_lat + 1;
			}
			index[2] = index[1] + 1;
			index[3] = index[0] + 1;
			normal = CalculateNormal(ball_vert[index[0]], ball_vert[index[1]], ball_vert[index[2]]);
			for (int k = 0; k < 3; k++)
			{
				ball_norm[index[k]] = ball_norm[index[k]] + normal;
			}
			normal = CalculateNormal(ball_vert[index[2]], ball_vert[index[3]], ball_vert[index[0]]);
			for (int k = 0; k < 4; k++)
			{
				if (k == 1) continue;
				ball_norm[index[k]] = ball_norm[index[k]] + normal;
			}
		}
	}
	while (nVert > 0)
	{
		ball_norm[--nVert].Normalize();
	}
}

CVector767 Shader::CalculateNormal(CVector767& v1, CVector767& v2, CVector767& v3)
{
	CVector767 normal, dirv2_v1, dirv2_v3;
	dirv2_v1 = v1 - v2;
	dirv2_v3 = v3 - v2;
	normal = dirv2_v1.crossMul(dirv2_v3);
	return normal;
}

//Load Texture Data
int Shader::LoadGLTextures(const int& id, const char* name)
{
	//Load Image
	CImage img;
	HRESULT hResult = img.Load(name);
	if (FAILED(hResult)) {
		return 0;
	}
	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture[id]);
	//Mipmaps
	int pitch = img.GetPitch();
	if (pitch < 0) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(),
			img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetPixelAddress(0, img.GetHeight() - 1));
	}
	else {
		gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(),
			img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetBits());
	}
	//Linear Mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//Repeat Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	return 1;
}

void Shader::Set_Light(CVector767& light0_pos, CVector767& light1_pos) {
	//Set Light Properties and Positions
	GLfloat pos[4] = { light0_pos.x, light0_pos.y, light0_pos.z, 1 };
	GLfloat pos1[4] = { light1_pos.x, light1_pos.y, light1_pos.z, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_spe);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	//Smooth Lighting
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//Set the Environments
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Set the materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spe);
}

void Shader::Disable_Light() {
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
}

void Shader::Draw_Ray(CRay767& ray) {
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	float l1 = 10, l2 = ray_max_render_dist;
	CVector767 p1 = ray.pos + l1 * ray.dir;
	CVector767 p2 = ray.pos + l2 * ray.dir;
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}

void Shader::Draw_Box(Boundary_Box& box) {
	GLfloat X_min = box.X_min, X_max = box.X_max;
	GLfloat Y_min = box.Y_min, Y_max = box.Y_max;
	GLfloat Z_min = box.Z_min, Z_max = box.Z_max;
	glLineWidth(0);
	glColor4f(1, 1, 1, 1);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.333);
	glVertex3f(X_min, Y_min, Z_min);
	glTexCoord2f(0.5, 0.333);
	glVertex3f(X_max, Y_min, Z_min);
	glTexCoord2f(0.5, 0.666);
	glVertex3f(X_max, Y_max, Z_min);
	glTexCoord2f(0.25, 0.666);
	glVertex3f(X_min, Y_max, Z_min);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.333);
	glVertex3f(X_min, Y_min, Z_min);
	glTexCoord2f(0.25, 0.001);
	glVertex3f(X_min, Y_min, Z_max);
	glTexCoord2f(0.5, 0.001);
	glVertex3f(X_max, Y_min, Z_max);
	glTexCoord2f(0.5, 0.333);
	glVertex3f(X_max, Y_min, Z_min);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.333);
	glVertex3f(X_min, Y_min, Z_min);
	glTexCoord2f(0.25, 0.666);
	glVertex3f(X_min, Y_max, Z_min);
	glTexCoord2f(0.001, 0.666);
	glVertex3f(X_min, Y_max, Z_max);
	glTexCoord2f(0.001, 0.333);
	glVertex3f(X_min, Y_min, Z_max);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.999, 0.666);
	glVertex3f(X_min, Y_min, Z_max);
	glTexCoord2f(0.999, 0.333);
	glVertex3f(X_min, Y_max, Z_max);
	glTexCoord2f(0.75, 0.334);
	glVertex3f(X_max, Y_max, Z_max);
	glTexCoord2f(0.75, 0.666);
	glVertex3f(X_max, Y_min, Z_max);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.666);
	glVertex3f(X_min, Y_max, Z_min);
	glTexCoord2f(0.5, 0.666);
	glVertex3f(X_max, Y_max, Z_min);
	glTexCoord2f(0.5, 0.999);
	glVertex3f(X_max, Y_max, Z_max);
	glTexCoord2f(0.25, 0.999);
	glVertex3f(X_min, Y_max, Z_max);
	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5, 0.666);
	glVertex3f(X_max, Y_min, Z_min);
	glTexCoord2f(0.75, 0.666);
	glVertex3f(X_max, Y_min, Z_max);
	glTexCoord2f(0.75, 0.334);
	glVertex3f(X_max, Y_max, Z_max);
	glTexCoord2f(0.5, 0.334);
	glVertex3f(X_max, Y_max, Z_min);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Shader::Draw_Bubble(Bubble& b, const bool& isFront) {
	//Set Color and Texture
	CVector767 col = b.col;
	if (isFront) {
		glColor4f(col.x, col.y, col.z, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glFrontFace(GL_CCW);
	}
	else {
		glColor4f(col.x, col.y, col.z, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glFrontFace(GL_CW);
	}
	glPolygonMode(GL_BACK, GL_FILL);
	glEnable(GL_TEXTURE_2D);
	//Set Light and Draw Sphere
	Draw_Sphere(b);
	//Reset States
	glDisable(GL_TEXTURE_2D);
}

void Shader::Draw_Sphere(CSphere767& s) {
	CMatrix767 M;
	M.SetTrans(s.pos);
	float radius = s.radius;
	glPushMatrix();
	glMultMatrixf(M);
	glRotatef(s.pos[0], s.pos[1], s.pos[2], s.pos[0]);
	glRotatef(s.pos[3], s.pos[1], s.pos[2], s.pos[2]);
	glBegin(GL_TRIANGLES);
	//Draw Sphere
	int index[4], ord[] = { 0, 1, 2, 2, 3, 0 };
	for (int i = 0; i < ball_lon; i++)	//Longitude
	{
		for (int j = 0; j < ball_lat; j++)	//Latitude
		{
			index[0] = i * (ball_lat + 1) + j;
			if (i == ball_lon - 1) {
				index[1] = j;
			}
			else {
				index[1] = index[0] + ball_lat + 1;
			}
			index[2] = index[1] + 1;
			index[3] = index[0] + 1;
			for (int k = 0; k < 6; k++)
			{
				glTexCoord2f(ball_texture_coordinate[index[ord[k]]][0], ball_texture_coordinate[index[ord[k]]][1]);
				glNormal3fv(ball_norm[index[ord[k]]]);
				glVertex3fv(radius * ball_vert[index[ord[k]]]);
			}
		}
	}
	//Reset States
	glEnd();
	glPopMatrix();
}