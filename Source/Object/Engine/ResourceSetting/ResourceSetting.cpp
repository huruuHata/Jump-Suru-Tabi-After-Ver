
#define _USING_V110_SDK71_ 1

#include "ResourceSetting.h"

using namespace KeyString;
using namespace Common;

void ResourceSetting::SceneResourceSetting(Engine* pEngine, const int scene_num, const bool bBlack_mode, const bool bBuild_mode)
{
	m_textures.clear();
	m_ses.clear();
	m_bgm.clear();

	switch (scene_num)
	{
	case SCENE_TITLE:

		TitleSetting();

		break;

	case SCENE_GAME:

		GameSetting(bBlack_mode, bBuild_mode);

		break;

	case SCENE_CLEAR:

		ClearSetting();

		break;

	case SCENE_GAMEOVER:

		GameoverSetting();

		break;

	default:

		break;
	}

	AddTextures(pEngine);
	AddSE(pEngine);
	AddBGM(pEngine);
}

void ResourceSetting::SceneResourceRelease(Engine* pEngine)
{
	ReleaseTextures(pEngine);
	ReleaseSE(pEngine);
	ReleaseBGM(pEngine);
}

void ResourceSetting::AddTextures(Engine* pEngine)
{
	for (const std::string& texture : m_textures)
	{
		pEngine->AddTexture(texture);
	}
}

void ResourceSetting::AddSE(Engine * pEngine)
{
	for (const std::string& se : m_ses)
	{
		pEngine->AddSE(se);
	}
}

void ResourceSetting::AddBGM(Engine * pEngine)
{
	if (!m_bgm.empty()) pEngine->LoadBGM(m_bgm);
}

void ResourceSetting::ReleaseTextures(Engine * pEngine)
{
	for (const std::string& texture : m_textures)
	{
		pEngine->ReleaseTexture(texture);
	}
}

void ResourceSetting::ReleaseSE(Engine * pEngine)
{
	for (const std::string& se : m_ses)
	{
		pEngine->ReleaseSE(se);
	}
}

void ResourceSetting::ReleaseBGM(Engine * pEngine)
{
	if (!m_bgm.empty()) pEngine->ReleaseBGM();
}

void ResourceSetting::TitleSetting()
{
	m_textures =
	{
		TEXTURE_TITLE,
		TEXTURE_TITLE_START,
		TEXTURE_TITLE_WHITE,
		TEXTURE_TITLE_BLACK,
		TEXTURE_BACK,
		TEXTURE_CONGRATULATION_TITLE,
	};

	m_bgm = BGM_TITLE;

	m_ses =
	{
		SE_DECIDE,
	};
}

void ResourceSetting::GameSetting(const bool is_black_mode, const bool is_build_mode)
{
	if (is_black_mode)
	{
		m_textures =
		{
			TEXTURE_CHIP_BLACK,
			TEXTURE_BLACK_CHARA,
			TEXTURE_CONGRATULATION_GAME,
		};
	}
	else
	{
		if (is_build_mode)
		{
			m_textures =
			{
				TEXTURE_CHIP_WHITE,
				TEXTURE_WHITE_CHARA,
				TEXTURE_BUILD_KEY_EXPLAIN,
				TEXTURE_BUILD_EXPLAIN,
				TEXTURE_BACK_GAME,
			};
		}
		else
		{
			m_textures =
			{
				TEXTURE_CHIP_WHITE,
				TEXTURE_WHITE_CHARA,
				TEXTURE_EXPLAIN_GOAL,
				TEXTURE_EXPLAIN_FALL,
				TEXTURE_EXPLAIN_KEY,
				TEXTURE_EXPLAIN_JUMP,
				TEXTURE_EXPLAIN_HIT,
				TEXTURE_BACK_GAME,
			};
		}
	}

	m_bgm = is_black_mode ? BGM_BLACK : BGM_WHITE;

	m_ses =
	{
		SE_JUMP,
	};
}

void ResourceSetting::ClearSetting()
{
	m_textures =
	{
		TEXTURE_NEXT,
		TEXTURE_CLEAR_BACK,
		TEXTURE_CLEAR_TELOP,
		TEXTURE_GAMECLEAR_BACK,
		TEXTURE_GAMECLEAR,
		TEXTURE_NEWMODE,
	};

	m_ses =
	{
		SE_STAGECLEAR,
		SE_GAMECLEAR,
	};
}

void ResourceSetting::GameoverSetting()
{
	m_textures =
	{
		TEXTURE_GAMEOVER,
		TEXTURE_GAMEOVER_BACK,
	};

	m_ses =
	{
		SE_GAMEOVER,
	};
}
