#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdarg.h>
#include <random>
#include <time.h>
#include <vector>
#include <set>
#include <map>
using namespace std;

class CEuler767;
class CVector767;
class CMatrix767;
class CQuaternion767;
class CRay767;
class CSphere767;
class Bubble;

#include "CEuler767.h"
#include "CVector767.h"
#include "CMatrix767.h"
#include "CQuaternion767.h"
#include "Geometry.h"
#include "FileIO.h"
#include "Util.h"

Err_Code Task1_main(int argc, char *argv[]);
Err_Code Task2_main(int argc, char *argv[]);