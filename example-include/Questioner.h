#pragma once

#include "IItem.h"

class Questioner
{
public:
	Questioner() : 
		m_Question{ nullptr }, 
		m_Ans{ nullptr },
		m_correctAnswers{ 0 },
		m_wrongAnswers{ 0 }
		{ };
	std::string generateQuestion(ItemPtr q, ItemPtr a);
	std::string generateResponseTo(std::string);
	int correctAnswers() { return m_correctAnswers; }
	int wrongAnswers() { return m_wrongAnswers; }
private:
	ItemPtr m_Question;
	ItemPtr m_Ans;
	int m_correctAnswers;
	int m_wrongAnswers;
};