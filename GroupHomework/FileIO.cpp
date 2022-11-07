#include "stdafx.h"
#include "Pch.h"
#include "Operations.h"

map<string, string(*)(ifstream&)> FileIO::Operations = {
	{ "向量相加", Operation_Vector_Add },
	{ "向量点乘", Operation_Vector_Dot },
	{ "向量叉乘", Operation_Vector_Cross },
	{ "向量标准化", Operation_Vector_Normalize },
	{ "向量求模", Operation_Vector_Norm },
	{ "向量投影", Operation_Vector_Project },
	//homework_2
	{ "矩阵相乘", Operation_Matrix_Multiplication },
	{ "矩阵乘向量", Operation_Matrix_vecMul },
	{ "矩阵乘位置", Operation_Matrix_posMul },
	{ "矩阵设置旋转", Operation_Matrix_Rotate },
	{ "矩阵设置平移", Operation_Matrix_Translate },
	{ "矩阵设置缩放", Operation_Matrix_Scale },
	{ "矩阵求逆", Operation_Matrix_Inverse },
	//homework_3
	{ "欧拉角转换向量", Operation_Euler_toVector },
	{ "向量转换欧拉角", Operation_Vector_toEuler },
	{ "欧拉角转换四元数", Operation_Euler_toQuaternion },
	{ "四元数转换欧拉角", Operation_Quaternion_toEuler },
	{ "欧拉角转换矩阵", Operation_Euler_toMatrix },
	{ "矩阵转换欧拉角", Operation_Matrix_toEuler },
	{ "矩阵转换四元数", Operation_Matrix_toQuaternion },
	{ "四元数转换矩阵", Operation_Quaternion_toMatrix },
	{ "欧拉角标准化", Operation_Euler_Normalize },
	{ "四元数单位化", Operation_Quaternion_Normalize },
	{ "四元数相乘", Operation_Quaternion_Product },
	{ "四元数求差", Operation_Quaternion_Division },
	{ "四元数点乘", Operation_Quaternion_Dot },
	{ "四元数求逆", Operation_Quaternion_Inverse },
	{ "四元数求角度和旋转轴", Operation_Quaternion_GetAngle },
	{ "四元数插值", Operation_Quaternion_Slerp }
};

Err_Code FileIO::Read_File(ifstream& in_stream,ofstream& out_stream) {
	string s;
	in_stream >> s;
#ifdef _DEBUG
	cout << s << endl;
#endif
	if (s == "") {
		return NO_ERR;
	}
	if (Operations.count(s) == 0) {
		return ERR_INVALID;
	}
	string output_str = Operations[s](in_stream);
	out_stream << output_str << endl;
#ifdef _DEBUG
		cout << output_str << endl;
#endif
	return NO_ERR;
}