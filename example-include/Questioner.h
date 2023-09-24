#pragma once

#include "IItem.h"

class Questioner
{
public:
	Questioner() : m_Question{ nullptr }, m_Ans{ nullptr } { };
	std::string generateQuestion(ItemPtr q, ItemPtr a);
	std::string generateResponseTo(std::string);
private:
	ItemPtr m_Question;
	ItemPtr m_Ans;
};