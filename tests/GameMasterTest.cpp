#include "CppUTest/TestHarness.h"
#include "GameWithTime.h"

TEST_GROUP(GameWithTime)
{
	void setup()
	{
	}
	void teardown()
	{
	}
};

class MyGame : public IGame
{
public:
	MyGame(int correctAns, int wrongAns) :
		m_correctAns{ correctAns }, m_wrongAns{ wrongAns }, m_tick{ 0 } {};
	void tick() override
	{
		m_tick++;
	}
	int correctAnswers() override
	{
		return m_correctAns;
	}
	int wrongAnswers() override
	{
		return m_wrongAns;
	}
	int getTicks() { return m_tick; }
private:
	int m_correctAns;
	int m_wrongAns;
	int m_tick;
};

class MyClock : public IGameClock
{
public:
	MyClock(time_t startTime, time_t tick) : m_startTime{ startTime },
		m_tick{ tick } {};
	time_t getTime() override
	{
		time_t currTime = m_startTime;
		m_startTime += m_tick;
		return currTime;
	}
private:
	time_t m_startTime;
	time_t m_tick;
};

TEST(GameWithTime, game_runs_for_the_allocated_time)
{
	// given
	uint32_t corrAns = 10;
	uint32_t wroAns = 10;
	time_t startTime = 3424223;	// arb starting time
	time_t tick = 1;			// 1 second increment
	uint32_t timeToRun = 60;	// the allocated time
	std::shared_ptr<MyGame> myGame = std::make_shared<MyGame>(corrAns, wroAns);
	std::shared_ptr<MyClock> myClock = std::make_shared<MyClock>(startTime, tick);
	// when
	GameWithTime g(myGame, myClock, timeToRun);
	g.play();
	// then
	CHECK_EQUAL(60, myGame->getTicks());
}


/*
// time increments 1s per tick:
	// expect tick called 60 times.
// give a score for the game; (correctAns*2) - (wrongAns*1))
	//	score can't go below 0

// expect message: Starting the game ...
// Time's up! Final score:
// Name for highscores:
// Show highscore
*/