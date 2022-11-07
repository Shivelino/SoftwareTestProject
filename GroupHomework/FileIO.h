#pragma once

#ifndef _TEST_FileIO
#define _TEST_FileIO

enum Err_Code {
	NO_ERR,
	ERR_FILEIO,
	ERR_INVALID
};

class FileIO {
public:
	static map<string, string(*)(ifstream&)> Operations;
	static Err_Code Read_File(ifstream&, ofstream&);
};

#endif