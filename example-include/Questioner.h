#pragma once

#include "IItem.h"

class Questioner
{
public:
	Questioner() : m_Question{ nullptr }, m_Ans{ nullptr } { };
	std::string generateQuestion(IItem* q, IItem* a);
	std::string generateResponseTo(std::string);
private:
	IItem* m_Question;
	IItem* m_Ans;
};