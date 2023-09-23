#pragma once

#include "IItem.h"

class HexNumber : public IItem
{
public:
	HexNumber(int num) : m_num{ num } {};
	bool isItEquivalent(std::string val) override;
	std::string getString() override;
	std::string getBaseString() override;
private:
	int m_num;
};