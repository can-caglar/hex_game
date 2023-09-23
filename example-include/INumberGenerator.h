#pragma once

#include "IItem.h"

class INumberGenerator
{
public:
	IItem* getQuestion();
	IItem* getAnswer();
	virtual void generate() = 0;
};
