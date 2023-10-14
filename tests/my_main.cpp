#include <iostream>
#include <memory>
#include "Game.h"
#include "QuestionGenerator.h"
#include "GameWithTime.h"
#include "common.h"
#include <random>
#include "Highscores.h"
#include "MyEncryptor.h"
#include "FileStorage.h"
#include <ctime>
#include <iomanip>

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
	// Warning, messy code below. Got too impatient and wanted it to just work :).
	
	std::cout << "Welcome to the hex maths game!" << std::endl << std::endl;
	bool running = true;
	do
	{
		// Build
		QuestionGenerator questionGenerator(std::make_shared<MyRNG>());
		std::shared_ptr<IGame> game = std::make_shared<Game>(&std::cin, &std::cout, &questionGenerator);
		std::shared_ptr<IGameClock> gclock = std::make_shared<GameClock>();

		uint8_t time = 60;
		GameWithTime gt(game, gclock, time);
		// Run
		std::cout << "You will have " << std::to_string(time) << " seconds. To begin, enter any key." << std::endl;
		std::cin.get();
		gt.play();

		// score calculation (3*correctAns) - (1*wrongAns) | can't be less than 0.
		uint32_t score = game->correctAnswers() * 10;
		uint32_t penalty = game->wrongAnswers() * 5;
		score = (score < penalty) ? 0 : (score - penalty);
		std::cout << "You scored " << std::to_string(score) << " points! (Correct: " << std::to_string(game->correctAnswers()) << ", Incorrect: " << std::to_string(game->wrongAnswers()) << ")." << std::endl;

		// Save highscore (rough code below)
		IEncryptorPtr xorEncrypt = std::make_shared<MyEncryptor>();
		IDataStoragePtr fs = std::make_shared<FileStorage>("hs");
		Highscores highscores(fs, xorEncrypt);

		HighscoreEntry entry;
		std::cout << "Enter name: ";
		std::string name;
		std::cin >> name;
		entry.name = name;
		entry.score = score;
		{
			std::time_t now = std::time(nullptr);
			std::tm* localTime = std::localtime(&now);
			char buffer[100];
			std::strftime(buffer, 100, "%d-%m-%Y_%H:%M:%S", localTime);
			entry.timestamp = std::string(buffer);
		}

		highscores.add(entry);
		highscores.save();

		// show highscores
		std::cout << std::endl << std::left << std::setw(20) << "Name"
			<< std::setw(10) << "Score"
			<< std::setw(25) << "Timestamp" << std::endl;

		std::cout << std::setw(20) << std::setfill('-') << ""
			<< std::setw(10) << ""
			<< std::setw(25) << "" << std::endl;

		// Reset fill character to space
		std::cout << std::setfill(' ');

		for (uint32_t i = 0; i < highscores.size(); i++)
		{
			auto hs = highscores.get(i);
			std::cout << std::left << std::setw(20) << hs.name
				<< std::setw(10) << hs.score
				<< std::setw(25) << hs.timestamp << std::endl;
		}
		std::cout << std::endl << "Play again? (y/n): ";
		char val;
		while ((val = std::cin.get()))
		{
			if (std::tolower(val) == 'n')
			{
				running = false;
				break;
			}
			if (std::tolower(val) == 'y')
			{
				break;
			}
		}
		std::getline(std::cin, std::string());	// clear buffer
	} while (running);
}
#endif