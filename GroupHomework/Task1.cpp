#include "stdafx.h"
#include "glut.h"
#include "Pch.h"

Err_Code Task1_main(int argc, char *argv[]) {
	ifstream file_in("test.txt");
	ofstream file_out("out.txt");
	if (!file_in.is_open())
	{
		cout << "错误代码ERR_FILEIO：打开文件异常！" << endl;
		file_in.clear();
		return ERR_FILEIO;
	}
	while (!file_in.eof()) {
		Err_Code err_code = FileIO::Read_File(file_in, file_out);
		if (err_code == ERR_INVALID) {
			cout << "错误代码ERR_INVALID：输入异常！" << endl;
			file_in.clear();
			return err_code;
		}
	}
	file_in.clear();
	return NO_ERR;
}