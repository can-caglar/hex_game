#pragma once

#include <istream>
#include <ostream>
#include "INumberGenerator.h"
#include "Questioner.h"

class IGame
{
public:
	virtual void tick() = 0;
	virtual int correctAnswers() = 0;
	virtual int wrongAnswers() = 0;
};

class Game : public IGame
{
public:
	Game(std::istream* is, std::ostream* os,
		INumberGenerator* gen) :
		m_is{ is },
		m_os{ os },
		m_gen{ gen },
		m_questioner() {}
	void tick() override;
	int correctAnswers() override;
	int wrongAnswers() override;
private:
	std::istream* m_is;
	std::ostream* m_os;
	INumberGenerator* m_gen;
	Questioner m_questioner;	// todo, "don't rely on concretions"
};