#include "Game.h"
#include "Questioner.h"

void Game::tick()
{
	// Generate new question/answer
	m_gen->generate();

	// Generate the string
	std::string q = m_questioner.generateQuestion(m_gen->getQuestion(), m_gen->getAnswer());

	// Write it out
	*m_os << q;

	// Get answer
	std::string ans("");
	*m_is >> ans;

	std::string response = m_questioner.generateResponseTo(ans);

	*m_os << response;
}

int Game::correctAnswers()
{
	return m_questioner.correctAnswers();
}

int Game::wrongAnswers()
{
	return m_questioner.wrongAnswers();
}