#include "stdafx.h"
#include "Pch.h"

int main(int argc, char *argv[])
{
	Err_Code err_code = Task1_main(argc, argv);
	if (err_code != NO_ERR) {
		return err_code;
	}
	err_code = Task2_main(argc, argv);
	if (err_code != NO_ERR) {
		return err_code;
	}
	return 0;
}