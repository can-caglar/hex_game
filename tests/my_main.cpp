#include <iostream>
#include <memory>
#include "Game.h"
#include "QuestionGenerator.h"
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
	QuestionGenerator questionGenerator(std::make_shared<MyRNG>());
	Game game(&std::cin, &std::cout, &questionGenerator);
	while (1)
	{
		game.tick();
	}
}
#endif