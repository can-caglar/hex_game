#pragma once

#include "IItem.h"

class DecimalNumber : public IItem
{
public:
	DecimalNumber(int num) : m_num{ (double)num } {};

	bool isItEquivalent(std::string) override;
	std::string getString() override;
	std::string getBaseString() override;
private:
	double m_num;
};

