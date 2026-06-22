
//シーンごとにTexture,SE,BGMのセットを行い、Add,Releaseを行う

#pragma once

#include "..\\..\\..\\GameData.h"

class ResourceSetting
{
public:

	static ResourceSetting& getInstance()
	{
		static ResourceSetting instance;
		return instance;
	}

	ResourceSetting(const ResourceSetting&) = delete;
	ResourceSetting& operator=(const ResourceSetting&) = delete;

	void SceneResourceSetting(Engine* pEngine, const int scene_num, const bool bBlack_mode = false, const bool bBuild_mode = false);
	void SceneResourceRelease(Engine* pEngine);

private:

	void AddTextures(Engine* pEngine);
	void AddSE(Engine* pEngine);
	void AddBGM(Engine* pEngine);

	void ReleaseTextures(Engine* pEngine);
	void ReleaseSE(Engine* pEngine);
	void ReleaseBGM(Engine* pEngine);

	void TitleSetting();
	void GameSetting(const bool bBlack_mode, const bool bBuild_mode);
	void ClearSetting();
	void GameoverSetting();
	void EndrollSetting();

	int m_now_scene_num;

	std::vector<std::string> m_textures;
	std::vector<std::string> m_ses;

	std::string m_font;
	std::string m_bgm;

	ResourceSetting() {}

	~ResourceSetting() = default;
};