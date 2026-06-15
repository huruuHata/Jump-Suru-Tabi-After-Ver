#pragma once

#include "..\\..\\Player\\Player.h"

class Collide
{
public:
	
	static Collide& getInstance()
	{
		static Collide instance;
		return instance;
	}

	Collide(const Collide&) = delete;
	Collide& operator=(const Collide&) = delete;

private:

	Collide() {}

	~Collide() = default;
};