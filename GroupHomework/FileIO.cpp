#include "stdafx.h"
#include "Pch.h"
#include "Operations.h"

map<string, string(*)(ifstream&)> FileIO::Operations = {
	{ "�������", Operation_Vector_Add },
	{ "�������", Operation_Vector_Dot },
	{ "�������", Operation_Vector_Cross },
	{ "������׼��", Operation_Vector_Normalize },
	{ "������ģ", Operation_Vector_Norm },
	{ "����ͶӰ", Operation_Vector_Project },
	//homework_2
	{ "�������", Operation_Matrix_Multiplication },
	{ "���������", Operation_Matrix_vecMul },
	{ "�����λ��", Operation_Matrix_posMul },
	{ "����������ת", Operation_Matrix_Rotate },
	{ "��������ƽ��", Operation_Matrix_Translate },
	{ "������������", Operation_Matrix_Scale },
	{ "��������", Operation_Matrix_Inverse },
	//homework_3
	{ "ŷ����ת������", Operation_Euler_toVector },
	{ "����ת��ŷ����", Operation_Vector_toEuler },
	{ "ŷ����ת����Ԫ��", Operation_Euler_toQuaternion },
	{ "��Ԫ��ת��ŷ����", Operation_Quaternion_toEuler },
	{ "ŷ����ת������", Operation_Euler_toMatrix },
	{ "����ת��ŷ����", Operation_Matrix_toEuler },
	{ "����ת����Ԫ��", Operation_Matrix_toQuaternion },
	{ "��Ԫ��ת������", Operation_Quaternion_toMatrix },
	{ "ŷ���Ǳ�׼��", Operation_Euler_Normalize },
	{ "��Ԫ����λ��", Operation_Quaternion_Normalize },
	{ "��Ԫ�����", Operation_Quaternion_Product },
	{ "��Ԫ�����", Operation_Quaternion_Division },
	{ "��Ԫ�����", Operation_Quaternion_Dot },
	{ "��Ԫ������", Operation_Quaternion_Inverse },
	{ "��Ԫ����ǶȺ���ת��", Operation_Quaternion_GetAngle },
	{ "��Ԫ����ֵ", Operation_Quaternion_Slerp }
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