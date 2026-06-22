#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\Engine\\FileCheck\\FileCheck.h"

#include<iostream>

using json = nlohmann::json;

class SaveGame
{
public:
	
	static SaveGame& getInstance()
	{
		static SaveGame instance;
		return instance;
	}

	struct SaveData
	{
		bool is_game_clear;
		bool is_all_game_clear;
	};
 
	static void SaveFile(const SaveData& data);
	static SaveData LoadFile();

private:


	SaveGame() {}

	~SaveGame() = default;
};