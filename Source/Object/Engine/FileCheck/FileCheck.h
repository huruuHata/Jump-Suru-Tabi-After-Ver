#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\nlohmann\json.hpp"

#include <fstream>

using json = nlohmann::json;

class FileCheck
{
public:
	
	static FileCheck& getInstance()
	{
		static FileCheck instance;
		return instance;
	}

	static const json FileOpenCheck(std::string json_file_name);
	static const void FileCheck::TextFileOpenCheck(std::string text_file_name, std::vector<std::string>& out_texts);
	
private:


	FileCheck() {}

	~FileCheck() = default;
};