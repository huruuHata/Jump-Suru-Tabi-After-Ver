
#define _USING_V110_SDK71_ 1

#include "SaveGame.h"

using namespace KeyString;

void SaveGame::SaveFile(const SaveData& data)
{
	json save = FileCheck::FileOpenCheck(FILE_SAVE); 

	save["IsGameClear"] = data.is_game_clear;
	save["IsAllGameClear"] = data.is_all_game_clear;

	std::ofstream file(FILE_SAVE);

	if (file.is_open()) 
	{
		file << save.dump(4); //４を入れるとファイルの中身が見やすくなるため
	}
}

SaveGame::SaveData SaveGame::LoadFile()
{
	SaveData data;
	data.is_game_clear = false;
	data.is_all_game_clear = false;

	std::ifstream file(FILE_SAVE);

	if (file.is_open()) 
	{
		try 
		{
			json save;
			file >> save;

			if (save.contains("IsGameClear")) 
			{
				data.is_game_clear = save["IsGameClear"].get<bool>();
			}
			if (save.contains("IsAllGameClear"))
			{
				data.is_all_game_clear = save["IsAllGameClear"].get<bool>();
			}
		}
		catch (const json::exception& e) 
		{
			std::cerr << "JSONの読み込みに失敗しました: " << e.what() << std::endl;
		}
	}
	else 
	{
		std::cerr << "セーブファイルが開けませんでした" << std::endl;
	}

	return data;

}
