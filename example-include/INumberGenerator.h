#pragma once

#include "IItem.h"
#include <memory>

class INumberGenerator
{
public:
	virtual ItemPtr getQuestion() = 0;
	virtual ItemPtr getAnswer() = 0;
	virtual void generate() = 0;
};
