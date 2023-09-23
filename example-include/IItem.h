#pragma once

#include <string>

class IItem
{
public:
	virtual bool isItEquivalent(std::string val) = 0;
	virtual std::string getString() = 0;
	virtual std::string getBaseString() = 0;
};
