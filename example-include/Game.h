#pragma once

#include <istream>
#include <ostream>
#include "INumberGenerator.h"
#include "Questioner.h"

class Game
{
public:
	Game(std::istream* is, std::ostream* os,
		INumberGenerator* gen) :
		m_is{ is },
		m_os{ os },
		m_gen{ gen },
		m_questioner() {}
	void tick();
	int correctAnswers();
	int wrongAnswers();
private:
	std::istream* m_is;
	std::ostream* m_os;
	INumberGenerator* m_gen;
	Questioner m_questioner;	// todo, "don't rely on concretions"
};