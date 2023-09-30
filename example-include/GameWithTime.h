#pragma once

#include <memory>
#include "IGameClock.h"
#include "Game.h"

class GameWithTime
{
public:
	GameWithTime(std::shared_ptr<IGame> game,
				std::shared_ptr<IGameClock> myClock,
				time_t timeToRun) : m_game{ game },
		m_clock { myClock },
		m_timeToRunGame { timeToRun }
	{};
	void play()
	{
		time_t timeAtStart = m_clock->getTime();
		time_t elapsed = 0;
		while (elapsed < m_timeToRunGame)
		{
			m_game->tick();
		 	elapsed = m_clock->getTime() - timeAtStart;
		}
	}
private:
	std::shared_ptr<IGame> m_game;
	std::shared_ptr<IGameClock> m_clock;
	time_t m_timeToRunGame;
};