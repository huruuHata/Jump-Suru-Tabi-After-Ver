
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

const void FileCheck::TextFileOpenCheck(string text_file_name, vector<string>& out_texts)
{
	ifstream ifs(text_file_name, ios::in);

	if (!ifs) throw DxSystemException(DxSystemException::OM_FILE_OPEN_ERROR);

	string tmp_str;

	do { getline(ifs, tmp_str); out_texts.push_back(tmp_str); } while (!ifs.eof());

	ifs.close();
}

