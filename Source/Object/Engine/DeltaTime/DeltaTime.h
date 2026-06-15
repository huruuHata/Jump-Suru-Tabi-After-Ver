
//前フレームからの経過時間を計測する

#pragma once

#include "..\\..\\..\\GameBase.h"

class DeltaTime
{
public:
	
	static DeltaTime& getInstance()
	{
		static DeltaTime instance;
		return instance;
	}

	DeltaTime(const DeltaTime&) = delete;
	DeltaTime& operator=(const DeltaTime&) = delete;

	void DeltaTimeCount();

	float GetDeltaTime();

private:

	float m_delta_time;
	DWORD m_prev_time;

	DeltaTime() {}

	~DeltaTime() = default;
};