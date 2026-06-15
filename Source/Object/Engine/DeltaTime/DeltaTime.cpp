
#define _USING_V110_SDK71_ 1

#include "DeltaTime.h"

void DeltaTime::DeltaTimeCount()
{
	DWORD now = timeGetTime();

	if (m_prev_time == 0)
	{
		m_prev_time = now;
		m_delta_time = 0.0f;
		return;
	}

	m_delta_time = (now - m_prev_time) / 1000.0f;
	m_prev_time = now;
}

float DeltaTime::GetDeltaTime()
{
	return m_delta_time;
}
