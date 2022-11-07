#include "stdafx.h"
#include "Pch.h"

const int Util::sizeOfBuffer = 256;
char* Util::format_char = new char[Util::sizeOfBuffer];

const float Util::eps = 1e-6;
const double Util::Pi = acos(-1);

default_random_engine Util::Random;

string Util::format(const char* format, ...) {
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsnprintf(Util::format_char, Util::sizeOfBuffer, format, arg_ptr);
	return string(Util::format_char);
}

float Util::DegToRad(const float& deg) {
	return deg * Pi / 180;
}

float Util::RadToDeg(const float& rad) {
	return rad * 180 / Pi;
}

float Util::WrapAngle(const float& x) {
	float ax = 0.0f;
	int sgn = 0;
	if (x >= 0.0f) {
		ax = x;
		sgn = 1;
	}
	else {
		ax = -x;
		sgn = -1;
	}
	return x - (int)(ax + 180.0f) / 360 * 360 * sgn;
}

float Util::Ratio(const int& x, const int& y) {
	return (float)x / y;
}

bool Util::RoughEqual(const float& a, const float& b) {
	return abs(a-b) < eps;
}

//Random Functions
void Util::Set_Random_Seed() {
	Random.seed(time(0));
}

float Util::Get_Random_Float(const float& l, const float& r) {
	uniform_real_distribution<float> Random_float(l, r);
	return Random_float(Random);
}

CVector767 Util::Get_Random_Position(const float& X_min, const float& X_max, const float& Y_min, const float& Y_max, const float& Z_min, const float& Z_max) {
	return CVector767(Get_Random_Float(X_min, X_max), Get_Random_Float(Y_min, Y_max), Get_Random_Float(Z_min, Z_max));
}

CVector767 Util::Get_Random_Color() {
	return CVector767(Get_Random_Float(0.4, 0.6), Get_Random_Float(0.4, 0.6), Get_Random_Float(0.4, 0.6));
}

CVector767 Util::Get_Random_Direction() {
	float s = Get_Random_Float(0, 2 * Pi), v = Get_Random_Float(-1, 1);
	float phi = acos(v) - Pi / 2; //theta = s
	return CVector767(cos(phi)*cos(s), sin(phi), cos(phi)*sin(s));
}