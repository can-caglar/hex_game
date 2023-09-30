#include <iostream>
#include <memory>
#include "Game.h"
#include "QuestionGenerator.h"
#include "GameWithTime.h"
#include "common.h"
#include <random>

class MyRNG : public IRNG
{
public:
	int getRandomNum() override
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> dist(1, 100);
		int random_num = dist(rng);
		return random_num;
	}
};

#ifdef RUN_MY_MAIN
int main()
{
	// Build
	QuestionGenerator questionGenerator(std::make_shared<MyRNG>());
	std::shared_ptr<IGame> game = std::make_shared<Game>(&std::cin, &std::cout, &questionGenerator);
	std::shared_ptr<IGameClock> gclock = std::make_shared<GameClock>();
	
	GameWithTime gt(game, gclock, 20);
	// Run
	gt.play();
}
#endif