#pragma once

#include "IItem.h"

class BinaryNumber : public IItem
{
public:
	BinaryNumber(int num) : m_num{ num } {};
	bool isItEquivalent(std::string val) override;
	std::string getString() override;
	std::string getBaseString() override;
protected:
	int m_num;
};