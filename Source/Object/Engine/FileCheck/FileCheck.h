
//JSONファイルが開けるか確認を行う

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
	
private:


	FileCheck() {}

	~FileCheck() = default;
};