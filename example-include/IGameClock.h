#pragma once
#include <ctime>

class IGameClock
{
public:
	virtual time_t getTime() = 0;
};

class GameClock : public IGameClock
{
public:
	time_t getTime()
	{
		return time(nullptr);
	}
};