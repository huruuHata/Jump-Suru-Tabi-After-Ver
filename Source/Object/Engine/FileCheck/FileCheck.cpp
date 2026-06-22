
#define _USING_V110_SDK71_ 1

#include "FileCheck.h"

using namespace std;

const json FileCheck::FileOpenCheck(string json_file_name)
{
	std::ifstream ifs(json_file_name);

	if (!ifs.is_open()) throw exception("Jsonファイルが開けません");

	ifs.seekg(0, ios::beg);

	json data = json::array();

	ifs >> data;

	return data;
}


