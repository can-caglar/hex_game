#include <iostream>
#include <memory>
#include "Game.h"
#include "QuestionGenerator.h"

class MyRNG : public IRNG
{
public:
	int getRandomNum() override
	{
		return 5;
	}
};

#if 0
int main()
{
	QuestionGenerator questionGenerator(std::make_shared<IRNG>());
	Game game(&std::cin, &std::cout, questionGenerator);
	while (1)
	{
		game.tick();
	}
}
#endif