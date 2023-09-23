#pragma once

#include <string>
#include <memory>

class IItem
{
public:
	virtual bool isItEquivalent(std::string val) = 0;
	virtual std::string getString() = 0;
	virtual std::string getBaseString() = 0;
};

typedef std::shared_ptr<IItem> ItemPtr;
